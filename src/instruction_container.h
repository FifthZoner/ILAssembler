#ifndef INSTRUCTION_CONTAINER_H
#define INSTRUCTION_CONTAINER_H

#include <stdint.h>

typedef enum {
    none, a, b, c, d
} instruction_data_configuration;

typedef struct InstructionContainer {

    // OP - operand
    // t  - 4  bit type
    // d  - 1  bit destination
    // s  - 32 bit literal
    // b  - 5  bit address within a data memory word
    // r  - 20 bit address
    // x  - ???

    union {
        struct  {
            uint32_t op : 3 ;
            uint32_t t  : 4 ;
            uint32_t d  : 1 ;
            uint32_t s  : 32;
        } type_a;
        struct  {
            uint32_t op : 8 ;
            uint32_t s  : 32;
        } type_b;
        struct  {
            uint32_t op : 10;
            uint32_t t  : 4 ;
            uint32_t d  : 1 ;
            uint32_t b  : 5 ;
            uint32_t r  : 20;
        } type_c;
        struct  {
            uint32_t op : 8 ;
            uint32_t x  : 12;
            uint32_t r  : 20;
        } type_d;
        struct {
            // the first 40 bits serve as a spacer to preserve the encoded 40 bit instruction
            // variables after that encode metadata in space that would be wasted anyway
            uint64_t padding_do_not_use : 40;
            uint64_t configuration_type : 3 ;
            uint64_t is_valid           : 1 ;
        } meta;
    };

} InstructionContainer;

#endif //INSTRUCTION_CONTAINER_H
