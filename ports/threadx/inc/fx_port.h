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
/*    fx_port.h                                            ThreadX        */
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


/* Include the ThreadX api file.  */

#include "tx_api.h"


/* Force the undef of "FX_STANDALONE_MODE" to disable it even if it was enabled in the fx_user.h  */

#ifdef FX_STANDALONE_ENABLE
#undef FX_STANDALONE_ENABLE
#endif

/* Define FileX internal protection macros.  If FX_SINGLE_THREAD is defined,
   these protection macros are effectively disabled.  However, for multi-thread
   uses, the macros are setup to utilize a ThreadX mutex for multiple thread
   access control into an open media.  */

#if defined(FX_SINGLE_THREAD)
#define FX_PROTECT
#define FX_UNPROTECT
#else
#define FX_PROTECT                      if (media_ptr -> fx_media_id != FX_MEDIA_ID) return(FX_MEDIA_NOT_OPEN); \
                                        else if (tx_mutex_get(&(media_ptr -> fx_media_protect), TX_WAIT_FOREVER) != TX_SUCCESS) return(FX_MEDIA_NOT_OPEN);
#define FX_UNPROTECT                    tx_mutex_put(&(media_ptr -> fx_media_protect));
#endif


/* Override the interrupt protection provided in FileX port files to simply use ThreadX protection,
   which is often in-line assembly.  */

#ifndef FX_LEGACY_INTERRUPT_PROTECTION
#undef  FX_INT_SAVE_AREA
#undef  FX_DISABLE_INTS
#undef  FX_RESTORE_INTS
#define FX_INT_SAVE_AREA    TX_INTERRUPT_SAVE_AREA
#define FX_DISABLE_INTS     TX_DISABLE
#define FX_RESTORE_INTS     TX_RESTORE
#endif

/* Define interrupt lockout constructs to protect the system date/time from being updated
   while they are being read.  */
#ifndef FX_INT_SAVE_AREA
#define FX_INT_SAVE_AREA                unsigned int  old_interrupt_posture;
#endif

#ifndef FX_DISABLE_INTS
#define FX_DISABLE_INTS                 old_interrupt_posture =  tx_interrupt_control(TX_INT_DISABLE);
#endif

#ifndef FX_RESTORE_INTS
#define FX_RESTORE_INTS                 tx_interrupt_control(old_interrupt_posture);
#endif


/* Define the error checking logic to determine if there is a caller error in the FileX API.
   The default definitions assume ThreadX is being used.  This code can be completely turned
   off by just defining these macros to white space.  */


#ifndef TX_TIMER_PROCESS_IN_ISR

#define FX_CALLER_CHECKING_EXTERNS      extern  FX_THREAD      *_tx_thread_current_ptr; \
                                        extern  FX_THREAD       _tx_timer_thread; \
                                        extern  volatile ULONG  _tx_thread_system_state;

#define FX_CALLER_CHECKING_CODE         if ((TX_THREAD_GET_SYSTEM_STATE()) || \
                                            (_tx_thread_current_ptr == TX_NULL) || \
                                            (_tx_thread_current_ptr == &_tx_timer_thread)) \
                                            return(FX_CALLER_ERROR);

#else
#define FX_CALLER_CHECKING_EXTERNS      extern  FX_THREAD      *_tx_thread_current_ptr; \
                                        extern  volatile ULONG  _tx_thread_system_state;

#define FX_CALLER_CHECKING_CODE         if ((TX_THREAD_GET_SYSTEM_STATE()) || \
                                            (_tx_thread_current_ptr == TX_NULL)) \
                                            return(FX_CALLER_ERROR);
#endif


/* Disable ThreadX error checking for internal FileX source code.  */

#ifdef FX_SOURCE_CODE
#ifndef TX_DISABLE_ERROR_CHECKING
#define TX_DISABLE_ERROR_CHECKING
#endif
#endif

/* Define the update rate of the system timer.  These values may also be defined at the command
   line when compiling the fx_system_initialize.c module in the FileX library build.  Alternatively, they can
   be modified in this file or fx_user.h. Note: the update rate must be an even number of seconds greater
   than or equal to 2, which is the minimal update rate for FAT time. */

/* Define the number of seconds the timer parameters are updated in FileX.  The default
   value is 10 seconds.  This value can be overwritten externally. */

#ifndef FX_UPDATE_RATE_IN_SECONDS
#define FX_UPDATE_RATE_IN_SECONDS 10
#endif


/* Defines the number of ThreadX timer ticks required to achieve the update rate specified by
   FX_UPDATE_RATE_IN_SECONDS defined previously. By default, the ThreadX timer tick is 10ms,
   so the default value for this constant is 1000.  If TX_TIMER_TICKS_PER_SECOND is defined,
   this value is derived from TX_TIMER_TICKS_PER_SECOND.  */

#ifndef FX_UPDATE_RATE_IN_TICKS
#if defined(TX_TIMER_TICKS_PER_SECOND)
#define FX_UPDATE_RATE_IN_TICKS         (TX_TIMER_TICKS_PER_SECOND * FX_UPDATE_RATE_IN_SECONDS)
#else
#define FX_UPDATE_RATE_IN_TICKS         1000
#endif
#endif


/* Map generic FileX types to ThreadX equivalent ones. */
#define FX_MUTEX                 TX_MUTEX
#define FX_THREAD                TX_THREAD
#define FX_TIMER                 TX_TIMER


/* Determine if local paths are enabled and if the local path setup code has not been defined.
   If so, define the default local path setup code for files that reference the local path.  */

#ifndef FX_NO_LOCAL_PATH
#ifndef FX_LOCAL_PATH_SETUP
#ifndef FX_SINGLE_THREAD
#define FX_LOCAL_PATH_SETUP     extern FX_THREAD *_tx_thread_current_ptr;
#else
#define FX_NO_LOCAL_PATH
#endif
#endif
#endif
/* Determine if tracing is enabled.  */

#if defined(TX_ENABLE_EVENT_TRACE)


/* Trace is enabled. Remap calls so that interrupts can be disabled around the actual event logging.  */

#include "tx_trace.h"


/* Define the object types in FileX, if not defined.  */

#ifndef FX_TRACE_OBJECT_TYPE_MEDIA
#define FX_TRACE_OBJECT_TYPE_MEDIA                      9               /* P1 = FAT cache size, P2 = sector cache size       */
#define FX_TRACE_OBJECT_TYPE_FILE                       10              /* none                                              */
#endif


/* Define event filters that can be used to selectively disable certain events or groups of events.  */

#define FX_TRACE_ALL_EVENTS                             0x00007800      /* All FileX events                          */
#define FX_TRACE_INTERNAL_EVENTS                        0x00000800      /* FileX internal events                     */
#define FX_TRACE_MEDIA_EVENTS                           0x00001000      /* FileX media events                        */
#define FX_TRACE_DIRECTORY_EVENTS                       0x00002000      /* FileX directory events                    */
#define FX_TRACE_FILE_EVENTS                            0x00004000      /* FileX file events                         */


/* Define the trace events in FileX, if not defined.  */

/* Define FileX Trace Events, along with a brief description of the additional information fields,
   where I1 -> Information Field 1, I2 -> Information Field 2, etc.  */

/* Define the FileX internal events first.  */

#ifndef FX_TRACE_INTERNAL_LOG_SECTOR_CACHE_MISS
#define FX_TRACE_INTERNAL_LOG_SECTOR_CACHE_MISS         201             /* I1 = media ptr, I2 = sector, I3 = total misses, I4 = cache size          */
#define FX_TRACE_INTERNAL_DIR_CACHE_MISS                202             /* I1 = media ptr, I2 = total misses                                        */
#define FX_TRACE_INTERNAL_MEDIA_FLUSH                   203             /* I1 = media ptr, I2 = dirty sectors                                       */
#define FX_TRACE_INTERNAL_DIR_ENTRY_READ                204             /* I1 = media ptr                                                           */
#define FX_TRACE_INTERNAL_DIR_ENTRY_WRITE               205             /* I1 = media ptr                                                           */
#define FX_TRACE_INTERNAL_IO_DRIVER_READ                206             /* I1 = media ptr, I2 = sector, I3 = number of sectors, I4 = buffer         */
#define FX_TRACE_INTERNAL_IO_DRIVER_WRITE               207             /* I1 = media ptr, I2 = sector, I3 = number of sectors, I4 = buffer         */
#define FX_TRACE_INTERNAL_IO_DRIVER_FLUSH               208             /* I1 = media ptr                                                           */
#define FX_TRACE_INTERNAL_IO_DRIVER_ABORT               209             /* I1 = media ptr                                                           */
#define FX_TRACE_INTERNAL_IO_DRIVER_INIT                210             /* I1 = media ptr                                                           */
#define FX_TRACE_INTERNAL_IO_DRIVER_BOOT_READ           211             /* I1 = media ptr, I2 = buffer                                              */
#define FX_TRACE_INTERNAL_IO_DRIVER_RELEASE_SECTORS     212             /* I1 = media ptr, I2 = sector, I3 = number of sectors                      */
#define FX_TRACE_INTERNAL_IO_DRIVER_BOOT_WRITE          213             /* I1 = media ptr, I2 = buffer                                              */
#define FX_TRACE_INTERNAL_IO_DRIVER_UNINIT              214             /* I1 = media ptr                                                           */


/* Define the FileX API events.  */

#define FX_TRACE_DIRECTORY_ATTRIBUTES_READ              220             /* I1 = media ptr, I2 = directory name, I3 = attributes                     */
#define FX_TRACE_DIRECTORY_ATTRIBUTES_SET               221             /* I1 = media ptr, I2 = directory name, I3 = attributes                     */
#define FX_TRACE_DIRECTORY_CREATE                       222             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_DEFAULT_GET                  223             /* I1 = media ptr, I2 = return path name                                    */
#define FX_TRACE_DIRECTORY_DEFAULT_SET                  224             /* I1 = media ptr, I2 = new path name                                       */
#define FX_TRACE_DIRECTORY_DELETE                       225             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_FIRST_ENTRY_FIND             226             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_FIRST_FULL_ENTRY_FIND        227             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_INFORMATION_GET              228             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_LOCAL_PATH_CLEAR             229             /* I1 = media ptr                                                           */
#define FX_TRACE_DIRECTORY_LOCAL_PATH_GET               230             /* I1 = media ptr, I2 = return path name                                    */
#define FX_TRACE_DIRECTORY_LOCAL_PATH_RESTORE           231             /* I1 = media ptr, I2 = local path ptr                                      */
#define FX_TRACE_DIRECTORY_LOCAL_PATH_SET               232             /* I1 = media ptr, I2 = local path ptr, I3 = new path name                  */
#define FX_TRACE_DIRECTORY_LONG_NAME_GET                233             /* I1 = media ptr, I2 = short file name, I3 = long file name                */
#define FX_TRACE_DIRECTORY_NAME_TEST                    234             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_NEXT_ENTRY_FIND              235             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_NEXT_FULL_ENTRY_FIND         236             /* I1 = media ptr, I2 = directory name                                      */
#define FX_TRACE_DIRECTORY_RENAME                       237             /* I1 = media ptr, I2 = old directory name, I3 = new directory name         */
#define FX_TRACE_DIRECTORY_SHORT_NAME_GET               238             /* I1 = media ptr, I2 = long file name, I3 = short file name                */
#define FX_TRACE_FILE_ALLOCATE                          239             /* I1 = file ptr, I2 = size I3 = previous size, I4 = new size               */
#define FX_TRACE_FILE_ATTRIBUTES_READ                   240             /* I1 = media ptr, I2 = file name, I3 = attributes                          */
#define FX_TRACE_FILE_ATTRIBUTES_SET                    241             /* I1 = media ptr, I2 = file name, I3 = attributes                          */
#define FX_TRACE_FILE_BEST_EFFORT_ALLOCATE              242             /* I1 = file ptr, I2 = size, I3 = actual_size_allocated                     */
#define FX_TRACE_FILE_CLOSE                             243             /* I1 = file ptr, I3 = file size                                            */
#define FX_TRACE_FILE_CREATE                            244             /* I1 = media ptr, I2 = file name                                           */
#define FX_TRACE_FILE_DATE_TIME_SET                     245             /* I1 = media ptr, I2 = file name, I3 = year, I4 = month                    */
#define FX_TRACE_FILE_DELETE                            246             /* I1 = media ptr, I2 = file name                                           */
#define FX_TRACE_FILE_OPEN                              247             /* I1 = media ptr, I2 = file ptr, I3 = file name, I4 = open type            */
#define FX_TRACE_FILE_READ                              248             /* I1 = file ptr, I2 = buffer ptr, I3 = request size I4 = actual size       */
#define FX_TRACE_FILE_RELATIVE_SEEK                     249             /* I1 = file ptr, I2 = byte offset, I3 = seek from, I4 = previous offset    */
#define FX_TRACE_FILE_RENAME                            250             /* I1 = media ptr, I2 = old file name, I3 = new file name                   */
#define FX_TRACE_FILE_SEEK                              251             /* I1 = file ptr, I2 = byte offset, I3 = previous offset                    */
#define FX_TRACE_FILE_TRUNCATE                          252             /* I1 = file ptr, I2 = size, I3 = previous size, I4 = new size              */
#define FX_TRACE_FILE_TRUNCATE_RELEASE                  253             /* I1 = file ptr, I2 = size, I3 = previous size, I4 = new size              */
#define FX_TRACE_FILE_WRITE                             254             /* I1 = file ptr, I2 = buffer ptr, I3 = size, I4 = bytes written            */
#define FX_TRACE_MEDIA_ABORT                            255             /* I1 = media ptr                                                           */
#define FX_TRACE_MEDIA_CACHE_INVALIDATE                 256             /* I1 = media ptr                                                           */
#define FX_TRACE_MEDIA_CHECK                            257             /* I1 = media ptr, I2 = scratch memory, I3 = scratch memory size, I4 =errors*/
#define FX_TRACE_MEDIA_CLOSE                            258             /* I1 = media ptr                                                           */
#define FX_TRACE_MEDIA_FLUSH                            259             /* I1 = media ptr                                                           */
#define FX_TRACE_MEDIA_FORMAT                           260             /* I1 = media ptr, I2 = root entries, I3 = sectors, I4 = sectors per cluster*/
#define FX_TRACE_MEDIA_OPEN                             261             /* I1 = media ptr, I2 = media driver, I3 = memory ptr, I4 = memory size     */
#define FX_TRACE_MEDIA_READ                             262             /* I1 = media ptr, I2 = logical sector, I3 = buffer ptr, I4 = bytes read    */
#define FX_TRACE_MEDIA_SPACE_AVAILABLE                  263             /* I1 = media ptr, I2 = available bytes ptr, I3 = available clusters        */
#define FX_TRACE_MEDIA_VOLUME_GET                       264             /* I1 = media ptr, I2 = volume name, I3 = volume source                     */
#define FX_TRACE_MEDIA_VOLUME_SET                       265             /* I1 = media ptr, I2 = volume name                                         */
#define FX_TRACE_MEDIA_WRITE                            266             /* I1 = media ptr, I2 = logical_sector, I3 = buffer_ptr, I4 = byte written  */
#define FX_TRACE_SYSTEM_DATE_GET                        267             /* I1 = year, I2 = month, I3 = day                                          */
#define FX_TRACE_SYSTEM_DATE_SET                        268             /* I1 = year, I2 = month, I3 = day                                          */
#define FX_TRACE_SYSTEM_INITIALIZE                      269             /* None                                                                     */
#define FX_TRACE_SYSTEM_TIME_GET                        270             /* I1 = hour, I2 = minute, I3 = second                                      */
#define FX_TRACE_SYSTEM_TIME_SET                        271             /* I1 = hour, I2 = minute, I3 = second                                      */
#define FX_TRACE_UNICODE_DIRECTORY_CREATE               272             /* I1 = media ptr, I2 = source unicode, I3 = source length, I4 = short_name */
#define FX_TRACE_UNICODE_DIRECTORY_RENAME               273             /* I1 = media ptr, I2 = source unicode, I3 = source length, I4 = new_name   */
#define FX_TRACE_UNICODE_FILE_CREATE                    274             /* I1 = media ptr, I2 = source unicode, I3 = source length, I4 = short name */
#define FX_TRACE_UNICODE_FILE_RENAME                    275             /* I1 = media ptr, I2 = source unicode, I3 = source length, I4 = new name   */
#define FX_TRACE_UNICODE_LENGTH_GET                     276             /* I1 = unicode name, I2 = length                                           */
#define FX_TRACE_UNICODE_NAME_GET                       277             /* I1 = media ptr, I2 = source short name, I3 = unicode name, I4 = length   */
#define FX_TRACE_UNICODE_SHORT_NAME_GET                 278             /* I1 = media ptr, I2 = source unicode name, I3 = length, I4 =  short name  */
#endif


/* Map the trace macros to internal FileX versions so we can get interrupt protection.  */

#ifdef FX_SOURCE_CODE

#define FX_TRACE_OBJECT_REGISTER(t, p, n, a, b)         _fx_trace_object_register(t, (VOID *)p, (CHAR *)n, (ULONG)a, (ULONG)b);
#define FX_TRACE_OBJECT_UNREGISTER(o)                   _fx_trace_object_unregister((VOID *)o);
#define FX_TRACE_IN_LINE_INSERT(i, a, b, c, d, f, g, h) _fx_trace_event_insert((ULONG)i, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)d, (ULONG)f, g, h);
#define FX_TRACE_EVENT_UPDATE(e, t, i, a, b, c, d)      _fx_trace_event_update((TX_TRACE_BUFFER_ENTRY *)e, (ULONG)t, (ULONG)i, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)d);


/* Define FileX trace prototypes.  */

VOID _fx_trace_object_register(UCHAR object_type, VOID *object_ptr, CHAR *object_name, ULONG parameter_1, ULONG parameter_2);
VOID _fx_trace_object_unregister(VOID *object_ptr);
VOID _fx_trace_event_insert(ULONG event_id, ULONG info_field_1, ULONG info_field_2, ULONG info_field_3, ULONG info_field_4, ULONG filter, TX_TRACE_BUFFER_ENTRY **current_event, ULONG *current_timestamp);
VOID _fx_trace_event_update(TX_TRACE_BUFFER_ENTRY *event, ULONG timestamp, ULONG event_id, ULONG info_field_1, ULONG info_field_2, ULONG info_field_3, ULONG info_field_4);

#endif

#else /* defined(TX_ENABLE_EVENT_TRACE) */
#define FX_TRACE_OBJECT_REGISTER(t, p, n, a, b)
#define FX_TRACE_OBJECT_UNREGISTER(o)
#define FX_TRACE_IN_LINE_INSERT(i, a, b, c, d, f, g, h)
#define FX_TRACE_EVENT_UPDATE(e, t, i, a, b, c, d)
#endif


/* Define the version ID of FileX.  This may be utilized by the application.  */

#ifdef FX_SYSTEM_INIT
CHAR                            _fx_version_id[] =
                                    "Copyright (c) Microsoft Corporation. All rights reserved.  *  FileX Generic Version 6.4.0 *";
#else
extern  CHAR                    _fx_version_id[];
#endif

#endif

