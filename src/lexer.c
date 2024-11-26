#include "lexer.h"

#include <stdio.h>

#include <stdlib.h>

LexerOutput run_lexer(const CommandArguments* arguments) {
    LexerOutput output;

    FILE* in;
    in = fopen(arguments->source_file, "r");
    if (in == nullptr) {
        output.result = false;
        printf("Aborted: could not open source file!");
        return output;
    }


    fclose(in);

    output.result = true;
    return output;
}
