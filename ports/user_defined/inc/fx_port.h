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
/*    fx_port.h                                            User        */
/*                                                           6.3.0        */
/*                                                                        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains data type definitions that make the FileX FAT    */
/*    compatible file system function identically on a variety of         */
/*    different processor architectures.  For example, the byte offset of */
/*    various entries in the boot record, and directory entries are       */
/*    defined in this file.                                               */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  11-09-2020     William E. Lamie         Initial Version 6.1.2         */
/*  03-02-2021     William E. Lamie         Modified comment(s), and      */
/*                                            added standalone support,   */
/*                                            resulting in version 6.1.5  */
/*  10-31-2023     Xiuwen Cai               Modified comment(s),          */
/*                                            added basic types guards,   */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/

#ifndef FX_PORT_H
#define FX_PORT_H


/* Determine if the optional FileX user define file should be used.  */

#ifdef FX_INCLUDE_USER_DEFINE_FILE


/* Yes, include the user defines in fx_user.h. The defines in this file may 
   alternately be defined on the command line.  */

#include "fx_user.h"
#endif



/* Force the undef of "FX_STANDALONE_MODE" to disable it even if it was enabled in the fx_user.h  */

#ifdef FX_STANDALONE_ENABLE
#undef FX_STANDALONE_ENABLE
#endif

/* Define compiler library include files.  */

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef VOID
#define VOID                                    void
typedef char                                    CHAR;
typedef char                                    BOOL;
typedef unsigned char                           UCHAR;
typedef int                                     INT;
typedef unsigned int                            UINT;
typedef long                                    LONG;
typedef unsigned long                           ULONG;
typedef short                                   SHORT;
typedef unsigned short                          USHORT;
#endif

/* Define ULONG64 typedef, if already defined.  */

#ifdef ULONG64_DEFINED
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
#define FX_DISABLE_INTS
#define FX_RESTORE_INTS

/* Map generic FileX types to RTOS equivalent ones. */

#define FX_MUTEX
#define FX_TIMER


/* Define filex FX_PROTECT and FX_UNPROTECT macro to respectively locking and unlocking a Mutex object.  */

#if defined(FX_SINGLE_THREAD)
#define FX_PROTECT
#define FX_UNPROTECT
#else
#define FX_PROTECT                               /* Define mutex object lock definition */                               
#define FX_UNPROTECT                             /* Define mutex object unlock definition */       
#endif


/* Defines the number of RTOS ticks required to achieve the update rate specified by
   FX_UPDATE_RATE_IN_SECONDS. */

#ifndef FX_UPDATE_RATE_IN_TICKS
#ifdef configTICK_RATE_HZ
#define FX_UPDATE_RATE_IN_TICKS                 
#endif
#endif

/* Define the error checking logic to check the current state of the scheduler. */

#define FX_CALLER_CHECKING_EXTERNS
#define FX_CALLER_CHECKING_CODE

/* Define the support of 'LOCAL_PATH' */

#ifndef FX_NO_LOCAL_PATH
#define FX_NO_LOCAL_PATH
#endif


/*  Define filex FX_DISABLE_PREEMPTION and FX_RESTORE_PREEMPTION macro respectively,
 to disable and restore a preemption thread. */

#ifndef FX_SINGLE_THREAD
#define FX_DECLARE_PREEMPTION
#define FX_DISABLE_PREEMPTION
#define FX_RESTORE_PREEMPTION
#else
#define FX_DISABLE_PREEMPTION
#define FX_RESTORE_PREEMPTION
#endif


/* Define trace macros */

#define FX_TRACE_OBJECT_REGISTER(t, p, n, a, b)
#define FX_TRACE_OBJECT_UNREGISTER(o)
#define FX_TRACE_IN_LINE_INSERT(i, a, b, c, d, f, g, h)
#define FX_TRACE_EVENT_UPDATE(e, t, i, a, b, c, d)


/* Define the function prototypes. */

VOID fx_os_mutex_delete(FX_MUTEX *mutex);
UINT fx_os_mutex_create(FX_MUTEX *mutex, const CHAR* mutex_name);
UINT fx_os_timer_create(FX_TIMER  *fx_system_timer, const CHAR *timer_name, VOID (*expiration_function) (ULONG), ULONG expiration_input, ULONG initial_ticks);

/* Define the version ID of FileX.  This may be utilized by the application.  */

#ifdef FX_SYSTEM_INIT
CHAR                            _fx_version_id[] =
                                    "Copyright (c) Microsoft Corporation. All rights reserved.  *  FileX Generic Version 6.4.0 *";
#else
extern  CHAR                    _fx_version_id[];
#endif

#endif

