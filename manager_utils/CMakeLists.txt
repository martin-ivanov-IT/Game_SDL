cmake_minimum_required(VERSION 3.10.2)

project(manager_utils LANGUAGES C)

set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/manager_utils)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_library(
    ${PROJECT_NAME}
        STATIC
            ${_INC_DIR}/managers/DrawMgr.h
            ${_INC_DIR}/managers/ResourceMngr.h
            ${_INC_DIR}/managers/ManagerHandler.h
            ${_INC_DIR}/managers/ResourceMngrProxy.h
            ${_INC_DIR}/managers/DrawMgrProxy.h
            ${_INC_DIR}/managers/config/DrawMgrCfg.h
            ${_INC_DIR}/managers/config/ResourceMngrCfg.h
            ${_INC_DIR}/managers/config/ManagerHandlerCfg.h
            ${_INC_DIR}/drawing/Text.h
            ${_INC_DIR}/drawing/Image.h
            ${_INC_DIR}/drawing/Widget.h
            
            ${_SRC_DIR}//managers/DrawMgr.c
            ${_SRC_DIR}//managers/ResourceMngr.c
            ${_SRC_DIR}//managers/ManagerHandler.c
            ${_SRC_DIR}/drawing/Text.c
            ${_SRC_DIR}/drawing/Image.c
            ${_SRC_DIR}/drawing/Widget.c
)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME} 
        PUBLIC
            sdl_utils
)
