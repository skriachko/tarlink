cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD 17)

# Specify the project info.
project(tarme VERSION 1.0.0 DESCRIPTION "TAR pack/unpack tool")


add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Set the version property.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
# Set the shared object version property to the project's major version.
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ../src/
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        tarlink
)

