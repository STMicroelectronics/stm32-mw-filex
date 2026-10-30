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

/* Private includes ----------------------------------------------------------*/
#include "stm32_fx_driver.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

VOID  fx_stm32_custom_driver(FX_MEDIA *media_ptr)
{
  switch (media_ptr->fx_media_driver_request)
  {
    case FX_DRIVER_INIT:
    {

      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_UNINIT:
    {

      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_BOOT_READ:
    {

      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_READ:
    {
      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_BOOT_WRITE:
    {

      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_WRITE:
    {
      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_FLUSH:
    {
      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    case FX_DRIVER_ABORT:
    {
      media_ptr->fx_media_driver_status = FX_SUCCESS;

      break;
    }

    default:
    {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        break;
    }
  }
}
