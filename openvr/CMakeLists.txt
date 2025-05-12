cmake_minimum_required(VERSION "3.15")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)

# Solution
project("Basic XReal Air 2 ULTRA driver")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SIZEOF_VOIDP ${CMAKE_SIZEOF_VOID_P})
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PROCESSOR_ARCH "64")
else()
    set(PROCESSOR_ARCH "32")
endif()

if(WIN32)
    set(PLATFORM_NAME "win")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_NAME "linux")
elseif(APPLE)
    set(PLATFORM_NAME "osx")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENVR REQUIRED openvr)

# Example Driver
set(DRIVER_NAME "xrealair2ultra")
set(XREALAIR2ULTRA_DRIVER "driver_${DRIVER_NAME}")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library("${XREALAIR2ULTRA_DRIVER}" SHARED "${HEADERS}" "${SOURCES}")

target_include_directories("${XREALAIR2ULTRA_DRIVER}" PUBLIC "${OPENVR_INCLUDE_DIRS}")
target_include_directories("${XREALAIR2ULTRA_DRIVER}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries("${XREALAIR2ULTRA_DRIVER}" PUBLIC "${OPENVR_LIBS}")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCES})
set_property(TARGET "${XREALAIR2ULTRA_DRIVER}" PROPERTY CXX_STANDARD 17)

add_custom_target(
    clang-format
    ALL
    COMMAND clang-format
    -i --style=file:${CMAKE_CURRENT_SOURCE_DIR}/.clang-format
    ${HEADERS} ${SOURCES}
)
