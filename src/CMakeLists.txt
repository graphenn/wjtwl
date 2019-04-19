cmake_minimum_required(VERSION 3.6)

include_directories("../include")

aux_source_directory(. DIR_LIB_SRCS)

add_library(wjtwl STATIC ${DIR_LIB_SRCS})