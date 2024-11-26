#include <stdio.h>

#include "parse_arguments.h"
#include "lexer.h"

int main(int argc, const char** argv) {
    const CommandArguments arguments = parse_command_arguments(argc, argv);

    if (arguments.source_file == nullptr) {
        return 1;
    }

    const LexerOutput lexer_output = run_lexer(&arguments);
    if (lexer_output.result == false) {
        return 1;
    }

    // stuff heregit

    printf("Assembling complete!\n");
    return 0;
}
