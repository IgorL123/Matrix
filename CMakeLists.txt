cmake_minimum_required(VERSION 3.17)
project(Matrix C)

set(CMAKE_C_STANDARD 99)

add_executable(Matrix main.c Matrix.h Matrix.c test.c Matrix_types.c)
