cmake_minimum_required(VERSION 3.0)
project(player_movement)

find_package(SFML 2.5.1 COMPONENTS
                graphics 
                window 
                system
            REQUIRED)

set (EXEC_FILE "platformer.exe")

set (SOURCES 
            sources/main.cpp
            sources/player.cpp
            sources/player_states.cpp
    )

add_executable(${EXEC_FILE} ${SOURCES})
target_include_directories(${EXEC_FILE} PRIVATE include)

target_compile_features(${EXEC_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXEC_FILE} PRIVATE
                        sfml-graphics
                        sfml-system
                        sfml-window
                    )

set (COMPILER_SETTINGS
    -O2
)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})