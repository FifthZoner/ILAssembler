#ifndef INSTRUCTION_DESCRIPTOR_H
#define INSTRUCTION_DESCRIPTOR_H

#include "lexer.h"
#include "instruction_container.h"
#include "instruction_translator.h"

struct Translator;

// might not be needed if the translator is always called with known data type needed
typedef enum TranslatorOutputType {
    translator_instruction, translator_label, translator_variable,
} TranslatorOutputType;

typedef struct TranslatorOutput {
    union {
        InstructionContainer(*called_function)(LexerLine*, LexerOutput*, struct Translator*);
        uint64_t jump_address;
        // <variable something here>
    } content;

} TranslatorOutput;

typedef struct TranslatorEntry {

    // these functions will take lexer lines and convert them into correct instructions
    TranslatorOutput entry;

} InstructionDescriptor;

#endif //INSTRUCTION_DESCRIPTOR_H
