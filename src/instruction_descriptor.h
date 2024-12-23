#ifndef INSTRUCTION_DESCRIPTOR_H
#define INSTRUCTION_DESCRIPTOR_H

#include "lexer.h"
#include "instruction_container.h"

typedef struct InstructionDescriptor {

    // these functions will take lexer lines and convert them into correct instructions
    InstructionContainer(called_function*)(LexerLine line) = nullptr;

} InstructionDescriptor;

#endif //INSTRUCTION_DESCRIPTOR_H
