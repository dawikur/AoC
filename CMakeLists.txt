# Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

cmake_minimum_required(VERSION 3.16)

project(
  AoC
  VERSION 0.1
  LANGUAGES CXX)

# ##############################################################################
# configure

if(NOT CMAKE_BUILD_TYPE)
  if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(CMAKE_BUILD_TYPE "Debug")
  else()
    set(CMAKE_BUILD_TYPE "Release")
  endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
  COMMAND date +%Y
  OUTPUT_VARIABLE DATE_YEAR
  OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

execute_process(
  COMMAND git rev-parse HEAD
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

execute_process(
  COMMAND git diff-index --quiet HEAD --
  RESULT_VARIABLE GIT_DIRTY
  ERROR_QUIET)

configure_file(config.tpp include/aoc/config.hpp)

# ##############################################################################
# AoC

add_library(AoC INTERFACE)

target_compile_features(AoC INTERFACE cxx_std_20)
set_target_properties(AoC PROPERTIES CXX_EXTENSIONS OFF)

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
target_compile_definitions(AoC INTERFACE IS_${BUILD_TYPE}=1)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_options(AoC INTERFACE -Og)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_compile_definitions(AoC INTERFACE IS_UNIX=1)

  target_compile_options(
    AoC
    INTERFACE -fPIC
              -Wall
              -Wcast-align
              -Wconversion
              -Wdouble-promotion
              -Werror
              -Wextra
              -Wformat=2
              -Wnon-virtual-dtor
              -Wnull-dereference
              -Wold-style-cast
              -Woverloaded-virtual
              -Wpedantic
              -Wshadow
              -Wsign-conversion
              -Wunused
              -pedantic)

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_definitions(AoC INTERFACE IS_CLANG=1)

    target_compile_options(
      AoC INTERFACE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic
                    -fcolor-diagnostics)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_definitions(AoC INTERFACE IS_GNU=1)

    target_compile_options(
      AoC
      INTERFACE -Wduplicated-branches -Wduplicated-cond -Wlogical-op
                -Wmisleading-indentation -Wuseless-cast
                -fdiagnostics-color=always)

    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 11.0)
      target_compile_options(AoC PUBLIC -fconcepts-diagnostics-depth=3)
    endif()
  else()
    message(WARNING "Unknown compiler [${CMAKE_CXX_COMPILER_ID}]")
  endif()
else()
  message(WARNING "Unknown platform [${CMAKE_SYSTEM_NAME}]")
endif()

target_include_directories(AoC INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(AoC INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)

# ##############################################################################
# solutions

set(SOLUTIONS ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(
  GLOB AOC_YEARS
  RELATIVE ${SOLUTIONS}/
  ${SOLUTIONS}/*)

foreach(aoc_year ${AOC_YEARS})
  if(IS_DIRECTORY ${SOLUTIONS}/${aoc_year})
    file(
      GLOB AOC_DAYS
      RELATIVE ${SOLUTIONS}/${aoc_year}
      ${SOLUTIONS}/${aoc_year}/*)

    foreach(aoc_day ${AOC_DAYS})
      if(IS_DIRECTORY ${SOLUTIONS}/${aoc_year}/${aoc_day})
        add_executable(${aoc_year}_${aoc_day}
                       ${SOLUTIONS}/${aoc_year}/${aoc_day}/main.cpp)

        target_include_directories(${aoc_year}_${aoc_day}
                                   PRIVATE ${SOLUTIONS}/${aoc_year}/${aoc_day})

        target_link_libraries(${aoc_year}_${aoc_day} PRIVATE AoC)

        set_target_properties(
          ${aoc_year}_${aoc_day}
          PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/aoc/libs"
                     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/aoc/libs"
                     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/aoc/apps")
      endif()
    endforeach()
  endif()
endforeach()
