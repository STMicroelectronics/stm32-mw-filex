

# Middleware FileX Component


![tag](https://img.shields.io/badge/tag-2.0.0-brightgreen.svg)
[![release note](https://img.shields.io/badge/release_note-view_html-gold.svg)](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/stm32-mw-filex/blob/hal2/ST_Release_Notes.html)

## Overview
The FileX middleware component is an STM32-specific fork of the [Eclipse ThreadX FILEX](https://github.com/eclipse-threadx/filex).

FileX provides common file system features, such as formatting media, creating directories and files, and accessing files in read and write modes.

The main purpose of this component is to integrate various media storage devices through STM32 HAL drivers.

## RTOS support

This FileX fork is decoupled from hardcoded RTOS dependencies. The **ports** folder provides a reference implementation based on FreeRTOS™.

## Low level drivers

The **interfaces** folder contains a set of generic, ready-to-use low-level drivers for each storage media type:

| Media type (folder) | Driver flavor | Driver entry point | Description |
|---|---|---|---|
| SD card (`interfaces/sd`) | Polling | `stm32_fx_sd_polling_driver()` | Blocking transfers using the STM32 HAL SD API in polling mode. |
| SD card (`interfaces/sd`) | DMA (RTOS) | `stm32_fx_sd_dma_os_driver()` | DMA-based transfers with RTOS synchronization (uses semaphores for transfer completion).  |
| SD card (`interfaces/sd`) | DMA (No-OS) | `stm32_fx_sd_dma_no_os_driver()` | DMA-based transfers without RTOS objects; waits for transfer completion using polling/timeouts. |
| MMC/eMMC (`interfaces/mmc`) | Polling | `stm32_fx_mmc_polling_driver()` | Blocking transfers using the STM32 HAL MMC API in polling mode. |
| MMC/eMMC (`interfaces/mmc`) | DMA (RTOS) | `stm32_fx_mmc_dma_os_driver()` | DMA-based transfers with RTOS synchronization (uses semaphores for transfer completion).  |
| MMC/eMMC (`interfaces/mmc`) | DMA (No-OS) | `stm32_fx_mmc_dma_no_os_driver()` | DMA-based transfers without RTOS objects; waits for transfer completion using polling/timeouts.|
| NOR flash (`interfaces/nor`) | LevelX NOR | `stm32_fx_nor_flash_driver()` | FileX media driver wrapper on top of LevelX NOR (`lx_nor_flash_*`) for block-based access to NOR flash. |
| NAND flash (`interfaces/nand`) | LevelX NAND | `stm32_fx_nand_flash_driver()` | FileX media driver wrapper on top of LevelX NAND (`lx_nand_flash_*`) for block-based access to NAND flash. |

See `interfaces/readme.txt` for the low-level drivers changelog.
