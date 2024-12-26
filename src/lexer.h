#ifndef LEXER_H
#define LEXER_H

#include "parse_arguments.h"

#include <stdint.h>

typedef enum LiteralType {
    numeric, instruction, label
} LiteralType;

typedef enum NumericType {
    integer, real, hex, oct, bin
} NumericType;


typedef struct LexerToken {
    // the type to use is dependent on type below
    union {
        char* text;
        char* instruction;
        uint64_t label_line;
        int64_t integer;
        long double real;
        uint64_t hex;
        uint64_t oct;
        uint64_t bin;
    } token;
    uint32_t length;
    struct {
        // these only check for the possibility if it being this given type
        LiteralType general_type : 2;
        NumericType numeric_type : 3;
        bool valid_decimal : 1;
        bool valid_hex     : 1;
        bool valid_octal   : 1;
        bool valid_binary  : 1;
        bool valid_boolean : 1;
        bool valid_real    : 1;
        bool valid_numeric : 1;
    } data;
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
