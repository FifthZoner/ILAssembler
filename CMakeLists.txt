cmake_minimum_required(VERSION 3.29)
project(ILAssembler C)

set(CMAKE_C_STANDARD 23)

add_executable(ILAssembler src/main.c
        src/parse_arguments.h
        src/parse_arguments.c
        src/lexer.c
        src/lexer.h
        src/instruction_translator.c
        src/instruction_translator.h
        src/instruction_descriptor.h
        src/instruction_container.h
        src/assembler_runner.c
        src/assembler_runner.h
        src/instruction_handlers.c
        src/instruction_handlers.h)
