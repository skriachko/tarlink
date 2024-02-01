cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD 17)

project(tarlink VERSION 1.0.0 DESCRIPTION "TAR library")

set(TARME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tarme)

add_library(${PROJECT_NAME} SHARED
    src/tar.cpp
    src/tar.hpp
)

# Set the version property.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
# Set the shared object version property to the project's major version.
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

add_subdirectory(${TARME_DIR})
