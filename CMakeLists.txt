cmake_minimum_required(VERSION 3.28.1)
project(hse C)

set(CMAKE_C_STANDARD 11)


# setting consts
set(LAB_INDEX 6)
set(HEADERS_DIR libs)

set(HEADERS
        ${HEADERS_DIR}/utils.h
        ${HEADERS_DIR}/matrix.h
        ${HEADERS_DIR}/input.h
        ${HEADERS_DIR}/queue.h
        lab-6/passenger.h
        lab-6/file_operations.h
)

set(SOURCES
        ${HEADERS_DIR}/input.c
        ${HEADERS_DIR}/matrix.c
        ${HEADERS_DIR}/queue.c
        lab-6/file_operations.c
        lab-6/passenger.c
)

# adding all the executables
add_executable(main lab-${LAB_INDEX}/main.c ${SOURCES} ${HEADERS})
target_compile_definitions(main PRIVATE AUTO_INITIALIZER)
#add_executable(add lab-${LAB_INDEX}/add.c ${SOURCES} ${HEADERS})
add_executable(test test.c)
