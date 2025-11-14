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
#include "fx_system.h"


/**
* @brief Create a timer object
* @param fx_system_timer: Pointer to timer control block
* @param timer_name: Pointer to timer name
* @param expiration_function: Application expiration function
* @param initial_ticks: Initial expiration ticks
* @retval returns an "FX_SUCCESS" state if the timer is created successfully.
 If the timer is not created, the function returns an error state "FX_PTR_ERROR" instead
*/
UINT fx_os_timer_create(FX_TIMER  *fx_system_timer, const CHAR *timer_name, VOID (*expiration_function) (ULONG), ULONG expiration_input, ULONG initial_ticks)
{
  UINT status;

  /* Return completion status. */
  return status;
}
