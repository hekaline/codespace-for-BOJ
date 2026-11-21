cmake_minimum_required(VERSION 3.20)

project(codespace-for-BOJ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROBLEM_FILE "src/main.cpp" CACHE STRING "Path to the problem source file")

if(IS_ABSOLUTE "${PROBLEM_FILE}")
    set(PROBLEM_SOURCE "${PROBLEM_FILE}")
else()
    set(PROBLEM_SOURCE "${CMAKE_SOURCE_DIR}/${PROBLEM_FILE}")
endif()

if(NOT EXISTS "${PROBLEM_SOURCE}")
    message(FATAL_ERROR "Problem source file does not exist: ${PROBLEM_SOURCE}")
endif()

add_executable(solution "${PROBLEM_SOURCE}")
