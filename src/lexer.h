#ifndef LEXER_H
#define LEXER_H

#include "parse_arguments.h"

#include <stdint.h>

typedef enum LiteralType {
    numeric, text, instruction
} LiteralType;

typedef enum NumericType {
    integer, real, unsigned_integer, hex_mask
} NumericType;


typedef struct LexerToken {
    // the type to use is dependent on type below
    union {
        char* text;
        char* instruction;
        int64_t integer;
        long double real;
        uint64_t unsigned_integer;
        uint64_t hex_mask;
    } token;

    uint32_t length;
    LiteralType literal_type : 2;
    NumericType numeric_type : 2;
} LexerToken;

typedef struct LexerLine {
    uint32_t token_amount;
    uint32_t capacity;
    LexerToken* tokens;
} LexerLine;

typedef struct LexerOutput {
    // used space
    uint64_t lines_amount;
    // reserved space
    uint64_t capacity;
    LexerLine* lines;
} LexerOutput;

typedef struct LexerFiles {
    uint32_t file_amount;
    uint32_t capacity;
    char** files;
} LexerFiles;

LexerOutput run_lexer(const CommandArguments* arguments, LexerFiles* files);

#endif //LEXER_H
