cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 99)
project(tcp_cc C)

set(SOURCE_FILES
        cmake-build-debug/stockList.txt
        measure.c
        sender.c
        )

include_directories(.)

add_executable(Server measure.c)
add_executable(Client sender.c)
