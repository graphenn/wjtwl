# Many projects still are stuck using CMake 2.8 is several places so it's good to provide backward support too. This is
# specially true in old embedded systems (OpenWRT and friends) where CMake isn't necessarily upgraded.
cmake_minimum_required(VERSION 2.8)

include_directories("../include")

#添加此头文件是为了单元测试。正常使用不需要添加
include_directories("../src")

aux_source_directory(. DIR_EXAMPLE_SRCS)

add_executable(example ${DIR_EXAMPLE_SRCS})

target_link_libraries(example wjtwl)
