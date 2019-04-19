# Many projects still are stuck using CMake 2.8 is several places so it's good to provide backward support too. This is
# specially true in old embedded systems (OpenWRT and friends) where CMake isn't necessarily upgraded.
cmake_minimum_required(VERSION 2.8)

# If we've got 3.0 then it's good, let's provide support. Otherwise, leave it be.
if(POLICY CMP0038)
  # Policy CMP0038 introduced was in CMake 3.0
  cmake_policy(SET CMP0038 NEW)
endif()

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

#文举天文历
project(wjtwl C)

set(CMAKE_C_STANDARD 11)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
    # There's a catch here.
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Werror")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

endif()

#编译库
add_subdirectory(src)

option (BUILD_EXAMPLES
       "Build the examples." ON)

#编译例子
if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif(BUILD_EXAMPLES)


