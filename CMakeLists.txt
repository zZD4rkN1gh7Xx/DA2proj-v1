cmake_minimum_required(VERSION 3.26)
project(DA2proj_v1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA2proj_v1
        main.cpp
        place.cpp
        worldGraph.cpp
        FileReaderToy.cpp
        connection.cpp
        FileReaderToy.cpp
)