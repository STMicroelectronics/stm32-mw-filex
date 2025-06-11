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
/*    fx_port.h                                            Generic        */
/*                                                           6.4.1        */
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
/*  28-05-2024     STMicroelectronics       Modified the code             */
/*                                            to be RTOS agnostic support */
/*                                            resulting in version 6.4.1  */
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

/* This port file to be used in standalone mode.
Force the definition of FX_STANDALONE_ENABLE if not already defined in fx_user.h.  */

#ifndef FX_STANDALONE_ENABLE
#define FX_STANDALONE_ENABLE
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


/* Define FileX internal protection macros.  */

#define FX_PROTECT
#define FX_UNPROTECT

/* Add details that there is no lock mechanism in standalone mode.  */

#define FX_INT_SAVE_AREA
#define FX_DISABLE_INTS
#define FX_RESTORE_INTS


/* Details that these macros are not needed in the standalone mode.  */

#define FX_CALLER_CHECKING_EXTERNS
#define FX_CALLER_CHECKING_CODE


/* Define the update rate of the system timer.  These values may also be defined at the command
   line when compiling the fx_system_initialize.c module in the FileX library build.  Alternatively, they can
   be modified in this file or fx_user.h. Note: the update rate must be an even number of seconds greater
   than or equal to 2, which is the minimal update rate for FAT time. */

/* Define the number of seconds the timer parameters are updated in FileX.  The default
   value is 10 seconds.  This value can be overwritten externally. */

#ifndef FX_UPDATE_RATE_IN_SECONDS
#define FX_UPDATE_RATE_IN_SECONDS               10
#endif


/* Defines the number of timer ticks required,so the default value for this constant is 1000.  */

#ifndef FX_UPDATE_RATE_IN_TICKS
#define FX_UPDATE_RATE_IN_TICKS                 1000
#endif

/* Define trace macros as 'empty' since trace is not supported in standalone mode.  */

#define FX_TRACE_OBJECT_REGISTER(t, p, n, a, b)
#define FX_TRACE_OBJECT_UNREGISTER(o)
#define FX_TRACE_IN_LINE_INSERT(i, a, b, c, d, f, g, h)
#define FX_TRACE_EVENT_UPDATE(e, t, i, a, b, c, d)


/* Define the version ID of FileX.  This may be utilized by the application.  */

#ifdef FX_SYSTEM_INIT
CHAR                            _fx_version_id[] =
  "Copyright (c) 2024 Microsoft Corporation.  *  FileX Generic Version 6.4.1 *";
#else
extern  CHAR                    _fx_version_id[];
#endif

#endif

