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
* @brief Delete a mutex object
* @param mutex: Pointer to mutex control block
* @retval None
*/
VOID fx_os_mutex_delete(FX_MUTEX *mutex)
{
    if (mutex != FX_NULL)
    {
        if (mutex->mutex_handle != FX_NULL)
        {
#if (configQUEUE_REGISTRY_SIZE > 0)
            vQueueUnregisterQueue((QueueHandle_t) mutex->mutex_handle);
#endif
            /* Call FreeRTOS to delete the Mutex object. */
            vSemaphoreDelete(mutex->mutex_handle);

            /* Reset the mutex handle */
            mutex->mutex_handle = 0U;
        }
    }
}
