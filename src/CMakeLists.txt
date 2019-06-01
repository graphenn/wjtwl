cmake_minimum_required(VERSION 2.8)

include_directories("../include")
include_directories(${PROJECT_BINARY_DIR}/src)

aux_source_directory(. DIR_LIB_SRCS)

option (CHINESE_CALENDAR_HISTORY_SUPPORT
       "Add support on calculate Chinese calendar in history time." ON)


configure_file(wjtwl_lib_config.h.in        ${PROJECT_BINARY_DIR}/src/wjtwl_lib_config.h)
message(STATUS "Written ${PROJECT_BINARY_DIR}/wjtwl_lib_config.h")

add_library(wjtwl STATIC ${DIR_LIB_SRCS})