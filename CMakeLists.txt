cmake_minimum_required(VERSION 4.0)
project(hse C)

set(CMAKE_C_STANDARD 11)

# setting consts
set(LAB_INDEX e)
set(HEADERS_DIR libs)

set(HEADERS
        ${HEADERS_DIR}/utils.h
        ${HEADERS_DIR}/matrix.h
        ${HEADERS_DIR}/input.h
        ${HEADERS_DIR}/queue.h
)

set(SOURCES
        ${HEADERS_DIR}/input.c
        ${HEADERS_DIR}/matrix.c
        ${HEADERS_DIR}/queue.c
)

# adding all the executables
add_executable(main lab-${LAB_INDEX}/main.c ${SOURCES} ${HEADERS})
#add_executable(add lab-${LAB_INDEX}/add.c ${SOURCES} ${HEADERS})
add_executable(test test.c)
