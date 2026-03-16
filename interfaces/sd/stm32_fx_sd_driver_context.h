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
#ifndef STM32_FX_SD_DRIVER_CONTEXT_H
#define STM32_FX_SD_DRIVER_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "fx_api.h"
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  FX_SD_FLAG_NONE                = 0x00000000U,
  FX_SD_FLAG_CACHE_MAINTENANCE   = 0x00000001U,
  FX_SD_FLAG_SCRATCH_BUFFER      = 0x00000002U,
  FX_SD_FLAG_ALL                 = 0x00000003U,
} STM32_FX_SD_FLAGS;

typedef struct STM32_FX_SD_DRIVER_CONTEXT_STURCT
{
  STM32_FX_SD_FLAGS              flags;
  hal_sd_handle_t                *sd_handle;
  UCHAR                          *scratch_buffer; /* Should be allocated with a size of 512 bytes */
  ULONG                          sd_max_timeout;
#ifndef FX_STANDALONE_ENABLE
  FX_SEMAPHORE                   sd_rx_cplt_semaphore;
  FX_SEMAPHORE                   sd_tx_cplt_semaphore;
#else
  volatile UINT                  sd_rx_cplt;
  volatile UINT                  sd_tx_cplt;
#endif /* FX_STANDALONE_ENABLE */

} STM32_FX_SD_DRIVER_CONTEXT;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* STM32_FX_SD_DRIVER_CONTEXT_H */
