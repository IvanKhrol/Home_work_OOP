cmake_minimum_required (VERSION 3.0)

project ("SkillTree" VERSION 1.0)


find_package(SFML 2.5.1 COMPONENTS 
                graphics 
                window 
                system 
                REQUIRED)

set (EXEC_FILE "skill_tree")

set(CMAKE_CXX_STANDARD 17)


set (SOURCES
    sources/Node.cpp
    sources/main.cpp
    sources/HitNode.cpp
    sources/AccumulateNode.cpp
    sources/AbstructSkillTree.cpp
)

add_executable(${EXEC_FILE} ${SOURCES})

target_include_directories(${EXEC_FILE} PRIVATE include)
target_link_libraries(${EXEC_FILE} 
                        sfml-graphics 
                        sfml-window 
                        sfml-system
                     )

set(CMAKE_CXX_STANDARD_REQUIRED True)

target_compile_options(${EXEC_FILE} PRIVATE ${COMPILER_SETTINGS})