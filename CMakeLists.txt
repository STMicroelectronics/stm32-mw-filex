# origin-pack: STMicroelectronics::filex@2.0.0
# file-format: 1.0.0
project(STMicroelectronics_filex_2_0_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_filex_2_0_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_filex_2_0_0)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:Core#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:No_OS#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:Fault Tolerance Support#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:sd_polling_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:sd_dma_os_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:sd_dma_no_os_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:nor_flash_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:nand_flash_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:mmc_polling_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:mmc_dma_os_itf#Cversion:6.4.2")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:mmc_dma_no_os_itf#Cversion:6.4.2")
endif()

# All conditions used by this package

# condition: STMicroelectronics.filex.2.0.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.filex.2.0.0 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0 enabled")
else()
  set(STMicroelectronics.filex.2.0.0 0)
endif()


# condition: STMicroelectronics.filex.2.0.0:FX Core Condition
# description: FX common condition :dependency to FileX Core
set(STMicroelectronics.filex.2.0.0_FX_Core_Condition "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:File System#.*Cgroup:FileX#.*Csub:Core(#.*|$)>,>>")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_FX_Core_Condition enabled")


# condition: STMicroelectronics.filex.2.0.0:Operating System Used
# description: 
set(STMicroelectronics.filex.2.0.0_Operating_System_Used "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_Operating_System_Used enabled")


# condition: STMicroelectronics.filex.2.0.0:USE FAULT TOLERANCE ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE MMC DMA NO OS ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_MMC_DMA_NO_OS_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_MMC_DMA_NO_OS_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE MMC DMA OS ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_MMC_DMA_OS_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_MMC_DMA_OS_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE MMC POLLING ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_MMC_POLLING_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_MMC_POLLING_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE NAND ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_NAND_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_NAND_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE NOR ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_NOR_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_NOR_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE SD DMA NO OS ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_SD_DMA_NO_OS_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_SD_DMA_NO_OS_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE SD DMA OS ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_SD_DMA_OS_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_SD_DMA_OS_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:USE SD POLLING ENV
# description: 
set(STMicroelectronics.filex.2.0.0_USE_SD_POLLING_ENV "1")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_USE_SD_POLLING_ENV enabled")


# condition: STMicroelectronics.filex.2.0.0:filex freertos condition
# description: 
set(STMicroelectronics.filex.2.0.0_filex_freertos_condition "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:RTOS#.*Cgroup:FreeRTOS#.*Csub:Core(#.*|$)>,>>,$<NOT:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:File System#.*Cgroup:FileX#.*Csub:No_OS(#.*|$)>,>>>>")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_filex_freertos_condition enabled")


# condition: STMicroelectronics.filex.2.0.0:filex standalone condition
# description: 
set(STMicroelectronics.filex.2.0.0_filex_standalone_condition "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:File System#.*Cgroup:FileX#.*Csub:No_OS(#.*|$)>,>>")
message(DEBUG "CMSIS condition STMicroelectronics.filex.2.0.0_filex_standalone_condition enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:Core#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # FileX core component
  message(DEBUG "Using component File_System_FileX_Core_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "-DCMSIS_USE_File_System_FileX_Core_6_4_2=1")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/inc")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/inc/")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_attributes_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_attributes_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_default_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_default_get_copy.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_default_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_delete.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_entry_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_entry_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_first_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_first_full_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_free_search.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_information_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_local_path_clear.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_local_path_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_local_path_get_copy.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_local_path_restore.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_local_path_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_long_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_long_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_name_extract.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_name_test.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_next_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_next_full_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_search.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_short_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_directory_short_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_attributes_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_attributes_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_best_effort_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_close.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_date_time_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_delete.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_extended_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_extended_best_effort_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_extended_relative_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_extended_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_extended_truncate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_extended_truncate_release.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_open.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_relative_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_truncate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_truncate_release.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_file_write_notify_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_abort.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_boot_info_extract.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_cache_invalidate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_check.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_check_FAT_chain_check.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_check_lost_cluster_check.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_close.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_close_notify_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_extended_space_available.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_flush.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_format.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_format_oem_name_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_format_type_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_format_volume_id_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_open.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_open_notify_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_space_available.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_volume_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_volume_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_volume_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_media_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_partition_offset_calculate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_system_date_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_system_date_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_system_initialize.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_system_time_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_system_time_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_system_timer_entry.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_directory_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_directory_entry_change.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_directory_entry_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_directory_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_directory_search.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_file_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_file_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_length_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_length_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_short_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_unicode_short_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_16_unsigned_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_16_unsigned_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_32_unsigned_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_32_unsigned_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_64_unsigned_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_64_unsigned_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_FAT_entry_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_FAT_entry_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_FAT_flush.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_FAT_map_flush.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_FAT_sector_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_absolute_path_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_logical_sector_cache_entry_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_logical_sector_flush.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_logical_sector_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_logical_sector_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_memory_copy.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_memory_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_string_length_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fx_utility_token_length_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_attributes_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_attributes_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_default_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_default_get_copy.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_default_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_delete.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_first_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_first_full_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_information_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_local_path_clear.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_local_path_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_local_path_get_copy.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_local_path_restore.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_local_path_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_long_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_long_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_name_test.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_next_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_next_full_entry_find.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_short_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_directory_short_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_fault_tolerant_enable.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_attributes_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_attributes_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_best_effort_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_close.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_date_time_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_delete.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_extended_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_extended_best_effort_allocate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_extended_relative_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_extended_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_extended_truncate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_extended_truncate_release.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_open.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_relative_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_seek.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_truncate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_truncate_release.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_file_write_notify_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_abort.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_cache_invalidate.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_check.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_close.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_close_notify_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_extended_space_available.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_flush.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_format.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_open.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_open_notify_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_read.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_space_available.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_volume_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_volume_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_volume_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_media_write.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_system_date_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_system_date_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_system_time_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_system_time_set.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_directory_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_directory_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_file_create.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_file_rename.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_name_get_extended.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_short_name_get.c")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/src/fxe_unicode_short_name_get_extended.c")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_filex_freertos_condition}:${CMAKE_CURRENT_LIST_DIR}/ports/freertos/inc/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_filex_freertos_condition}:${CMAKE_CURRENT_LIST_DIR}/ports/freertos/src/fx_os_current_thread_tls_get.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_filex_freertos_condition}:${CMAKE_CURRENT_LIST_DIR}/ports/freertos/src/fx_os_current_thread_tls_set.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_filex_freertos_condition}:${CMAKE_CURRENT_LIST_DIR}/ports/freertos/src/fx_os_mutex_create.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_filex_freertos_condition}:${CMAKE_CURRENT_LIST_DIR}/ports/freertos/src/fx_os_mutex_delete.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_filex_freertos_condition}:${CMAKE_CURRENT_LIST_DIR}/ports/freertos/src/fx_os_timer_create.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:No_OS#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # FileX Standalone Mode 
  message(DEBUG "Using component File_System_FileX_No_OS_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "-DCMSIS_USE_File_System_FileX_No_OS_6_4_2=1")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/ports/generic/inc/")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:Fault Tolerance Support#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # Fault tolerance support component
  message(DEBUG "Using component File_System_FileX_Fault_Tolerance_Support_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:-DCMSIS_USE_File_System_FileX_Fault_Tolerance_Support_6_4_2=1>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_add_FAT_log.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_add_bitmap_log.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_add_checksum_log.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_add_dir_log.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_apply_logs.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_calculate_checksum.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_cleanup_FAT_chain.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_create_log_file.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_enable.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_read_FAT.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_read_directory_sector.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_read_log_file.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_recover.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_reset_log_file.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_set_FAT_chain.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_transaction_end.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_transaction_fail.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_transaction_start.c>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_FAULT_TOLERANCE_ENV}:${CMAKE_CURRENT_LIST_DIR}/common/src/fx_fault_tolerant_write_log_file.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:sd_polling_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # SD Polling interface component 
  message(DEBUG "Using component File_System_FileX_sd_polling_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_POLLING_ENV}:-DCMSIS_USE_File_System_FileX_sd_polling_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_POLLING_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_POLLING_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_POLLING_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd/stm32_fx_sd_polling_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:sd_dma_os_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # SD DMA OS interface component
  message(DEBUG "Using component File_System_FileX_sd_dma_os_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_DMA_OS_ENV}:-DCMSIS_USE_File_System_FileX_sd_dma_os_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_DMA_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd/>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.filex.2.0.0_USE_SD_DMA_OS_ENV},${STMicroelectronics.filex.2.0.0_filex_freertos_condition}>:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.filex.2.0.0_USE_SD_DMA_OS_ENV},${STMicroelectronics.filex.2.0.0_filex_freertos_condition}>:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd/stm32_fx_sd_dma_os_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:sd_dma_no_os_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # SD DMA NO OS interface component
  message(DEBUG "Using component File_System_FileX_sd_dma_no_os_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_DMA_NO_OS_ENV}:-DCMSIS_USE_File_System_FileX_sd_dma_no_os_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_SD_DMA_NO_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd/>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.filex.2.0.0_USE_SD_DMA_NO_OS_ENV},${STMicroelectronics.filex.2.0.0_filex_standalone_condition}>:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.filex.2.0.0_USE_SD_DMA_NO_OS_ENV},${STMicroelectronics.filex.2.0.0_filex_standalone_condition}>:${CMAKE_CURRENT_LIST_DIR}/interfaces/sd/stm32_fx_sd_dma_no_os_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:nor_flash_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # FileX NOR Flash Interface
  message(DEBUG "Using component File_System_FileX_nor_flash_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NOR_ENV}:-DCMSIS_USE_File_System_FileX_nor_flash_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NOR_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/nor>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NOR_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/nor/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NOR_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/nor/stm32_fx_nor_flash_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:nand_flash_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # FileX NAND Flash Interface
  message(DEBUG "Using component File_System_FileX_nand_flash_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NAND_ENV}:-DCMSIS_USE_File_System_FileX_nand_flash_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NAND_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/nand>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NAND_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/nand/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_NAND_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/nand/stm32_fx_nand_flash_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:mmc_polling_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # MMC Polling interface component
  message(DEBUG "Using component File_System_FileX_mmc_polling_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_POLLING_ENV}:-DCMSIS_USE_File_System_FileX_mmc_polling_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_POLLING_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_POLLING_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_POLLING_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc/stm32_fx_mmc_polling_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:mmc_dma_os_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # MMC Polling interface component
  message(DEBUG "Using component File_System_FileX_mmc_dma_os_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_OS_ENV}:-DCMSIS_USE_File_System_FileX_mmc_dma_os_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc/stm32_fx_mmc_dma_os_driver.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:File System#Cgroup:FileX#Csub:mmc_dma_no_os_itf#Cversion:6.4.2" IN_LIST CMSIS_COMPONENTS_LIST)  # MMC Polling interface component
  message(DEBUG "Using component File_System_FileX_mmc_dma_no_os_itf_6_4_2")
  target_compile_definitions(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_NO_OS_ENV}:-DCMSIS_USE_File_System_FileX_mmc_dma_no_os_itf_6_4_2=1>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_NO_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc>")
  target_include_directories(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_NO_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc/>")
  target_sources(STMicroelectronics_filex_2_0_0 INTERFACE "$<${STMicroelectronics.filex.2.0.0_USE_MMC_DMA_NO_OS_ENV}:${CMAKE_CURRENT_LIST_DIR}/interfaces/mmc/stm32_fx_mmc_dma_no_os_driver.c>")
endif()

