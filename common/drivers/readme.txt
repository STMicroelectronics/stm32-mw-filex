/**
  ******************************************************************************
  * @file    readme.txt
  * @author  MCD Application Team
  * @brief   This file lists the main changes done by STMicroelectronics on
  *          FileX low level drivers for STM32 devices.
  ******************************************************************************
  */

### V6.4.1 (11-08-2025) ###
=================================
Main changes
-------------
- Deliver first release of Eclipse-ThreadX FileX low level drivers for STM32 MCU series
   + fx_stm32_levelx_nand_driver.c
   + fx_stm32_levelx_nor_driver.c
   + fx_stm32_mmc_driver.c
   + fx_stm32_sd_driver.c
   + fx_stm32_sram_driver.c
   + template/fx_stm32_driver.c
   + template/fx_stm32_driver.h
   + template/fx_stm32_levelx_nand_driver.h
   + template/fx_stm32_levelx_nor_driver.h
   + template/fx_stm32_mmc_driver.h
   + template/fx_stm32_mmc_driver_glue.c
   + template/fx_stm32_sd_driver.h
   + template/fx_stm32_sd_driver_dma_rtos.h
   + template/fx_stm32_sd_driver_dma_standalone.h
   + template/fx_stm32_sd_driver_glue.c
   + template/fx_stm32_sd_driver_glue_dma_rtos.c
   + template/fx_stm32_sd_driver_glue_dma_standalone.c
   + template/fx_stm32_sram_driver.h

- Update low-level driver templates to work with FreeRTOS
   + template/fx_stm32_sd_driver_glue_dma_rtos.c
   + template/fx_stm32_sd_driver_dma_rtos.h

- Fix SA0038 security issue (Buffer overflow issue in FileX STM32 RAM driver)
   + fx_stm32_sram_driver.c
