# Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

cmake_minimum_required(VERSION 3.16)

project(
  AoD
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

configure_file(config.tpp include/aod/config.hpp)

# ##############################################################################
# AoD

add_library(AoD INTERFACE include/aod/primitives.hpp)

target_compile_features(AoD INTERFACE cxx_std_20)
set_target_properties(AoD PROPERTIES CXX_EXTENSIONS OFF)

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
target_compile_definitions(AoD INTERFACE IS_${BUILD_TYPE}=1)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_options(AoD INTERFACE -Og)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_compile_definitions(AoD INTERFACE IS_UNIX=1)

  target_compile_options(
    AoD
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
    target_compile_definitions(AoD INTERFACE IS_CLANG=1)

    target_compile_options(
      AoD
      INTERFACE -Weverything
                -Wno-c++98-compat
                -Wno-c++98-compat-pedantic
                -Wno-exit-time-destructors # for assert::signal
                -Wno-global-constructors # for assert::signal, Color::XXX
                -Wno-gnu-zero-variadic-macro-arguments # for λ macro
                -Wno-packed # ignore unnecessary packed atribute
                -Wno-padded # general paddings
                -Wno-switch-enum # for 'default's in enum
                -Wno-weak-vtables # for API structs
                -fcolor-diagnostics)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_definitions(AoD INTERFACE IS_GNU=1)

    target_compile_options(
      AoD
      INTERFACE -Wduplicated-branches -Wduplicated-cond -Wlogical-op
                -Wmisleading-indentation -Wuseless-cast
                -fdiagnostics-color=always)

    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 11.0)
      target_compile_options(AoD PUBLIC -fconcepts-diagnostics-depth=3)
    endif()
  else()
    message(WARNING "Unknown compiler [${CMAKE_CXX_COMPILER_ID}]")
  endif()
else()
  message(WARNING "Unknown platform [${CMAKE_SYSTEM_NAME}]")
endif()

target_include_directories(AoD INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)

# ##############################################################################
# solutions

set(SOLUTIONS ${CMAKE_CURRENT_SOURCE_DIR}/aod)
file(
  GLOB AOD_YEARS
  RELATIVE ${SOLUTIONS}/
  ${SOLUTIONS}/*)

foreach(aod_year ${AOD_YEARS})
  if(IS_DIRECTORY ${SOLUTIONS}/${aod_year})
    file(
      GLOB AOD_DAYS
      RELATIVE ${SOLUTIONS}/${aod_year}
      ${SOLUTIONS}/${aod_year}/*)

    foreach(aod_day ${AOD_DAYS})
      if(IS_DIRECTORY ${SOLUTIONS}/${aod_year}/${aod_day})
        add_executable(${aod_year}_${aod_day}
                       ${SOLUTIONS}/${aod_year}/${aod_day}/main.cpp)

        target_include_directories(${aod_year}_${aod_day}
                                   PRIVATE ${SOLUTIONS}/${aod_year}/${aod_day})

        target_link_libraries(${aod_year}_${aod_day} PRIVATE AoD)

        set_target_properties(
          ${aod_year}_${aod_day}
          PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src/libs"
                     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src/libs"
                     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src/apps")
      endif()
    endforeach()
  endif()
endforeach()
