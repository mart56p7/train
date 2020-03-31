cmake_minimum_required(VERSION 3.15)
project(trainsim C)

set(CMAKE_C_STANDARD 99)

add_executable(trainsim main.c train.sim.webapp.h train.sim.webapp.c)
# https://stackoverflow.com/questions/46379610/c-winsock2-h-ws2-32-lib-linking-undefined-refernce-to
target_link_libraries(trainsim ws2_32)