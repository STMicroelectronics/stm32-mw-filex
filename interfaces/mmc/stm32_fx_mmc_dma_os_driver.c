/***************************************************************************
* Copyright (c) 2024 Microsoft Corporation
* Copyright (c) 2026 STMicroelectronics
*
* This program and the accompanying materials are made available under the
* terms of the MIT License which is available at
* https://opensource.org/licenses/MIT.
*
* SPDX-License-Identifier: MIT.
**************************************************************************/

/* Include necessary system files.  */
#include "stm32_fx_mmc_dma_os_driver.h"

/* Internal function prototypes for MMC utility and management */
UINT _fx_partition_offset_calculate(void  *partition_sector, UINT partition, ULONG *partition_start,
                                    ULONG *partition_size);
static UINT mmc_read_data(FX_MEDIA *media_ptr, STM32_FX_MMC_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors);
static UINT mmc_write_data(FX_MEDIA *media_ptr, STM32_FX_MMC_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors);
static UINT stm32_fx_get_card_state(hal_mmc_handle_t *mmc_handle, ULONG max_timeout);

/**
  * @brief Main entry point for the STM32 MMC disk driver.
  *        Handles FileX requests such as init, read, write, flush, etc.
  * @param media_ptr Pointer to the FileX media structure
  */
VOID stm32_fx_mmc_dma_os_driver(FX_MEDIA *media_ptr)
{
  UINT status;
  ULONG partition_start = 0;
  ULONG partition_size = 0;

  /* Retrieve the MMC driver context */
  STM32_FX_MMC_DRIVER_CONTEXT *ctx = (STM32_FX_MMC_DRIVER_CONTEXT *)media_ptr->fx_media_driver_info;

  /* Process the FileX driver request */
  switch (media_ptr->fx_media_driver_request)
  {
  case FX_DRIVER_INIT:
    {
      /* Validate context pointers */
      if (ctx == FX_NULL || ctx->mmc_handle == FX_NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;
        break;
      }

      /* Check that mmc_max_timeout is valid otherwise, set FX_PTR_ERROR. */
      if (ctx->mmc_max_timeout == 0)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* Check MMC card state */
      status = stm32_fx_get_card_state(ctx->mmc_handle, ctx->mmc_max_timeout);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      /* Create a semaphore used for transfer notification */
      ctx->mmc_rx_cplt_semaphore.semaphore_handle = xSemaphoreCreateBinary();

      if (ctx->mmc_rx_cplt_semaphore.semaphore_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      ctx->mmc_tx_cplt_semaphore.semaphore_handle = xSemaphoreCreateBinary();

      if (ctx->mmc_tx_cplt_semaphore.semaphore_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }


      /* Verify scratch buffer if flag is set */
      if ((ctx->flags & FX_MMC_FLAG_SCRATCH_BUFFER) && (ctx->scratch_buffer == FX_NULL))
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;
        break;
      }

      /* Register DMA transfer complete callback and associate user context */
      HAL_MMC_RegisterXferCpltCallback(ctx->mmc_handle, HAL_MMC_XferCpltCallback);
      HAL_MMC_SetUserData(ctx->mmc_handle, (void *)ctx);

      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

  case FX_DRIVER_READ:
  case FX_DRIVER_BOOT_READ:
    {
      /* Check MMC card state before reading */
      status = stm32_fx_get_card_state(ctx->mmc_handle, ctx->mmc_max_timeout);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      /* Determine logical sector to read (0 if boot read) */
      ULONG read_sector = (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_READ) ? 0 : media_ptr->fx_media_driver_logical_sector;

      /* Read requested sectors via DMA */
      status = mmc_read_data(media_ptr, ctx, read_sector, media_ptr->fx_media_driver_sectors);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        break;
      }

      /* If boot read, calculate partition offset and read partition data */
      if (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_READ)
      {
        status = _fx_partition_offset_calculate(media_ptr->fx_media_driver_buffer, 0, &partition_start, &partition_size);
        if (status != FX_SUCCESS)
        {
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
          break;
        }

        /* Read partition sectors if partition_start is valid */
        if (partition_start)
        {
          status = mmc_read_data(media_ptr, ctx, partition_start, media_ptr->fx_media_driver_sectors);
          if (status != FX_SUCCESS)
          {
            media_ptr->fx_media_driver_status = FX_IO_ERROR;
            break;
          }
        }
      }

      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

  case FX_DRIVER_WRITE:
  case FX_DRIVER_BOOT_WRITE:
    {
      /* Check MMC card state before writing */
      status = stm32_fx_get_card_state(ctx->mmc_handle, ctx->mmc_max_timeout);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      /* Determine logical sector to write (0 if boot write) */
      ULONG write_sector = (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_WRITE) ? 0 : media_ptr->fx_media_driver_logical_sector;

      /* Write requested sectors via DMA */
      status = mmc_write_data(media_ptr, ctx, write_sector, media_ptr->fx_media_driver_sectors);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        break;
      }

      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

  case FX_DRIVER_FLUSH:
  case FX_DRIVER_ABORT:
    {
      /* These operations are trivial in this context, return success */
      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

  case FX_DRIVER_UNINIT:
    {
      /* Delete the semaphore and free the associated resource */
      if (ctx->mmc_rx_cplt_semaphore.semaphore_handle != NULL)
      {
        vSemaphoreDelete(ctx->mmc_rx_cplt_semaphore.semaphore_handle);

        ctx->mmc_rx_cplt_semaphore.semaphore_handle = NULL;
      }

      if (ctx->mmc_tx_cplt_semaphore.semaphore_handle != NULL)
      {
        vSemaphoreDelete(ctx->mmc_tx_cplt_semaphore.semaphore_handle);

        ctx->mmc_tx_cplt_semaphore.semaphore_handle = NULL;
      }

      /* These operations are trivial in this context, return success */
      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

  default:
    {
      /* Unsupported request */
      media_ptr->fx_media_driver_status = FX_IO_ERROR;
      break;
    }
  }
}

/**
  * @brief Checks the MMC card state.
  * @param mmc_handle Pointer to the MMC handle
  * @param ULONG max_timeout Maximum timeout duration in milliseconds
  * @retval FX_SUCCESS if card is ready, FX_INVALID_STATE otherwise
  */
static UINT stm32_fx_get_card_state(hal_mmc_handle_t *mmc_handle, ULONG max_timeout)
{
  UINT status = FX_INVALID_STATE;
  hal_mmc_card_state_t state;
  uint32_t start_time = HAL_GetTick();

  /* Active wait with timeout until card is ready */
  while ((HAL_GetTick() - start_time) < max_timeout)
  {
    state = HAL_MMC_GetCardState(mmc_handle);
    if (state == HAL_MMC_CARD_TRANSFER)
    {
      status = FX_SUCCESS;
      break;
    }
  }

  return status;
}

/**
  * @brief Reads data from MMC into the destination buffer.
  * @param media_ptr Pointer to FileX media structure
  * @param ctx Pointer to MMC driver context
  * @param start_addr Starting sector address to read from
  * @param num_sectors Number of sectors to read
  * @retval FX_SUCCESS on success, FX_IO_ERROR otherwise
  */
static UINT mmc_read_data(FX_MEDIA *media_ptr, STM32_FX_MMC_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors)
{
  UINT status;
  UCHAR *buffer;
  hal_mmc_handle_t *mmc_handle = ctx->mmc_handle;
  UINT i;

  /* Select buffer based on memory alignment and scratch buffer flag */
  if ((ctx->flags & FX_MMC_FLAG_SCRATCH_BUFFER) && ((UINT)(media_ptr->fx_media_driver_buffer) & 0x3))
  {
    buffer = ctx->scratch_buffer;

    for (i = 0; i < num_sectors; i++)
    {
      /* Start DMA read transfer for one sector at a time */
      status = HAL_MMC_ReadBlocks_DMA(mmc_handle, buffer, (uint32_t)(start_addr + i), 1);
      if (status != HAL_OK)
      {
        return FX_IO_ERROR;
      }

      /* Wait for DMA completion semaphore */
      if (xSemaphoreTake(ctx->mmc_rx_cplt_semaphore.semaphore_handle, ctx->mmc_max_timeout) != pdTRUE)
      {
        return FX_IO_ERROR;
      }

      /* Copy from scratch buffer to user buffer for one sector */
      _fx_utility_memory_copy(ctx->scratch_buffer,
                              media_ptr->fx_media_driver_buffer + i * media_ptr->fx_media_bytes_per_sector,
                              media_ptr->fx_media_bytes_per_sector);

      /* Move buffer pointer to next sector */
      buffer += media_ptr->fx_media_bytes_per_sector;
    }
  }
  else
  {
    buffer = media_ptr->fx_media_driver_buffer;

    /* Start DMA read transfer for all sectors at once */
    status = HAL_MMC_ReadBlocks_DMA(mmc_handle, buffer, (uint32_t)start_addr, num_sectors);
    if (status != HAL_OK)
    {
      return FX_IO_ERROR;
    }

    /* Wait until the read operation is completed */
    if (xSemaphoreTake(ctx->mmc_rx_cplt_semaphore.semaphore_handle, ctx->mmc_max_timeout) != pdTRUE)
    {
      return FX_IO_ERROR;
    }
  }

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
  /* Invalidate D-Cache if cache maintenance flag is set */
  if (ctx->flags & FX_MMC_FLAG_CACHE_MAINTENANCE)
  {
    SCB_InvalidateDCache_by_Addr((uint32_t *)buffer, num_sectors * media_ptr->fx_media_bytes_per_sector);
  }
#endif

  return FX_SUCCESS;
}

/**
  * @brief Writes data to MMC from the source buffer.
  * @param media_ptr Pointer to FileX media structure
  * @param ctx Pointer to MMC driver context
  * @param start_addr Starting sector address to write to
  * @param num_sectors Number of sectors to write
  * @retval FX_SUCCESS on success, FX_IO_ERROR otherwise
  */
static UINT mmc_write_data(FX_MEDIA *media_ptr, STM32_FX_MMC_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors)
{
  UINT status;
  UCHAR *buffer;
  hal_mmc_handle_t *mmc_handle = ctx->mmc_handle;
  ULONG i;

  /* Check if scratch buffer should be used due to unaligned user buffer */
  if ((ctx->flags & FX_MMC_FLAG_SCRATCH_BUFFER) && ((UINT)(media_ptr->fx_media_driver_buffer) & 0x3))
  {
    /* Use scratch buffer for write operations */
    buffer = ctx->scratch_buffer;

    /* Write sectors one by one */
    for (i = 0; i < num_sectors; i++)
    {
      /* Copy one sector from user buffer to scratch buffer */
      _fx_utility_memory_copy(media_ptr->fx_media_driver_buffer + i * media_ptr->fx_media_bytes_per_sector,
                              buffer, media_ptr->fx_media_bytes_per_sector);

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
      /* Clean D-Cache to ensure data coherency if cache maintenance flag is set */
      if (ctx->flags & FX_MMC_FLAG_CACHE_MAINTENANCE)
      {
        SCB_CleanDCache_by_Addr((uint32_t *)buffer, media_ptr->fx_media_bytes_per_sector);
      }
#endif

      /* Start DMA transfer to write one sector */
      status = HAL_MMC_WriteBlocks_DMA(mmc_handle, buffer, (uint32_t)(start_addr + i), 1);
      if (status != HAL_OK)
      {
        return FX_IO_ERROR; /* Return error if DMA write fails */
      }

      /* Wait for DMA write completion semaphore */
      if (xSemaphoreTake(ctx->mmc_tx_cplt_semaphore.semaphore_handle, ctx->mmc_max_timeout) != pdTRUE)
      {
        return FX_IO_ERROR; /* Return error on timeout or failure */
      }

      /* Move buffer pointer to next sector */
      buffer += media_ptr->fx_media_bytes_per_sector;
    }
  }
  else
  {
    /* Use user buffer directly if properly aligned */
    buffer = media_ptr->fx_media_driver_buffer;

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    /* Clean D-Cache for entire buffer region before DMA write */
    if (ctx->flags & FX_MMC_FLAG_CACHE_MAINTENANCE)
    {
      SCB_CleanDCache_by_Addr((uint32_t *)buffer, num_sectors * media_ptr->fx_media_bytes_per_sector);
    }
#endif

    /* Start DMA transfer to write all sectors at once */
    status = HAL_MMC_WriteBlocks_DMA(mmc_handle, buffer, (uint32_t)start_addr, num_sectors);
    if (status != HAL_OK)
    {
      return FX_IO_ERROR; /* Return error if DMA write fails */
    }

    /* Wait for DMA write completion semaphore */
    if (xSemaphoreTake(ctx->mmc_tx_cplt_semaphore.semaphore_handle, ctx->mmc_max_timeout) != pdTRUE)
    {
      return FX_IO_ERROR; /* Return error on timeout or failure */
    }
  }

  /* Return success if all operations completed without error */
  return FX_SUCCESS;
}

/**
  * @brief SD DMA Rx Transfer completed callbacks in RTOS mode
  * @param SD_HandleTypeDef *hsd the SD_HandleTypeDef handle
  * @param hal_sd_event_cb_t cb_event callback event relative to the competed transfer operation
  * @retval None
  */
void HAL_MMC_XferCpltCallback(hal_mmc_handle_t *hmmc, hal_mmc_event_cb_t cb_event)
{
  STM32_FX_MMC_DRIVER_CONTEXT *ctx;
  const void *p_user_data;

  p_user_data = HAL_MMC_GetUserData(hmmc);
  ctx = (STM32_FX_MMC_DRIVER_CONTEXT *)p_user_data;

  /* Check that the Rx transfer is completed */
  if (cb_event == HAL_MMC_EVENT_CB_RX_CPLT)
  {
    xSemaphoreGiveFromISR(ctx->mmc_rx_cplt_semaphore.semaphore_handle, NULL);
  }
  /* check that the Tx transfer is completed. */
  if (cb_event == HAL_MMC_EVENT_CB_TX_CPLT)
  {
    xSemaphoreGiveFromISR(ctx->mmc_tx_cplt_semaphore.semaphore_handle, NULL);
  }
}
