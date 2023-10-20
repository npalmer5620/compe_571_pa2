cmake_minimum_required(VERSION 3.1)
project(PA2 C)

set(CMAKE_C_STANDARD 11)

add_executable(PA2
        main.c
        shortest_job_first.c
        round_robin.c
        round_robin.h
        util.c
        util.h)

target_link_libraries(PA2 m)
