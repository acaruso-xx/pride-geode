cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(pride VERSION 1.0.4)

# Disable Geode's precompiled headers.
set(GEODE_DISABLE_PRECOMPILED_HEADERS ON)

# Use bindings from submodule.
set(GEODE_BINDINGS_REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bindings)

# Suppress annoying warning with overridden virtuals.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wno-inconsistent-missing-override)
endif()

file(GLOB_RECURSE SOURCE_FILES src/**.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
