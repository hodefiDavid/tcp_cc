#cmake_minimum_required(VERSION 3.17)
#project(tcp_cc C)
#

#add_executable(tcp_cc measure.c )
#add_executable(tcp_cc sender.c )


cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 99)
project(tcp_cc C)


#set(SOURCE_FILES
#        cmake-build-debug/stockList.txt
#        measure.c
#        sender.c)
set(SOURCE_FILES
        cmake-build-debug/stockList.txt
        measure.c
        sender.c
        se.c
        cl.c
        )

include_directories(.)


add_executable(Server measure.c)
#add_executable(Server1 server.c)

add_executable(Client sender.c)
#add_executable(Se se.c)
#add_executable(Cl cl.c)

#add_executable(Project_2_2 ${SOURCE_FILES})
#set(CMAKE_CXX_STANDARD 11)
