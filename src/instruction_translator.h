#ifndef INSTRUCTION_TRANSLATOR_H
#define INSTRUCTION_TRANSLATOR_H

#include "instruction_descriptor.h"

typedef struct instruction_translator {
    struct instruction_translator* next_level = nullptr;
    instruction_descriptor descriptor;
    uint32_t next_level_size = 0;
    uint32_t key_letter = 0;
}instruction_translator;

#endif //INSTRUCTION_TRANSLATOR_H
