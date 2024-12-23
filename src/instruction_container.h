#ifndef INSTRUCTION_CONTAINER_H
#define INSTRUCTION_CONTAINER_H

#include <stdint.h>

typedef enum {
    none, a, b, c, d
} instruction_data_configuration;

typedef struct InstructionContainer {

    union {
        struct  {
            uint64_t op : 3 ;
            uint64_t t  : 4 ;
            uint64_t d  : 1 ;
            uint64_t s  : 32;
        } type_a;
        struct  {
            uint64_t op : 8 ;
            uint64_t s  : 32;
        } type_b;
        struct  {
            uint64_t op : 10;
            uint64_t t  : 4 ;
            uint64_t d  : 1 ;
            uint64_t b  : 5 ;
            uint64_t r  : 20;
        } type_c;
        struct  {
            uint64_t op : 8 ;
            uint64_t x  : 12;
            uint64_t r  : 20;
        } type_d;
        struct {
            // the first 40 bits serve as a spacer to preserve the encoded 40 bit instruction
            // variables after that encode metadata in space that would be wasted anyway
            uint64_t encoded_instruction: 40 = 0;
            uint64_t configuration_type : 3  = (instruction_data_configuration)none;
            uint64_t is_valid           : 1  = false;
        } meta;
    };

} InstructionContainer;

#endif //INSTRUCTION_CONTAINER_H
