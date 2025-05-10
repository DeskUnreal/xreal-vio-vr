cmake_minimum_required(VERSION "3.7.1")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
set(EXAMPLE_PROJECT "driver_${DRIVER_NAME}")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library("${EXAMPLE_PROJECT}" SHARED "${HEADERS}" "${SOURCES}")

target_include_directories("${EXAMPLE_PROJECT}" PUBLIC "${OPENVR_INCLUDE_DIRS}")
target_include_directories("${EXAMPLE_PROJECT}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries("${EXAMPLE_PROJECT}" PUBLIC "${OPENVR_LIBS}")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCES})
set_property(TARGET "${EXAMPLE_PROJECT}" PROPERTY CXX_STANDARD 17)

# Copy driver assets to output folder
#add_custom_command(
#    TARGET ${EXAMPLE_PROJECT}
#    PRE_BUILD 
#    COMMAND ${CMAKE_COMMAND} -E copy_directory 
#    ${CMAKE_SOURCE_DIR}/driver_files/driver/ 
#    $<TARGET_FILE_DIR:${EXAMPLE_PROJECT}>
#)
#
# Copy dll to output folder
#add_custom_command(
#    TARGET ${EXAMPLE_PROJECT} 
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy 
#    $<TARGET_FILE:${EXAMPLE_PROJECT}>
#    $<TARGET_FILE_DIR:${EXAMPLE_PROJECT}>/${DRIVER_NAME}/bin/${PLATFORM_NAME}${PROCESSOR_ARCH}/$<TARGET_FILE_NAME:${EXAMPLE_PROJECT}>
#)
