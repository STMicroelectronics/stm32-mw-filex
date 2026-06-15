

# Release Notes for
# <mark>FileX SW Pack</mark>


# Purpose

STM32Cube enables developers to achieve design success. With a comprehensive suite of professional development tools and embedded software components, STM32Cube allows developers to differentiate products, streamline design cycles, and reduce costs. STM32Cube ecosystem supports all design steps, including selection, configuration, development, debugging, programming, and monitoring.
The STM32Cube embedded software offer provides ready-to-use software components that can be added to a project. It includes STM32 peripheral driver APIs with two levels of abstraction, middleware, board drivers, and examples. There are several distribution channels, including the STM32CubeMX2 tool, the ST website, and GitHub. All embedded software comes with enhanced online documentation, with flowcharts and user sequences.

**FileX** is a high-performance, FAT-compatible file system middleware for embedded devices.
It provides a configurable set of features via compile-time options and is intended for use with STM32 microcontrollers.
FileX is RTOS-agnostic and can be integrated in bare-metal or RTOS-based applications.
Depending on the selected configuration, this pack may also include **LevelX** components for flash translation and wear leveling.

## Documentation

More  documentation is available at [**FileX SW Pack online documentation**](https://dev.st.com/stm32cube-docs/mw-filex/latest/en/index.html).

# Update history

<label for="collapse-section-2.1.0" aria-hidden="true">__2.1.0 / 12-June-2026__</label>
<div>

## Main changes

Release of FileX SW Pack update:

  - Bug fixing.
  - Miscellaneous update of .config files.

This pack is based on [**FileX V6.4.2 version**](https://github.com/eclipse-threadx/filex/releases/tag/v6.4.2.202503_rel).



## Contents

- **FileX** is RTOS-agnostic (can be used with FreeRTOS or other RTOSs)
- Supports NOR and NAND flash memories
- Supports SD and MMC storage devices

## Known limitations

- Multi-instance (creating multiple interfaces) is not supported.
- Cache is not supported with SD, MMC, NOR, and NAND interfaces.
- When an application uses the local path feature in FileX and stores data outside the FileX thread context, configNUM_THREAD_LOCAL_STORAGE_POINTERS must be increased by 1.

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V9.60.3 + ST-LINK
- MDK-ARM Keil uVision V5.42
- STM32CubeIDE for Visual Studio Code (GCC13 compiler)
- STM32CubeMX2 V1.0.1

## Supported devices and boards

- STM32C5 series

## Backward compatibility

- None

## Dependencies

- STM32C5xx HAL Drivers V2.0.0
- FreeRTOS SW Pack V2.0.0 (required when selecting RTOS mode)
- LevelX SW Pack V2.0.0 (required when selecting NOR/NAND interfaces)

</div>

<label for="collapse-section-2.0.0" aria-hidden="true">__2.0.0 / 13-March-2026__</label>
<div>

## Main changes

First Official release of **FileX SW Pack**.\
This pack is based on [**FileX V6.4.2 version**](https://github.com/eclipse-threadx/filex/releases/tag/v6.4.2.202503_rel).



## Contents

- **FileX** is RTOS-agnostic (can be used with FreeRTOS or other RTOSs)
- Supports NOR and NAND flash memories
- Supports SD and MMC storage devices

## Known limitations

- None

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V9.60.3 + ST-LINK
- MDK-ARM Keil uVision V5.42
- STM32CubeIDE for Visual Studio Code (GCC13 compiler)

## Supported devices and boards

- STM32C5 series

## Backward compatibility

- None

## Dependencies

- STM32C5xx HAL Drivers V2.0.0
- FreeRTOS SW Pack V2.0.0 (required when selecting RTOS mode)
- LevelX SW Pack V2.0.0 (required when selecting NOR/NAND interfaces)

</div>


For complete documentation on STM32 microcontrollers,
visit: [www.st.com/stm32](http://www.st.com/stm32)
<abbr title="Based on template cx566953 version 2.1">Info</abbr>

This release note uses up to date web standards and, for this reason, should not be opened with Internet Explorer but preferably with popular browsers such as Google Chrome, Mozilla Firefox, Opera or Microsoft Edge.