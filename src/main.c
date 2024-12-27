#include <stdio.h>
#include <stdlib.h>

#include "assembler_runner.h"
#include "parse_arguments.h"
#include "lexer.h"
#include "translator.h"
#include "instruction_handlers.h"

int main(int argc, const char** argv) {
    const CommandArguments arguments = parse_command_arguments(argc, argv);

    if (arguments.source_file == nullptr) {
        return 1;
    }

    // TODO: allow for multiple source files here
    LexerFiles files;
    struct Translator translator;
    translator.next_level_size = 0;

    add_instruction_handlers(&translator);

    const LexerOutput lexer_output = run_lexer(&arguments, &files, &translator);
    if (lexer_output.lines_amount == 0) {
        return 1;
    }

    run_assembling(&lexer_output, &arguments, &translator);

    // TODO: add freeing for every string
    free(files.files);

    // TODO: add lexer output freeing here

    printf("Assembling complete!\n");
    return 0;
}
