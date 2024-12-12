#ifndef INSTRUCTION_CONTAINER_H
#define INSTRUCTION_CONTAINER_H

#include <stdint.h>

typedef enum {
    none, a, b, c, d
} instruction_data_configuration;

typedef struct instruction_container {

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
            uint64_t first_4 : 32 = 0;
            uint64_t last_1  : 8  = 0;
            uint64_t configuration_type:24 = (instruction_data_configuration)none;
        } meta;
    };

} instruction_container;

#endif //INSTRUCTION_CONTAINER_H
