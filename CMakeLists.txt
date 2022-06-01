cmake_minimum_required(VERSION 3.0)
project(sqlite C)

set(CMAKE_C_STANDARD 99)

add_executable(sqlite main.c struct/input_buffer.h struct/row.h struct/row.c struct/table.h)
