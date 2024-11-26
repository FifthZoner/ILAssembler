cmake_minimum_required(VERSION 3.29)
project(ILAssembler C)

set(CMAKE_C_STANDARD 23)

add_executable(ILAssembler src/main.c
        src/parse_arguments.h
        src/parse_arguments.c
        src/lexer.c
        src/lexer.h)
