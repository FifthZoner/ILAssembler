#ifndef INSTRUCTION_TRANSLATOR_H
#define INSTRUCTION_TRANSLATOR_H

#include "instruction_descriptor.h"

typedef struct Translator {
    struct Translator* next_level;
    InstructionDescriptor descriptor;
    uint32_t next_level_size;
    uint32_t key_letter;
} InstructionTranslator;


void instruction_translator_add(InstructionTranslator* translator, const char* key, uint32_t key_length, InstructionDescriptor descriptor, uint32_t index);

const InstructionDescriptor* instruction_translator_get(InstructionTranslator* translator, const char* key, uint32_t key_length, uint32_t index);

void instruction_translator_clear (const InstructionTranslator* translator);

#endif //INSTRUCTION_TRANSLATOR_H
