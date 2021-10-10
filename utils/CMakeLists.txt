cmake_minimum_required(VERSION 3.5.2)

project(utils LANGUAGES C)

set(_ICLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(_HEADERS_DIR ${_ICLUDE_DIR}/utils)
set(_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME} STATIC 
        ${_HEADERS_DIR}/Log.h
        ${_HEADERS_DIR}/ErrorCodes.h
        ${_HEADERS_DIR}/containers/Vector.h
        ${_HEADERS_DIR}/drawing/Point.h
        ${_HEADERS_DIR}/drawing/Rectangle.h
        ${_HEADERS_DIR}/input/EventDefines.h

        ${_SOURCE_DIR}/containers/Vector.c
        ${_SOURCE_DIR}/drawing/Point.c
        ${_SOURCE_DIR}/drawing/Rectangle.c

)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
        ${_ICLUDE_DIR}
)
