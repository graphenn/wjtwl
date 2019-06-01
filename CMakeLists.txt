# Many projects still are stuck using CMake 2.8 is several places so it's good to provide backward support too. This is
# specially true in old embedded systems (OpenWRT and friends) where CMake isn't necessarily upgraded.
cmake_minimum_required(VERSION 2.8)

#文举天文历
project(wjtwl C)

#版本号
set (WJTWL_VERSION_MAJOR 0)
set (WJTWL_VERSION_MINOR 2)


# If we've got 3.0 then it's good, let's provide support. Otherwise, leave it be.
if(POLICY CMP0038)
  # Policy CMP0038 introduced was in CMake 3.0
  cmake_policy(SET CMP0038 NEW)
endif()

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

set(CMAKE_C_STANDARD 11)

include(CheckCSourceCompiles)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
    # There's a catch here.
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Werror")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

endif()

CHECK_C_SOURCE_COMPILES(
  "_Thread_local int x = 0; int main() { return 0; }"
  HAVE__THREAD_LOCAL)

CHECK_C_SOURCE_COMPILES(
  "__thread int x = 0; int main() { return 0; }"
  HAVE___THREAD)

CHECK_C_SOURCE_COMPILES(
  "__declspec(thread) int x = 0; int main() { return 0; }"
  HAVE___DECLSPEC_THREAD)

if (HAVE__THREAD_LOCAL)
    set(SPEC___THREAD "_Thread_local")
elseif (HAVE___THREAD)
    set(SPEC___THREAD "__thread")
elseif (HAVE___DECLSPEC_THREAD)
    set(SPEC___THREAD "__declspec(thread)")
else()
    set(SPEC___THREAD "")
    message(WARNING "Current compiler doesn't support TLS feature, wjtwl_set_config could only be called at single thread.")
endif()

option (BUILD_EXAMPLES
       "Build the examples." ON)


#编译库
add_subdirectory(src)

#编译例子
if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif(BUILD_EXAMPLES)


