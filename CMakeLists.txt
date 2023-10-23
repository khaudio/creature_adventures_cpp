cmake_minimum_required(VERSION 3.10)

project(creature_adventures VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CXX_EXTENSIONS ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo)
set(CMAKE_BUILD_TYPE Debug)

configure_file(inc/cmakeconfig.h.in inc/cmakeconfig.h)

list(APPEND LIBRARIES)

add_executable(${PROJECT_NAME}
    src/tieredobjectbase.cpp
    src/dice.cpp
    src/item.cpp
    src/modifier.cpp
    src/creature.cpp
    src/action.cpp
    src/deck.cpp
    src/artifact.cpp
    src/player.cpp
    src/battle.cpp
    src/core.cpp
    src/main.cpp
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:-O0 -g>
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g>
    
    PUBLIC
        $<$<CONFIG:Debug>:-O0 -g>
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g>

    INTERFACE
        $<$<CONFIG:Debug>:-O0 -g>
        $<$<CONFIG:Release>:-O2>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g>
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG_BUILD;_DEBUG>
        $<$<CONFIG:Release>:>
    
    PUBLIC
        $<$<CONFIG:Debug>:DEBUG_BUILD;_DEBUG>
        $<$<CONFIG:Release>:>

    INTERFACE
        $<$<CONFIG:Debug>:DEBUG_BUILD;_DEBUG>
        $<$<CONFIG:Release>:>
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc

    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${LIBRARIES} -lpthread

    PUBLIC
        ${LIBRARIES} -lpthread
    
    INTERFACE
        ${LIBRARIES} -lpthread
)

