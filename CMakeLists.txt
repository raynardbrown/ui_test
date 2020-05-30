################################################################################
# This is the CMake build script for the UI Test library.
#
# This script does _NOT_ make use of the CMake GTest module since it relies on
# the googletest library being built from source and _NOT_ installed.
#
# You must specify the path to the root of the googletest source archive that
# you built by passing it on the CMake command line using the variable
# GTEST_ROOT. Alternatively you can specify GTEST_ROOT using an environment
# variable.
#
# This script also relies on googletest being built out-of-source in a build
# directory within GTEST_ROOT/build.
################################################################################

cmake_minimum_required(VERSION 3.15.5)

# Set the name of the project and store it in a variable PROJECT_NAME
project(ui_test)

set(GTEST_LIB_NAME "gtest")

#
# Find the source compiled, not installed googletest library. Normally if you
# built and installed googletest you would just run find_package(GTest) within
# CMake. However, GTest does not work (at least I could not get it to work) with
# a googletest library that has not been installed.
find_library(MY_GTEST_LIBRARIES gtestd
             HINTS
                 ENV GTEST_ROOT
                 ${GTEST_ROOT}
             PATH_SUFFIXES build/googlemock/gtest)

if(NOT MY_GTEST_LIBRARIES)
  message(FATAL_ERROR "googletest library not found")
endif()

################################################################################
# Find the googletest headers
#
# Ensure that the names of the headers are specified just as they would be via
# an include statement.
################################################################################
find_path(MY_GTEST_INCLUDE_DIRS NAMES gtest/gtest.h 
          HINTS
               ENV GTEST_ROOT
               ${GTEST_ROOT}
          PATH_SUFFIXES googletest/include)

if(NOT MY_GTEST_INCLUDE_DIRS)
  message(FATAL_ERROR "googletest headers not found")
endif()

set(Headers "")
list(APPEND Headers ${CMAKE_CURRENT_SOURCE_DIR}/inc)
list(APPEND Headers ${MY_GTEST_INCLUDE_DIRS})

set(Libraries "")
list(APPEND Libraries ${MY_GTEST_LIBRARIES})

set(Sources src/IdManagerTest.cpp
            src/main.cpp)

if (MSVC)
    add_compile_options(-Zi 
                        -W4
                        -EHsc
                        -D_CRT_SECURE_NO_WARNINGS
                        -DSTRICT
                        -DUNICODE
                        -D_UNICODE)
else()
    # fail until we target more platforms
    message(FATAL_ERROR "compiler not supported")
endif()

find_library(UI_LIBRARY ui PATH_SUFFIXES ui/build)

if(NOT UI_LIBRARY)
  message(FATAL_ERROR "ui library not found")
endif()

list(APPEND Libraries ${UI_LIBRARY})

find_path(UI_INCLUDE NAMES ui/Window.h PATH_SUFFIXES ui/inc)

if(NOT UI_INCLUDE)
  message(FATAL_ERROR "ui headers not found")
endif()

list(APPEND Headers ${UI_INCLUDE})

find_path(UI_SRC_INCLUDE NAMES ui/private/IdManager.h PATH_SUFFIXES ui/src)

if(NOT UI_SRC_INCLUDE)
  message(FATAL_ERROR "ui src headers not found")
endif()

list(APPEND Headers ${UI_SRC_INCLUDE})

add_executable(${PROJECT_NAME} ${Sources})

target_link_libraries(${PROJECT_NAME} ${Libraries})

target_include_directories(${PROJECT_NAME} PRIVATE ${Headers})