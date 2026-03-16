
/***************************************************************************
  * Copyright (c) 2024 Microsoft Corporation
  * Copyright (c) 2026 STMicroelectronics
  *
  * This program and the accompanying materials are made available under the
  * terms of the MIT License which is available at
  * https://opensource.org/licenses/MIT.
  *
  * SPDX-License-Identifier: MIT
  *************************************************************************/


#include "stm32_fx_nand_flash_driver.h"

VOID  stm32_fx_nand_flash_driver(FX_MEDIA *media_ptr)
{
  UINT status;
  ULONG logical_sector;

  /* Retrieve the NAND flash driver context from the media control block */
  STM32_FX_NAND_FLASH_DRIVER_CONTEXT *nand_flash_context = (STM32_FX_NAND_FLASH_DRIVER_CONTEXT *)media_ptr->fx_media_driver_info;

  /* Process the driver request specified in the media control block.  */
  switch(media_ptr->fx_media_driver_request)
  {
  case FX_DRIVER_INIT:
    {
      /* Check that the nand_flash_context is valid otherwise return FX_PTR_ERROR. */
      if (nand_flash_context == FX_NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;
        break;
      }

      /* Check for a NULL nand_flash_handle  */
      if (nand_flash_context->stm32_lx_nand_flash_handle == NULL)
      {
        media_ptr->fx_media_driver_status = FX_PTR_ERROR;
        break;
      }
      /* call the lx_nand_flash_format_extended only when the fx_media_format() is the origin of
       * the DRIVER_INIT request.
       */
      if (media_ptr->fx_media_driver_status == FX_MEDIA_INVALID)
      {
        /* Format NAND flash instance using leveLX */
        status = lx_nand_flash_format_extended(nand_flash_context->stm32_lx_nand_flash_handle, "nand flash",

                                               nand_flash_context->stm32_lx_nand_flash_driver_init,

                                               nand_flash_context->stm32_lx_nand_flash_driver_context,

                                               nand_flash_context->stm32_lx_nand_driver_buffer,

                                               nand_flash_context->stm32_lx_nand_driver_buffer_size);
        /* check if format succeed */
        if (status != LX_SUCCESS)
        {
          /* Return an I/O error to FileX.  */
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
          break;
        }
      }

      /* Open the NAND flash instance using LevelX */
      status = lx_nand_flash_open_extended(nand_flash_context->stm32_lx_nand_flash_handle, "nand flash",

                                           nand_flash_context->stm32_lx_nand_flash_driver_init,

                                           nand_flash_context->stm32_lx_nand_flash_driver_context,

                                           nand_flash_context->stm32_lx_nand_driver_buffer,

                                           nand_flash_context->stm32_lx_nand_driver_buffer_size);

      /* LevelX driver correctly initialized */
      if (status == LX_SUCCESS)
      {
        media_ptr->fx_media_driver_status = FX_SUCCESS;
        media_ptr->fx_media_driver_free_sector_update = FX_TRUE;
      }
      else
      {
        /* Return an I/O error to FileX.  */
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
      }
      break;
    }
  case FX_DRIVER_UNINIT:
    {
      /* Successful driver */
      status = lx_nand_flash_close(nand_flash_context->stm32_lx_nand_flash_handle);
      if (status == LX_SUCCESS)
      {
        media_ptr->fx_media_driver_status =  FX_SUCCESS;
      }
      else
      {
        /* Return an I/O error to FileX. */
        media_ptr->fx_media_driver_status =  FX_IO_ERROR;
      }
      break;
    }
  case FX_DRIVER_READ:
    {
      /* Setup the destination buffer and logical sector.  */
      logical_sector = media_ptr->fx_media_driver_logical_sector;
      /* Loop to read sectors from flash.  */
      for (ULONG i = 0; i < media_ptr->fx_media_driver_sectors; i++)
      {
        /* Read a sector from NAND flash.  */
        status =  lx_nand_flash_sectors_read(nand_flash_context->stm32_lx_nand_flash_handle, logical_sector+i, media_ptr->fx_media_driver_buffer, 1);
        /* Determine if the read was successful.  */
        if (status != LX_SUCCESS)
        {
          /* Return an I/O error to FileX.  */
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
          return;
        }
        /* Move to the next entries.  */
        media_ptr->fx_media_driver_buffer = media_ptr->fx_media_driver_buffer + media_ptr->fx_media_bytes_per_sector;
      }
      /* Successful driver request.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }
  case FX_DRIVER_BOOT_READ:
    {
      /* Read boot sector from NAND flash.  */
      status =  lx_nand_flash_sectors_read(nand_flash_context->stm32_lx_nand_flash_handle, 0, media_ptr->fx_media_driver_buffer,1);
      /* Determine if the boot sector read was successful.  */
      if (status != LX_SUCCESS)
      {
        /* Return an I/O error to FileX.  */
        media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
        return;
      }
      /* Successful driver request.  */
      media_ptr -> fx_media_driver_status =  FX_SUCCESS;
      break;
    }
  case FX_DRIVER_WRITE:
    {
      /* Setup the source buffer and logical sector.  */
      logical_sector = media_ptr->fx_media_driver_logical_sector;
      /* Loop to write the requested number sectors to NAND flash.  */
      for (ULONG i = 0; i < media_ptr->fx_media_driver_sectors; i++)
      {
        /* Write a sector to NAND flash.  */
        status =  lx_nand_flash_sectors_write(nand_flash_context->stm32_lx_nand_flash_handle, logical_sector+i, media_ptr->fx_media_driver_buffer, 1);
        /* Determine if the write was successful.  */
        if (status != LX_SUCCESS)
        {
          /* Return an I/O error to FileX.  */
          media_ptr->fx_media_driver_status =  FX_IO_ERROR;
          return;
        }
        media_ptr->fx_media_driver_buffer =  media_ptr->fx_media_driver_buffer + media_ptr->fx_media_bytes_per_sector;
      }
      /* Successful driver request.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }
  case FX_DRIVER_BOOT_WRITE:
    {
      /* Write boot sector to NAND flash.  */
      status =  lx_nand_flash_sectors_write(nand_flash_context->stm32_lx_nand_flash_handle, 0, media_ptr->fx_media_driver_buffer, 1);
      /* Determine if the boot write was successful.  */
      if (status != LX_SUCCESS)
      {
        /* Return an I/O error to FileX.  */
        media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
      }
      /* Successful driver request.  */
      media_ptr -> fx_media_driver_status =  FX_SUCCESS;
      break ;
    }
  case FX_DRIVER_RELEASE_SECTORS:
    {
      /* Setup the logical sector.  */
      logical_sector =  media_ptr->fx_media_driver_logical_sector;
      /* Release sectors.  */
      for (ULONG i = 0; i < media_ptr->fx_media_driver_sectors; i++)
      {
        /* Release NAND flash sector.  */
        status = lx_nand_flash_sectors_release(nand_flash_context->stm32_lx_nand_flash_handle, logical_sector + i, 1);
        /* Determine if the sector release was successful.  */
        if (status != LX_SUCCESS)
        {
          /* Return an I/O error to FileX.  */
          media_ptr->fx_media_driver_status = FX_IO_ERROR;
          break;
        }
      }
      /* Successful driver request.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }
  case FX_DRIVER_FLUSH:
    {
      /* Return driver success.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }
  case FX_DRIVER_ABORT:
    {
      /* Return driver success.  */
      media_ptr->fx_media_driver_status =  FX_SUCCESS;
      break;
    }
  default:
    {
      /* Invalid driver request.  */
      media_ptr->fx_media_driver_status =  FX_IO_ERROR;
      break;
    }
  }
}
