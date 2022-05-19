cmake_minimum_required (VERSION 3.0)

project (Shared_ptr VERSION 1.0)


set (EXEC_FILE "main")

set (SOURCES
    sources/main.cpp
)

set (HEADERS
    include/shared_ptr.hpp
)

add_executable(${EXEC_FILE} ${SOURCES})

target_include_directories(${EXEC_FILE} PRIVATE include)

set (COMPILER_SETTINGS
    -std=c++17

    -O2
)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})
