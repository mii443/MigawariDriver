cmake_minimum_required(VERSION 3.29.4)

project("MigawariDriver")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(OPENVR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/openvr/headers")

set(PROCESSOR_ARCH "64")
set(PLATFORM_NAME "win")

find_library(OPENVR_LIB openvr_api HINTS "${CMAKE_CURRENT_SOURCE_DIR}/libraries/openvr/lib/${PLATFORM_NAME}${PROCESSOR_ARCH}/" NO_DEFAULT_PATH)

set(DRIVER_NAME "migawari")
set(PROJECT "driver_${DRIVER_NAME}")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/driver_files/src/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/driver_files/src/*.cpp")
add_library("${PROJECT}" SHARED "${HEADERS}" "${SOURCES}")

target_include_directories("${PROJECT}" PUBLIC "${OPENVR_INCLUDE_DIR}")
target_include_directories("${PROJECT}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/driver_files/src/")
target_link_libraries("${PROJECT}" PUBLIC "${OPENVR_LIB}")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/driver_files/src" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/driver_files/src" PREFIX "Source Files" FILES ${SOURCES})
set_property(TARGET "${PROJECT}" PROPERTY CXX_STANDARD 17)
