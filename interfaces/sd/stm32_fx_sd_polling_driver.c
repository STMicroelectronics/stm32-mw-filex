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


/* Include necessary system files. */
#include "stm32_fx_sd_polling_driver.h"


/* Utility function to compute the FAT start partition */
UINT _fx_partition_offset_calculate(void  *partition_sector, UINT partition, ULONG *partition_start, ULONG *partition_size);
static UINT stm32_fx_get_card_state(hal_sd_handle_t *sd_handle, ULONG max_timeout);


/**
 * @brief Entry point for the STM32 SD disk driver.
 * Relies on STM32 HAL SD peripheral library.
 * @param media_ptr Pointer to FileX Media Config Block.
 * @retval None
 */
VOID stm32_fx_sd_polling_driver(FX_MEDIA *media_ptr)
{
  ULONG status;
  STM32_FX_SD_DRIVER_CONTEXT *sd_context = (STM32_FX_SD_DRIVER_CONTEXT *)media_ptr->fx_media_driver_info;

  switch(media_ptr->fx_media_driver_request)
  {
    case FX_DRIVER_INIT:
    {
      /* Check that the sd_context is valid otherwise return FX_PTR_ERROR. */
      if (sd_context == FX_NULL)
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

      /* check that the sd card is ready. */
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);
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
      /* Check the card state before any oprartion */
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      if (HAL_SD_ReadBlocks(sd_context->sd_handle, media_ptr->fx_media_driver_buffer, media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors,
                            media_ptr->fx_media_driver_sectors, sd_context->sd_max_timeout) == HAL_OK)
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
      ULONG partition_start;
      ULONG partition_size;

      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      if (HAL_SD_ReadBlocks(sd_context->sd_handle, media_ptr->fx_media_driver_buffer, 0, media_ptr->fx_media_driver_sectors,
                            sd_context->sd_max_timeout) != HAL_OK)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      /* Sector correctly read, check the actual partition start */
      status = _fx_partition_offset_calculate(media_ptr->fx_media_driver_buffer, 0, &partition_start, &partition_size);
      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        break;
      }

      if (partition_start != 0)
      {
        status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);
        if (status != FX_SUCCESS)
        {
          media_ptr->fx_media_driver_status = FX_INVALID_STATE;
          break;
        }

        /* Read data from the uSD card into the data buffer */
        if (HAL_SD_ReadBlocks(sd_context->sd_handle, media_ptr->fx_media_driver_buffer, partition_start, media_ptr->fx_media_driver_sectors,
                              sd_context->sd_max_timeout) != HAL_OK)
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
      status = stm32_fx_get_card_state(sd_context->sd_handle, sd_context->sd_max_timeout);

      if (status != FX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_INVALID_STATE;
        break;
      }

      /* Set start sector to 0 for boot write, else use logical sector. */

      ULONG start_sector = (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_WRITE)
                           ? 0
                           : (media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors);

      /* Write data to SD card and set status to success if write succeeds. */
      if (HAL_SD_WriteBlocks(sd_context->sd_handle, (const uint8_t *)media_ptr->fx_media_driver_buffer, start_sector, media_ptr->fx_media_driver_sectors,
                             sd_context->sd_max_timeout) == HAL_OK)
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
    case FX_DRIVER_UNINIT:
    case FX_DRIVER_ABORT:
    {
      /* Return driver success. */
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
 * @brief Check the SD card state.
 * @param sd_handle Pointer to the HAL SD handle.
 * @param max_timeout Timeout in milliseconds.
 * @retval FX_SUCCESS if card is ready, FX_INVALID_STATE otherwise.
 */
static UINT stm32_fx_get_card_state(hal_sd_handle_t *sd_handle, ULONG max_timeout)
{
  UINT status = FX_INVALID_STATE;
  hal_sd_card_state_t state;

  uint32_t start_time = HAL_GetTick();

  while ((HAL_GetTick() - start_time) < max_timeout)
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
