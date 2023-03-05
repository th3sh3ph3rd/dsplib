cmake_minimum_required(VERSION 3.25)

project(test0)

set(SOURCES
    ../src/dft.cpp
    test0.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(test0
    PRIVATE
        ../include
        ../src
        ../lib/gnuplot_iostream
)

find_package(Boost REQUIRED COMPONENTS
    iostreams system filesystem
)
message(STATUS "Boost version: ${Boost_VERSION}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

