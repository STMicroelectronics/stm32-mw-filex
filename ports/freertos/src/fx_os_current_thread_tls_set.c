/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation
 * Copyright (c) 2025 STMicroelectronics
 *
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** FileX Component                                                       */
/**                                                                       */
/**   Directory                                                           */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define FX_SOURCE_CODE

/* Include necessary system files.  */

#include "fx_api.h"


/**
 * @brief Set the local path pointer for the current thread
 * @param VOID* tls_data: Pointer to the local path control block to be set for the current thread
 * @retval None
 */
VOID fx_os_current_thread_tls_set(VOID *tls_data)
{
  vTaskSetThreadLocalStoragePointer(NULL, FX_LOCAL_PATH_TLS_POINTER_INDEX, tls_data);
}
