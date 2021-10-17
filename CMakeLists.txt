cmake_minimum_required(VERSION 3.5.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers_c.cmake)

project(hello LANGUAGES C)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers_c.cmake)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(_INCLUDE_DIR ${_BASE_DIR}/include)
set(_SOURCES_DIR ${_BASE_DIR}/src)

add_executable(${PROJECT_NAME}
    ${_SOURCES_DIR}/main.c
    ${_SOURCES_DIR}/Engine/Engine.c
    ${_SOURCES_DIR}/Game/Game.c
    ${_SOURCES_DIR}/Engine/EngineConfigLoader.c

    ${_INCLUDE_DIR}/Engine/Engine.h
    ${_INCLUDE_DIR}/Game/Game.h
    ${_INCLUDE_DIR}/Game/config/GameCfg.h
    ${_INCLUDE_DIR}/Engine/config/EngineCfg.h
    ${_INCLUDE_DIR}/Engine/EngineConfigLoader.h

)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

target_link_libraries(
    ${PROJECT_NAME} 
        PRIVATE
            sdl_utils
)
target_include_directories(
    ${PROJECT_NAME} 
        PRIVATE
            ${_BASE_DIR}
            ${_INCLUDE_DIR}
)
add_subdirectory(utils)
add_subdirectory(sdl_utils)
