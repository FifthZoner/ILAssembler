#ifndef INSTRUCTION_HANDLERS_H
#define INSTRUCTION_HANDLERS_H

#include "translator.h"

// These functions will be called to assemble each instruction into it's correct variant
// There will be one for each code so this file will likely be the biggest in the project
void add_instruction_handlers(Translator* translator);

#endif //INSTRUCTION_HANDLERS_H
