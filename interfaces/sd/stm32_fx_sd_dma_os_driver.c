/***************************************************************************
  * Copyright (c) 2024 Microsoft Corporation
  * Copyright (c) 2026 STMicroelectronics
  *
  * This program and the accompanying materials are made available under the
  * terms of the MIT License which is available at
  * https://opensource.org/licenses/MIT.
  *
  * SPDX-License-Identifier: MIT
  **************************************************************************/


/* Include necessary system files.  */
#include "stm32_fx_sd_dma_os_driver.h"

/* utility function to compute the FAT start partition */
UINT  _fx_partition_offset_calculate(void  *partition_sector, UINT partition, ULONG *partition_start,
                                     ULONG *partition_size);
static UINT sd_read_data(FX_MEDIA *media_ptr, STM32_FX_SD_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors);
static UINT sd_write_data(FX_MEDIA *media_ptr, STM32_FX_SD_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors);
static UINT stm32_fx_get_card_state(hal_sd_handle_t *sd_handle, ULONG max_timeout);

/**
  * @brief This function is the entry point to the STM32 SD disk driver.
  * It relies on the STM32 peripheral library from ST.
  * @param media_ptr: FileX's Media Config Block
  * @retval None
  */

VOID  stm32_fx_sd_dma_os_driver(FX_MEDIA *media_ptr)
{
  UINT status;
  ULONG partition_start;
  ULONG partition_size;

  STM32_FX_SD_DRIVER_CONTEXT *sd_context = (STM32_FX_SD_DRIVER_CONTEXT *)media_ptr->fx_media_driver_info;


  /* Process the driver request specified in the media control block.  */
  switch (media_ptr->fx_media_driver_request)
  {
    case FX_DRIVER_INIT:
    {
      /* Check that the sd_context is valid otherwise return FX_PTR_ERROR. */
      if (sd_context == FX_NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* Check that the sd_handle is valid otherwise return FX_PTR_ERROR. */

      if (sd_context->sd_handle == FX_NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* Check that sd_max_timeout is valid otherwise, set FX_PTR_ERROR. */
      if (sd_context->sd_max_timeout == 0)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* The sd handle is already intitalized by the application
      check that the sd card is ready. */

      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);

      if (status == FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
      }

      /* Create a semaphore used for transfer notification */
      sd_context->sd_rx_cplt_semaphore.semaphore_handle = xSemaphoreCreateBinary();

      if (sd_context->sd_rx_cplt_semaphore.semaphore_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      sd_context->sd_tx_cplt_semaphore.semaphore_handle = xSemaphoreCreateBinary();

      if (sd_context->sd_tx_cplt_semaphore.semaphore_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* Check if the FX_SD_FLAG_SCRATCH_BUFFER flag is initialized */

      if (sd_context->flags & FX_SD_FLAG_SCRATCH_BUFFER)
      {
        if (sd_context->scratch_buffer == FX_NULL)
        {
          media_ptr->fx_media_driver_status = FX_PTR_ERROR;

          break;
        }
      }
      /* Register the SD Xfer Callback to be used */
      HAL_SD_RegisterXferCpltCallback(sd_context->sd_handle, HAL_SD_XferCpltCallback);

      /* Store the user data into the SD handle. */
      HAL_SD_SetUserData(sd_context->sd_handle, (void *)sd_context);

      break;
    }

    case FX_DRIVER_READ:
    {
      /* Check the card state before any operation */
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      status = sd_read_data(media_ptr, sd_context, media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors,
       media_ptr->fx_media_driver_sectors);

      if (status == FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
      }

      break;
    }

    case FX_DRIVER_BOOT_READ:
    {
      /* Check the card state before any operation */
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }
      /* the boot sector is the sector zero */
      status = sd_read_data(media_ptr, sd_context, 0, media_ptr->fx_media_driver_sectors);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = status;
        break;
      }

      /* Check if the sector 0 is the actual boot sector, otherwise calculate the offset into it.*/

      partition_start =  0;

      status =  _fx_partition_offset_calculate(media_ptr->fx_media_driver_buffer, 0, &partition_start, &partition_size);

      /* Check partition read error.  */
      if (status)
      {
        /* Unsuccessful driver request.  */
        media_ptr->fx_media_driver_status =  FX_IO_ERROR;
        break;
      }

      /* Check that there is a partition  */
      if (partition_start)
      {
        /* Yes, now lets read the actual boot record.  */
        status = sd_read_data(media_ptr, sd_context, partition_start, media_ptr->fx_media_driver_sectors);

        if (status != FX_SUCCESS)
        {
          media_ptr->fx_media_driver_status = status;
          break;
        }
      }

      /* Successful driver request.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }

    case FX_DRIVER_WRITE:
    {
      media_ptr->fx_media_driver_status = FX_IO_ERROR;

      /* Check the card state before any operation */
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      status = sd_write_data(media_ptr, sd_context, media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors,
       media_ptr->fx_media_driver_sectors);

      if (status == FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
      }

      break;
    }

    case FX_DRIVER_BOOT_WRITE:
    {
      media_ptr->fx_media_driver_status = FX_IO_ERROR;

      /* Check the card state before any operation */
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      status = sd_write_data(media_ptr, sd_context, 0, media_ptr->fx_media_driver_sectors);

      if (status == FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
      }

      break;
    }


    case FX_DRIVER_FLUSH:
    {
      /* Return driver success.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }

    case FX_DRIVER_UNINIT:
    case FX_DRIVER_ABORT:
    {
      /* Delete the semaphore and free the associated resource */
      if (sd_context->sd_rx_cplt_semaphore.semaphore_handle != NULL)
      {
        vSemaphoreDelete(sd_context->sd_rx_cplt_semaphore.semaphore_handle);

        sd_context->sd_rx_cplt_semaphore.semaphore_handle = NULL;
      }

      if (sd_context->sd_tx_cplt_semaphore.semaphore_handle != NULL)
      {
        vSemaphoreDelete(sd_context->sd_tx_cplt_semaphore.semaphore_handle);

        sd_context->sd_tx_cplt_semaphore.semaphore_handle = NULL;
      }

      /* Return driver success. */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;

      break;
    }

    default:
    {
      media_ptr->fx_media_driver_status =  FX_IO_ERROR;
      break;
    }
  }
}

/**
  * @brief Check the SD IP status.
  * @param hal_sd_handle_t *sd_handle
  * @param ULONG max_timeout Maximum timeout duration in milliseconds.
  * @retval FX_SUCCESS when ready and FX_INVALID_STATE otherwise
  */

static UINT stm32_fx_get_card_state(hal_sd_handle_t *sd_handle, ULONG max_timeout)
{
  UINT status = FX_INVALID_STATE;
  hal_sd_card_state_t state;

  uint32_t start_time = HAL_GetTick();
  while (HAL_GetTick() - start_time < max_timeout)
  {
    state = HAL_SD_GetCardState(sd_handle);

    if (state == HAL_SD_CARD_TRANSFER)
    {
      status = FX_SUCCESS;
      break;
    }

  }

  return status;
}

/**
  * @brief Read data from uSD into destination buffer
  * @param FX_MEDIA *media_ptr a pointer the main FileX structure
  * @param STM32_FX_SD_DRIVER_CONTEXT *ctx a pointer the sd driver context
  * @param ULONG start_addr first sector to start reading from
  * @param UINT num_sectors number of sectors to be read
  * @retval FX_SUCCESS on success FX_BUFFER_ERROR / FX_ACCESS_ERROR / FX_IO_ERROR otherwise
  */

static UINT sd_read_data(FX_MEDIA *media_ptr, STM32_FX_SD_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors)
{
  UINT status;
  UCHAR *read_addr;
  ULONG i;

  hal_sd_handle_t *sd_handle = ctx->sd_handle;

  /* When the FX_SD_FLAG_SCRATCH_BUFFER flag is enabled, we need to check that the media_buffer
     is not 4 byte aligned to decide whether to use an intermediate read operation or not.
   */
  if ((ctx->flags & FX_SD_FLAG_SCRATCH_BUFFER) && (UINT)(media_ptr->fx_media_driver_buffer) & 0x3)
  {
    read_addr = media_ptr->fx_media_driver_buffer;

    /* Read one sector at a time into the scratch buffer then copy into the user buffer. */
    for (i = 0; i < num_sectors; i++)
    {
      status = HAL_SD_ReadBlocks_DMA(sd_handle, (uint8_t *)ctx->scratch_buffer, (uint32_t)(start_addr + i), 1);

      if (status != HAL_OK)
      {
        return FX_IO_ERROR;
      }

      /* wait until the read operation is completed */
      if (xSemaphoreTake(ctx->sd_rx_cplt_semaphore.semaphore_handle, ctx->sd_max_timeout) != pdTRUE)
      {
        return FX_IO_ERROR;
      }

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
      if (ctx->flags & FX_SD_FLAG_CACHE_MAINTENANCE)
      {
        SCB_InvalidateDCache_by_Addr((uint32_t *)ctx->scratch_buffer, media_ptr->fx_media_bytes_per_sector);
      }
#endif /* __DCACHE_PRESENT */

      _fx_utility_memory_copy(ctx->scratch_buffer,
                              read_addr + i * media_ptr->fx_media_bytes_per_sector,
                              media_ptr->fx_media_bytes_per_sector);
    }

    status = FX_SUCCESS;
  }
  else
  {
    status = HAL_SD_ReadBlocks_DMA(sd_handle, media_ptr->fx_media_driver_buffer, (uint32_t)start_addr, num_sectors);

    if (status != HAL_OK)
    {
      /* read error occurred, call the error handler code then return immediately */
      return FX_IO_ERROR;
    }

    /* wait until the read operation is completed */
    if (xSemaphoreTake(ctx->sd_rx_cplt_semaphore.semaphore_handle, ctx->sd_max_timeout) != pdTRUE)
    {
      return FX_IO_ERROR;
    }

    status = FX_SUCCESS;

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    if (ctx->flags & FX_SD_FLAG_CACHE_MAINTENANCE)
    {
      SCB_InvalidateDCache_by_Addr((uint32_t *)media_ptr->fx_media_driver_buffer,
      num_sectors * media_ptr->fx_media_bytes_per_sector);
    }
#endif /* __DCACHE_PRESENT */
  }

  return status;
}

/**
  * @brief write data buffer into the uSD
  * @param FX_MEDIA *media_ptr a pointer the main FileX structure
  * @param STM32_FX_SD_DRIVER_CONTEXT *ctx a pointer the sd driver context
  * @param ULONG start_addr first sector to start writing from
  * @param UINT num_sectors number of sectors to be written
  * @retval FX_SUCCESS on success FX_BUFFER_ERROR / FX_ACCESS_ERROR / FX_IO_ERROR otherwise
  */

static UINT sd_write_data(FX_MEDIA *media_ptr, STM32_FX_SD_DRIVER_CONTEXT *ctx, ULONG start_addr, ULONG num_sectors)
{
  UINT status;
  UCHAR *write_addr;
  ULONG i;

  hal_sd_handle_t *sd_handle = ctx->sd_handle;

  /* When the FX_SD_FLAG_SCRATCH_BUFFER flag is enabled, we need to check that the media_buffer
     is not 4 byte aligned to decide whether to use an intermediate write operation or not.
  */
  if ((ctx->flags & FX_SD_FLAG_SCRATCH_BUFFER) && (UINT)(media_ptr->fx_media_driver_buffer) & 0x3)
  {
    write_addr = media_ptr->fx_media_driver_buffer;

    /* Write one sector at a time from the scratch buffer (used when user buffer is unaligned). */
    for (i = 0; i < num_sectors; i++)
    {
      _fx_utility_memory_copy(write_addr + i * media_ptr->fx_media_bytes_per_sector,
                              ctx->scratch_buffer,
                              media_ptr->fx_media_bytes_per_sector);

#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
      if (ctx->flags & FX_SD_FLAG_CACHE_MAINTENANCE)
      {
        /* Clean the DCache to make the SD DMA see the actual content of the scratch buffer */
        SCB_CleanDCache_by_Addr((uint32_t *)ctx->scratch_buffer, media_ptr->fx_media_bytes_per_sector);
      }
#endif /* __DCACHE_PRESENT */

      status = HAL_SD_WriteBlocks_DMA(sd_handle, (uint8_t *)ctx->scratch_buffer, (uint32_t)(start_addr + i), 1);

      if (status != HAL_OK)
      {
        return FX_IO_ERROR;
      }

      /* wait until the write operation is completed */
      if (xSemaphoreTake(ctx->sd_tx_cplt_semaphore.semaphore_handle, ctx->sd_max_timeout) != pdTRUE)
      {
        return FX_IO_ERROR;
      }
    }

    status = FX_SUCCESS;
  }

  else
  {
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    if (ctx->flags & FX_SD_FLAG_CACHE_MAINTENANCE)
    {
      SCB_CleanDCache_by_Addr((uint32_t *)media_ptr->fx_media_driver_buffer,
      num_sectors * media_ptr->fx_media_bytes_per_sector);
    }
#endif /* __DCACHE_PRESENT */

    /* FileX is writing one sector per operation,i.e num_sectors is always equal to 1.
       Thus call the HAL_SD_WriteBlocks_DMA without any loop
     */
    status = HAL_SD_WriteBlocks_DMA(sd_handle, media_ptr->fx_media_driver_buffer, (uint32_t)start_addr, num_sectors);

    if (status != HAL_OK)
    {
      return FX_IO_ERROR;
    }

    /* Define how to notify about write completion operation */
    if (xSemaphoreTake(ctx->sd_tx_cplt_semaphore.semaphore_handle, ctx->sd_max_timeout) != pdTRUE)
    {
      return FX_IO_ERROR;
    }
    status = FX_SUCCESS;
  }

  return status;
}

/**
  * @brief SD DMA Rx Transfer completed callbacks in RTOS mode
  * @param SD_HandleTypeDef *hsd the SD_HandleTypeDef handle
  * @param hal_sd_event_cb_t cb_event callback event relative to the competed transfer operation
  * @retval None
  */
void HAL_SD_XferCpltCallback(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event)
{
  STM32_FX_SD_DRIVER_CONTEXT *sd_context;
  const void *p_user_data;

  p_user_data = HAL_SD_GetUserData(hsd);
  sd_context = (STM32_FX_SD_DRIVER_CONTEXT *)p_user_data;

  /* Check that the Rx transfer is completed */
  if (cb_event == HAL_SD_EVENT_CB_RX_CPLT)
  {
    xSemaphoreGiveFromISR(sd_context->sd_rx_cplt_semaphore.semaphore_handle, NULL);
  }
  /* check that the Tx transfer is completed. */
  if (cb_event == HAL_SD_EVENT_CB_TX_CPLT)
  {
    xSemaphoreGiveFromISR(sd_context->sd_tx_cplt_semaphore.semaphore_handle, NULL);
  }
}

