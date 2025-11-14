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
* @brief Create a mutex object
* @param mutex: Pointer to mutex control block
* @param mutex_name: Pointer to mutex name
* @retval returns an "FX_SUCCESS" state if the mutex is created successfully.
 If the mutex is not created, the function returns an error state "FX_PTR_ERROR" instead
*/
UINT fx_os_mutex_create(FX_MUTEX *mutex, const CHAR* mutex_name)
{
    if (mutex != NULL)
    {
        /* Call FreeRTOS to create the Mutex object.  */
        mutex->mutex_handle = xSemaphoreCreateRecursiveMutex();

        if (mutex->mutex_handle == NULL)
        {
            return FX_PTR_ERROR;
        }

#if (configQUEUE_REGISTRY_SIZE > 0)
        if ((mutex_name != NULL))
        {
            vQueueAddToRegistry((QueueHandle_t) mutex->mutex_handle, mutex_name);
        }
#endif

    }
    else
    {
        return FX_PTR_ERROR;
    }
    return FX_SUCCESS;
}

