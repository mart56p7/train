cmake_minimum_required(VERSION 3.15)
project(trainsim C)

set(CMAKE_C_STANDARD 99)

add_executable(trainsim main.c train.sim.webapp.h train.sim.webapp.c)