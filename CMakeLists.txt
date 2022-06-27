cmake_minimum_required(VERSION 3.10.2)
project(simple_c_string C)

set(CMAKE_C_STANDARD 99)

add_executable(simple_c_string main.c lemon_string.c)