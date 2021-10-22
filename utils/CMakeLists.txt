cmake_minimum_required(VERSION 3.10.2)

project(utils LANGUAGES C)

set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/utils)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_library(
    ${PROJECT_NAME}
        STATIC
            ${_INC_DIR}/containers/Vector.h
            ${_INC_DIR}/drawing/Point.h
            ${_INC_DIR}/drawing/DrawParams.h
            ${_INC_DIR}/drawing/Rectangle.h
            ${_INC_DIR}/drawing/Color.h
            ${_INC_DIR}/input/EventDefines.h
            ${_INC_DIR}/time/Time.h
            ${_INC_DIR}/thread/Thread.h
            ${_INC_DIR}/ErrorCodes.h
            ${_INC_DIR}/Log.h
            
            ${_SRC_DIR}/drawing/Point.c
            ${_SRC_DIR}/drawing/DrawParams.c
            ${_SRC_DIR}/drawing/Rectangle.c
            ${_SRC_DIR}/drawing/Color.c
            ${_SRC_DIR}/time/Time.c
            ${_SRC_DIR}/thread/Thread.c
            ${_SRC_DIR}/containers/Vector.c

)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(
    ${PROJECT_NAME}
        PUBLIC
            _DEFAULT_SOURCE=1
)