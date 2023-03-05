cmake_minimum_required(VERSION 3.25)

project(dsplib)

set(SOURCES
    src/dft.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(dsplib
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
