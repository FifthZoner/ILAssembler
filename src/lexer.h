#ifndef LEXER_H
#define LEXER_H

#include "parse_arguments.h"

#include <stdint.h>

typedef struct {
    uint8_t result:1;
} LexerOutput;

LexerOutput run_lexer(const CommandArguments* arguments);

#endif //LEXER_H
