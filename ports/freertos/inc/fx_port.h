/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation
 * Copyright (c) 2024 STMicroelectronics
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
/**   Port Specific                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  PORT SPECIFIC C INFORMATION                            RELEASE        */
/*                                                                        */
/*    fx_port.h                                            FreeRTOS       */
/*                                                           6.4.1        */
/*                                                                        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    STMicroelectronics                                                  */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains data type definitions that make the FileX FAT    */
/*    compatible file system function identically on a variety of         */
/*    different processor architectures.  For example, the byte offset of */
/*    various entries in the boot record, and directory entries are       */
/*    defined in this file.                                               */
/**************************************************************************/

#ifndef FX_PORT_H
#define FX_PORT_H


/* Determine if the optional FileX user define file should be used.  */

#ifdef FX_INCLUDE_USER_DEFINE_FILE


/* Yes, include the user defines in fx_user.h. The defines in this file may
   alternately be defined on the command line.  */

#include "fx_user.h"
#endif

/* Include the FreeRTOS api file.  */

#include "FreeRTOS.h"
#include "task.h"
#if defined (configUSE_RECURSIVE_MUTEXES) && (configUSE_RECURSIVE_MUTEXES == 1)
#include "semphr.h"
#else
#error "configUSE_RECURSIVE_MUTEXES must be defined and set to 1 to use this functionality."
#endif
#if defined (configUSE_TIMERS) && (configUSE_TIMERS == 1)
#include "timers.h"
#else
#error "configUSE_TIMERS must be defined and set to 1 to use this functionality."
#endif

/* Force the undef of "FX_STANDALONE_MODE" to disable it even if it was enabled in the fx_user.h  */

#ifdef FX_STANDALONE_ENABLE
#undef FX_STANDALONE_ENABLE
#endif

/* Define compiler library include files.  */

#include <string.h>
#include <stdint.h>
#include <stdlib.h>


#ifndef VOID_DEFINED
#define VOID_DEFINED
typedef void                                    VOID;
#endif

#ifndef CHAR_DEFINED
#define CHAR_DEFINED
typedef char                                    CHAR;
#endif

#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef char                                    BOOL;
#endif

#ifndef UCHAR_DEFINED
#define UCHAR_DEFINED
typedef unsigned char                           UCHAR;
#endif

#ifndef INT_DEFINED
#define INT_DEFINED
typedef int                                     INT;
#endif

#ifndef UINT_DEFINED
#define UINT_DEFINED
typedef unsigned int                            UINT;
#endif

#ifndef LONG_DEFINED
#define LONG_DEFINED
typedef long                                    LONG;
#endif

#ifndef ULONG_DEFINED
#define ULONG_DEFINED
typedef unsigned long                           ULONG;
#endif

#ifndef SHORT_DEFINED
#define SHORT_DEFINED
typedef short                                   SHORT;
#endif

#ifndef USHORT_DEFINED
#define USHORT_DEFINED
typedef unsigned short                          USHORT;
#endif

#ifndef ULONG64_DEFINED
#define ULONG64_DEFINED
typedef unsigned long long                      ULONG64;
#endif

/* Define basic alignment type used in block and byte pool operations. This data type must
   be at least 32-bits in size and also be large enough to hold a pointer type.  */

#ifndef ALIGN_TYPE_DEFINED
#define ALIGN_TYPE_DEFINED
#define ALIGN_TYPE                              ULONG
#endif


/* Define filex FX_DISABLE_INTS and FX_ENABLE_INTS macro to respectively disable and restore the interrupts.  */

#define FX_INT_SAVE_AREA
#define FX_DISABLE_INTS                         taskDISABLE_INTERRUPTS();
#define FX_RESTORE_INTS                         taskENABLE_INTERRUPTS();

/* Map generic FileX types to FreeRTOS equivalent ones. */

#define FX_MUTEX                                SemaphoreHandle_t
#define FX_TIMER                                TimerHandle_t


/* Define filex FX_PROTECT and FX_UNPROTECT macro to respectively locking and unlocking a Mutex object.  */

#if defined(FX_SINGLE_THREAD)
#define FX_PROTECT
#define FX_UNPROTECT
#else
#define FX_PROTECT                              if (media_ptr -> fx_media_id != FX_MEDIA_ID) return(FX_MEDIA_NOT_OPEN); \
                                                else if (xSemaphoreTakeRecursive(media_ptr -> fx_media_protect, portMAX_DELAY) != pdTRUE) return(FX_MEDIA_NOT_OPEN);
#define FX_UNPROTECT                            xSemaphoreGiveRecursive(media_ptr -> fx_media_protect);
#endif


/* Defines the number of FreeRTOS ticks required to achieve the update rate specified by
   FX_UPDATE_RATE_IN_SECONDS. By default, the FreeRTOS tick rate is 1 kHz (1 millisecond tick interval),
   so the default value for this constant is 1000. If the configTICK_RATE_HZ constant is defined,
   then the value of FX_UPDATE_RATE_IN_TICKS is derived from configTICK_RATE_HZ. */


#ifndef FX_UPDATE_RATE_IN_TICKS
#ifdef configTICK_RATE_HZ
#define FX_UPDATE_RATE_IN_TICKS                 (configTICK_RATE_HZ * FX_UPDATE_RATE_IN_SECONDS)
#endif
#endif

/* Define the error checking logic to check the current state of the scheduler. */

#define FX_CALLER_CHECKING_EXTERNS
#define FX_CALLER_CHECKING_CODE                 if ((xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)) \
                                                { \
                                                  return(FX_CALLER_ERROR); \
                                                }


#ifndef FX_NO_LOCAL_PATH
#if (configNUM_THREAD_LOCAL_STORAGE_POINTERS == 0)
#error "configNUM_THREAD_LOCAL_STORAGE_POINTERS must be configured with a non-zero value to enable this functionality."
#endif
#ifndef FX_LOCAL_PATH_SETUP
#define FX_LOCAL_PATH_SETUP
#endif
#endif

/* Define the index for accessing the TLS(Thread Local Storage) pointer. */

#ifndef FX_LOCAL_PATH_TLS_POINTER_INDEX
#define FX_LOCAL_PATH_TLS_POINTER_INDEX (configNUM_THREAD_LOCAL_STORAGE_POINTERS -1)
#endif


/*  Define filex FX_DISABLE_PREEMPTION and FX_RESTORE_PREEMPTION macro respectively,
 to disable and restore a preemption thread. */

#ifndef FX_SINGLE_THREAD
#define FX_DECLARE_PREEMPTION
#define FX_DISABLE_PREEMPTION                   vTaskSuspendAll();
#define FX_RESTORE_PREEMPTION                   xTaskResumeAll();
#else
#define FX_DISABLE_PREEMPTION
#define FX_RESTORE_PREEMPTION
#endif


/* Define trace macros as 'empty' since trace is not supported in FreeRTOS mode.  */

#define FX_TRACE_OBJECT_REGISTER(t, p, n, a, b)
#define FX_TRACE_OBJECT_UNREGISTER(o)
#define FX_TRACE_IN_LINE_INSERT(i, a, b, c, d, f, g, h)
#define FX_TRACE_EVENT_UPDATE(e, t, i, a, b, c, d)


/* Define the function prototypes. */

VOID fx_os_mutex_delete(FX_MUTEX *mutex);
UINT fx_os_mutex_create(FX_MUTEX *mutex, const CHAR* mutex_name);
UINT fx_os_timer_create(FX_TIMER  *fx_system_timer, const CHAR *timer_name, VOID (*expiration_function) (ULONG), ULONG expiration_input, ULONG initial_ticks);
VOID* fx_os_current_thread_tls_get(VOID);
VOID fx_os_current_thread_tls_set(VOID *tls_data);

/* Define the version ID of FileX.  This may be utilized by the application.  */

#ifdef FX_SYSTEM_INIT
CHAR                            _fx_version_id[] =
                                    "Copyright (c) Microsoft Corporation. All rights reserved.  *  FileX Generic Version 6.4.0 *";
#else
extern  CHAR                    _fx_version_id[];
#endif

#endif

