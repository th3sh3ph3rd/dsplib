cmake_minimum_required(VERSION 3.25)

project(dft)

set(SOURCES
    src/dft.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(dft
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
