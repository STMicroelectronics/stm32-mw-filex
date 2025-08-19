  /**
  ******************************************************************************
  * @file    st_readme.txt
  * @author  GPM Application Team
  * @brief   This file lists the main changes done by STMicroelectronics on
  *          FileX for STM32 devices.
  ******************************************************************************
  */

### V6.4.1 (11-08-2025) ###
=================================
- SA0038 issue is fixed (Buffer overflow issue in FileX STM32 RAM driver)

### V6.4.1 (30-05-2025) ###
=========================
- Implement RTOS agnostic capabilities to support FreeRTOS and standalone modes:
  - Add fx_port.h to the ports/freertos/inc directory.
  - Remove all macros related to ThreadX from fx_api.h.
  - Move all macros related to ThreadX from fx_port.h located under ports/generic/inc to fx_port.h located under ports/threadx/inc.
  - Add APIs for the creation of mutexes and timers in the following files under the ports/freertos/src directory:
     * fx_os_mutex_create.c
     * fx_os_mutex_delete.c
     * fx_os_timer_create.c
- Add FileX 6.4.1 from Eclipse ThreadX
