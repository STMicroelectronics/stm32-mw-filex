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
#include "stm32_fx_mmc_polling_driver.h"


/* Utility function to compute the FAT start partition */
UINT _fx_partition_offset_calculate(void  *partition_sector, UINT partition,
                                    ULONG *partition_start, ULONG *partition_size);
static UINT stm32_fx_get_card_state(hal_mmc_handle_t *mmc_handle, ULONG max_timeout);


/**
  * @brief This function is the entry point to the STM32 MMC disk driver.
  * It relies on the STM32 peripheral library from ST.
  * @param media_ptr: FileX's Media Config Block
  * @retval None
  */
VOID  stm32_fx_mmc_polling_driver(FX_MEDIA *media_ptr)
{
  ULONG status;
  STM32_FX_MMC_DRIVER_CONTEXT *mmc_context = (STM32_FX_MMC_DRIVER_CONTEXT *)media_ptr->fx_media_driver_info;

  /* Process the driver request specified in the media control block.  */
  switch(media_ptr->fx_media_driver_request)
  {
    case FX_DRIVER_INIT:
    {
      /* Check that the mmc_context is valid otherwise return FX_PTR_ERROR. */
      if (mmc_context == FX_NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* Check that the mmc_handle is valid otherwise return FX_PTR_ERROR. */
      if (mmc_context->mmc_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /* Check that mmc_max_timeout is valid otherwise, set FX_PTR_ERROR. */
      if (mmc_context->mmc_max_timeout == 0)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;

        break;
      }

      /*
      * The MMC handle is already initialized by the application
      * check that the MMC card is ready.
      */
      status = stm32_fx_get_card_state(mmc_context->mmc_handle, mmc_context->mmc_max_timeout);

      if (status == FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
      }
      break;
    }

    case FX_DRIVER_READ:
    {
      /* Check the card state before any operation */
      status = stm32_fx_get_card_state(mmc_context->mmc_handle, mmc_context->mmc_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      if (HAL_MMC_ReadBlocks(mmc_context->mmc_handle, media_ptr->fx_media_driver_buffer, media_ptr->fx_media_driver_logical_sector,
                             media_ptr->fx_media_driver_sectors, mmc_context->mmc_max_timeout) == HAL_OK)
      {
        status = FX_SUCCESS;
      }
      else
      {
        status = FX_IO_ERROR;
      }

      media_ptr->fx_media_driver_status = status;

      break;
    }

    case FX_DRIVER_BOOT_READ:
    {
      ULONG partition_start;
      ULONG partition_size;

      status = stm32_fx_get_card_state(mmc_context->mmc_handle, mmc_context->mmc_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      if (HAL_MMC_ReadBlocks(mmc_context->mmc_handle, media_ptr->fx_media_driver_buffer, 0, media_ptr->fx_media_driver_sectors,
                             mmc_context->mmc_max_timeout) != HAL_OK)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      /* Sector correctly read, check the actual partition start */
      partition_start = 0;

      status = _fx_partition_offset_calculate(media_ptr->fx_media_driver_buffer, 0, &partition_start, &partition_size);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        break;
      }

      if (partition_start != 0)
      {
        if (HAL_MMC_ReadBlocks(mmc_context->mmc_handle, media_ptr->fx_media_driver_buffer, partition_start, media_ptr->fx_media_driver_sectors,
                               mmc_context->mmc_max_timeout) != HAL_OK)
        {
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
          break;
        }
      }

      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

    case FX_DRIVER_WRITE:
    case FX_DRIVER_BOOT_WRITE:
    {
      status = stm32_fx_get_card_state(mmc_context->mmc_handle, mmc_context->mmc_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      ULONG start_sector = (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_WRITE)
                           ? 0
                           : (media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors);

      if (HAL_MMC_WriteBlocks(mmc_context->mmc_handle, (const uint8_t *)media_ptr->fx_media_driver_buffer, start_sector, media_ptr->fx_media_driver_sectors,
                              mmc_context->mmc_max_timeout) == HAL_OK)
      {
        status = FX_SUCCESS;
      }
      else
      {
        status = FX_IO_ERROR;
      }

      media_ptr->fx_media_driver_status = status;

      break;
    }

    case FX_DRIVER_FLUSH:
    case FX_DRIVER_UNINIT:
    case FX_DRIVER_ABORT:
    {
      /* Return driver success.  */
      media_ptr->fx_media_driver_status = FX_SUCCESS;
      break;
    }

    default:
    {
      media_ptr->fx_media_driver_status = FX_INVALID_OPTION;
      break;
    }
  }
}

/**
  * @brief Check the MMC IP status.
  * @param hal_mmc_handle_t *mmc_handle
  * @param ULONG max_timeout Maximum timeout duration in milliseconds
  * @retval FX_SUCCESS when ready and FX_INVALID_STATE otherwise
  */

static UINT stm32_fx_get_card_state(hal_mmc_handle_t *mmc_handle, ULONG max_timeout)
{
  UINT status = FX_INVALID_STATE;
  hal_mmc_card_state_t state;

  uint32_t start_time = HAL_GetTick();
  while (HAL_GetTick() - start_time < max_timeout)
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
