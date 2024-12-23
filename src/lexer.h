#ifndef LEXER_H
#define LEXER_H

#include "parse_arguments.h"

#include <stdint.h>

typedef enum LiteralType {
    numeric, text
} LiteralType;

typedef enum NumericType {
    integer, real, unsigned_integer
} NumericType;


typedef struct LexerToken {
    char* token = nullptr;
    uint32_t length = 0;
    LiteralType literal_type : 2 = text;
    NumericType numeric_type : 2 = integer;
} LexerToken;

typedef struct LexerLine {
    uint32_t token_amount = 0;
    LexerToken* tokens = nullptr;
} LexerLine;

typedef struct LexerOutput {
    // used space
    uint64_t lines_amount = 0;
    // reserved space
    uint64_t capacity = 0;
    LexerLine* lines = nullptr;
} LexerOutput;

typedef struct LexerFiles {
    uint32_t file_amount = 0;
    uint32_t capacity = 0;
    char** files;
} LexerFiles;

LexerOutput run_lexer(const CommandArguments* arguments, LexerFiles* files);

#endif //LEXER_H
