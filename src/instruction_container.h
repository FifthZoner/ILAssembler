#ifndef INSTRUCTION_CONTAINER_H
#define INSTRUCTION_CONTAINER_H

#include <stdint.h>

typedef enum {
    none, a, b, c, d, e, f
} instruction_data_configuration;

typedef struct InstructionContainer {

    // OP - operand
    // t  - 4  bit type
    // d  - 1  bit destination
    // s  - 32 bit literal
    // b  - 5  bit address within a data memory word
    // r  - 20 bit address
    // x  - any, set to 0 to be sure

    // INFO: if the bits are in the wrong order it's most likely because of bif field ordering on the given platform
    // change the field order of contact me to add this case to the program
    union {
        struct  {
            uint32_t s  : 32;
            uint32_t d  : 1 ;
            uint32_t t  : 4 ;
            uint32_t op : 3 ;
        } type_a;
        struct  {
            uint32_t s  : 32;
            uint32_t op : 8 ;
        } type_b;
        struct  {
            uint32_t r  : 20;
            uint32_t b  : 5 ;
            uint32_t d  : 1 ;
            uint32_t t  : 4 ;
            uint32_t op : 10;
        } type_c;
        struct  {
            uint32_t r  : 20;
            uint32_t x  : 12;
            uint32_t op : 8 ;
        } type_d;
        // these types are unspecified in the article but needed
        struct  {
            uint32_t r  : 20;
            uint32_t b  : 5;
            uint32_t x  : 7;
            uint32_t op : 8 ;
        } type_e;
        struct  {
            uint32_t r  : 20;
            uint32_t x  : 5;
            uint32_t op : 15 ;
        } type_f;
        struct {
            // the first 40 bits on the right serve as a spacer to preserve the encoded 40 bit instruction
            // variables after that encode metadata in space that would be wasted anyway
            uint64_t padding_do_not_use : 40;
            uint64_t configuration_type : 3 ;
            uint64_t is_valid           : 1 ;
        } meta;
    };

} InstructionContainer;

#endif //INSTRUCTION_CONTAINER_H
