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
#ifndef STM32_FX_MMC_DMA_DRIVER_OS_H
#define STM32_FX_MMC_DMA_DRIVER_OS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_fx_mmc_driver_context.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
VOID  stm32_fx_mmc_dma_os_driver(FX_MEDIA *media_ptr);

/* Private defines -----------------------------------------------------------*/
#if defined (USE_HAL_MMC_USER_DATA) && (USE_HAL_MMC_USER_DATA == 0)
#error "USE_HAL_MMC_USER_DATA must be defined and set to 1 to use this functionality."
#endif /* USE_HAL_MMC_USER_DATA */

#ifdef __cplusplus
}
#endif

#endif /* STM32_FX_MMC_DMA_DRIVER_OS_H */