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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FX_STM32_NOR_FLASH_DRIVER_CONTEXT_H
#define FX_STM32_NOR_FLASH_DRIVER_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "fx_api.h"
#include "lx_api.h"
/* Exported types ------------------------------------------------------------*/

typedef enum
{
  STM32_FX_NOR_FLAG_NONE                   = 0x00000000,

  STM32_FX_NOR_FLAG_FORMAT_ON_INIT         = 0x00000001,

  STM32_FX_NOR_FLAG_ALL                    = 0x00000002,
} STM32_FX_NOR_FLASH_DRIVER_FLAGS;

typedef struct STM32_FX_NOR_FLASH_DRIVER_CONTEXT_STURCT
{
  STM32_FX_NOR_FLASH_DRIVER_FLAGS      stm32_fx_nor_flash_flags;
  LX_NOR_FLASH                         *stm32_lx_nor_flash_handle;
  CHAR                                  stm32_lx_nor_flash_name[16];
  UINT                                 (*stm32_lx_nor_flash_driver_init)(LX_NOR_FLASH *);
  VOID                                 *stm32_lx_nor_flash_driver_context;
#ifndef LX_NOR_DISABLE_EXTENDED_CACHE
  VOID                                 *extended_cache_memory;
  ULONG                                 extended_cache_memory_size;
#endif
} STM32_FX_NOR_FLASH_DRIVER_CONTEXT;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* FX_STM32_NOR_FLASH_DRIVER_CONTEXT_H */
