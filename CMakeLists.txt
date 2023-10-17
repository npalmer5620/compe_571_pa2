cmake_minimum_required(VERSION 3.26)
project(PA2 C)

set(CMAKE_C_STANDARD 11)

add_executable(PA2 shortest_job_first.c
        round_robin.c
        util.c
        util.h)
