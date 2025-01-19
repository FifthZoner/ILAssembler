#ifndef LEXER_H
#define LEXER_H

#include "parse_arguments.h"

#include <stdint.h>

typedef enum LiteralType {
    numeric, instruction, jump_label, variable, divider, IY, EQU
} LiteralType;

typedef enum NumericType {
    integer, real, hex, oct, bin, boolean
} NumericType;


typedef struct LexerToken {
    // the type to use is dependent on type below
    union {
        char* text;
        char* instruction;
        float real;
        uint32_t label_line;
        int32_t integer;
        // just for things to look nice since it's all the same for the computer
        uint32_t hex;
        uint32_t oct;
        uint32_t bin;
        uint32_t boolean;
        uint32_t address;
        uint32_t numeric;
    } token;
    uint32_t length;
    struct {
        // these only check for the possibility if it being this given type
        LiteralType general_type : 3;
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

#include "translator.h"

LexerOutput run_lexer(const CommandArguments* arguments, LexerFiles* files, struct Translator* translator);

#endif //LEXER_H
