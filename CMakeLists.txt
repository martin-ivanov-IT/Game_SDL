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
    ${_SOURCES_DIR}/Game/Entities/Hero.c
    ${_SOURCES_DIR}/Game/Entities/Wheel.c
    ${_SOURCES_DIR}/Game/Entities/Buttons/WheelButton.c
    ${_SOURCES_DIR}/Engine/EngineConfigLoader.c

    ${_INCLUDE_DIR}/Engine/Engine.h
    ${_INCLUDE_DIR}/Game/Game.h
    ${_INCLUDE_DIR}/Game/Entities/Hero.h
    ${_INCLUDE_DIR}/Game/Entities/Wheel.h
    ${_INCLUDE_DIR}/Game/Entities/Buttons/WheelButton.h
    ${_INCLUDE_DIR}/common/CommonDefines.h
    ${_INCLUDE_DIR}/common/TimerDefines.h
    ${_INCLUDE_DIR}/Game/config/GameCfg.h
    ${_INCLUDE_DIR}/Engine/config/EngineCfg.h
    ${_INCLUDE_DIR}/Engine/EngineConfigLoader.h

)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})
# enable_target_c_sanitizer(${PROJECT_NAME} "address")
# "undefined"
# "address"

target_link_libraries(
    ${PROJECT_NAME} 
        PRIVATE
            manager_utils
)
target_include_directories(
    ${PROJECT_NAME} 
        PRIVATE
            ${_BASE_DIR}
            ${_INCLUDE_DIR}
)
add_subdirectory(utils)
add_subdirectory(sdl_utils)
add_subdirectory(manager_utils)

if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(
        ${PROJECT_NAME}
            PRIVATE
            -DRELEASE_BUILD=1
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources

)
endif()
