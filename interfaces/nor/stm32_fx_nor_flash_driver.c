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
#include "stm32_fx_nor_flash_driver.h"
VOID stm32_fx_nor_flash_driver(FX_MEDIA *media_ptr)
{
  UINT status;
  STM32_FX_NOR_FLASH_DRIVER_CONTEXT *nor_flash_context = (STM32_FX_NOR_FLASH_DRIVER_CONTEXT *)media_ptr->fx_media_driver_info;

  /* Process the driver request specified in the media control block.  */
  switch(media_ptr->fx_media_driver_request)
  {
  case FX_DRIVER_INIT:
    {
      /* Check that the nor_flash_context is valid otherwise return FX_PTR_ERROR. */
      if (nor_flash_context == FX_NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;
        break;
      }

      /* Check that the nor_flash_handle is valid otherwise return FX_PTR_ERROR. */
      if (nor_flash_context->stm32_lx_nor_flash_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;
        break;
      }

      /* check on the initial fx_media_driver_status to know whether the FX_DRIVER_INIT request
       * is form a fx_media_format() or fx_media_open() call
       */
      if ( media_ptr->fx_media_driver_status == FX_MEDIA_INVALID)
      {
        status = lx_nor_flash_format(nor_flash_context->stm32_lx_nor_flash_handle, "NOR_FLASH",
                                     nor_flash_context->stm32_lx_nor_flash_driver_init,
                                     nor_flash_context->stm32_lx_nor_flash_driver_context);
        if (status != LX_SUCCESS)
        {
           media_ptr->fx_media_driver_status = FX_IO_ERROR;
           break;
        }
      }
      /* Open flash instance*/
      status = lx_nor_flash_open_extended(nor_flash_context->stm32_lx_nor_flash_handle, "NOR_FLASH",
                                          nor_flash_context->stm32_lx_nor_flash_driver_init,
                                          nor_flash_context->stm32_lx_nor_flash_driver_context);

      if (status == LX_SUCCESS)
      {
#ifndef LX_NOR_DISABLE_EXTENDED_CACHE
        /* Enable the NOR flash cache for the flash_instance */
        status = lx_nor_flash_extended_cache_enable(nor_flash_context->stm32_lx_nor_flash_handle,
                                                    nor_flash_context->extended_cache_memory,
                                                    nor_flash_context->extended_cache_memory_size);

        if (status == LX_SUCCESS)
        {
          media_ptr->fx_media_driver_free_sector_update = FX_TRUE;
          media_ptr->fx_media_driver_status = FX_SUCCESS;
        }
        else
        {
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
        }
#endif
        media_ptr->fx_media_driver_free_sector_update = FX_TRUE;
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
      }
      break;
    }

    case FX_DRIVER_UNINIT:
    {
      /* Close the LX_NOR_FLASH instance while the underlying hw is still initialized */
        status = lx_nor_flash_close(nor_flash_context->stm32_lx_nor_flash_handle);

        if (status == LX_SUCCESS)
        {
          media_ptr->fx_media_driver_status = FX_SUCCESS;
        }
        else
        {
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
        }
        break;
    }

    case FX_DRIVER_READ:
    case FX_DRIVER_BOOT_READ:
    {
      ULONG i;

      /* Setup the logical sector in FX_DRIVER_BOOT_READ: always read from logical sector 0. Otherwise, use media_ptr->fx_media_driver_logical_sector. */
      ULONG logical_sector = (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_READ)
        ? 0 : media_ptr->fx_media_driver_logical_sector;

      /* Loop to read the requested number of sectors. */
      for(i=0; i<media_ptr->fx_media_driver_sectors; i++)
      {
        /* Read data from a sector in the NOR flash memory */
        status = lx_nor_flash_sector_read(nor_flash_context->stm32_lx_nor_flash_handle, (logical_sector + i),
                                          media_ptr->fx_media_driver_buffer + (i * media_ptr->fx_media_bytes_per_sector));
        if (status != LX_SUCCESS)
        {
          break;
        }
      }
      if (status == LX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
      }
      else
      {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
      }
      break;
    }

    case FX_DRIVER_WRITE:
    case FX_DRIVER_BOOT_WRITE:
    {
      ULONG i;

      /* Setup the logical sector in FX_DRIVER_BOOT_WRITE: always write from logical sector 0. Otherwise, use media_ptr->fx_media_driver_logical_sector. */
      ULONG logical_sector = (media_ptr->fx_media_driver_request == FX_DRIVER_BOOT_WRITE)
        ? 0 : media_ptr->fx_media_driver_logical_sector;

      /* Loop to write the requested number of sectors. */
      for(i=0; i<media_ptr->fx_media_driver_sectors; i++)
      {
        /* write data from a sector in the NOR flash memory */
        status = lx_nor_flash_sector_write(nor_flash_context->stm32_lx_nor_flash_handle, (logical_sector + i),
                                            media_ptr->fx_media_driver_buffer + (i * media_ptr->fx_media_bytes_per_sector));

        if (status != LX_SUCCESS)
        {
          break;
        }
      }

      if (status == LX_SUCCESS)
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
