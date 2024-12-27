#ifndef INSTRUCTION_TRANSLATOR_H
#define INSTRUCTION_TRANSLATOR_H

#include "lexer.h"
#include "instruction_container.h"

struct Translator;

// might not be needed if the translator is always called with known data type needed
typedef enum TranslatorOutputType {
    translator_instruction, translator_label, translator_variable,
} TranslatorOutputType;

typedef struct TranslatorEntry {

    union {
        InstructionContainer(*called_function)(LexerLine*, struct Translator*);
        uint64_t jump_address;
        // <variable something here>
    } content;

} TranslatorEntry;

typedef struct Translator {
    struct Translator* next_level;
    TranslatorEntry descriptor;
    uint32_t next_level_size;
    uint32_t key_letter;
} Translator;


void translator_add(Translator* translator, const char* key, uint32_t key_length, TranslatorEntry descriptor, uint32_t index);

const TranslatorEntry* translator_get(Translator* translator, const char* key, uint32_t key_length, uint32_t index);

void translator_clear (const Translator* translator);

#endif //INSTRUCTION_TRANSLATOR_H
