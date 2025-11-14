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
 * @brief Get the local storage pointer for the current thread
 * @retval VOID*: Pointer to the local storage block for the current thread
 */
VOID* fx_os_current_thread_tls_get(VOID)
{
  return pvTaskGetThreadLocalStoragePointer(NULL, FX_LOCAL_PATH_TLS_POINTER_INDEX);
}
