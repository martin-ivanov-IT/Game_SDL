cmake_minimum_required(VERSION 3.5.2)
  
project(sdl_utils LANGUAGES C)

set(_ICLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(_HEADERS_DIR ${_ICLUDE_DIR}/sdl_utils)
set(_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(
    ${PROJECT_NAME} STATIC 
        ${_HEADERS_DIR}/SDL_loader.h
        ${_HEADERS_DIR}/MonitorWindow.h
        ${_HEADERS_DIR}/config/MonitorWindowCfg.h
        ${_HEADERS_DIR}/config/ImageContainerCfg.h
        ${_HEADERS_DIR}/config/TextContainerCfg.h
        ${_HEADERS_DIR}/Texture.h
        ${_HEADERS_DIR}/InputEvent.h
        ${_HEADERS_DIR}/Renderer.h
        ${_HEADERS_DIR}/containers/ImageContainer.h
        ${_HEADERS_DIR}/containers/TextContainer.h


        ${_SOURCES_DIR}/SDL_loader.c
        ${_SOURCES_DIR}/MonitorWindow.c
        ${_SOURCES_DIR}/Texture.c
        ${_SOURCES_DIR}/InputEvent.c
        ${_SOURCES_DIR}/Renderer.c
        ${_SOURCES_DIR}/containers/ImageContainer.c
        ${_SOURCES_DIR}/containers/TextContainer.c
        ${_SOURCES_DIR}/config/ImageContainerCfg.c
        ${_SOURCES_DIR}/config/TextContainerCfg.c




)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${_ICLUDE_DIR}
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} 
        PUBLIC
            utils
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARY}
            ${SDL2_TTF_LIBRARY}
            ${SDL2_MIXER_LIBRARY}
)

