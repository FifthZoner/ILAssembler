#include <stdio.h>
#include <stdlib.h>

#include "assembler_runner.h"
#include "parse_arguments.h"
#include "lexer.h"
#include "translator.h"
#include "instruction_handlers.h"

int main(int argc, const char** argv) {
    const CommandArguments arguments = parse_command_arguments(argc, argv);

    if (arguments.error) {
        printf("Invalid input parameters! Run the command with -h flag to get help!");
        return 1;
    }

    // when displaying help skip the run
    if (arguments.display_help) {
        printf("IL Assembler help:\n"
                     "To run the assembler use: \"<name of the binary> <source file> <output file> (-d/-c) (-s <size>)\"\n"
                     "Flags:\n"
                     "-c - separating instruction arguments by a comma (default)\n"
                     "-d - separating instruction arguments by a dot\n"
                     "-s - specify the start address, put a decimal or hex number (0x<number>) after the flag, default value is 0\n"
                     "The first path found is always the source file and the second, optional one is the output file, if it's not specified it will be called <source name>.hex\n"
                     "\n"
                     "Thank you for using my software!\n"
                     "Please report any found bugs and feature requests at: https://github.com/FifthZoner/ILAssembler\n"
                     );
        return 0;
    }

    LexerFiles files;
    struct Translator translator;
    translator.next_level_size = 0;

    add_instruction_handlers(&translator);

    LexerOutput lexer_output = run_lexer(&arguments, &files, &translator);
    if (lexer_output.lines_amount == 0) {
        return 1;
    }

    run_assembling(&lexer_output, &arguments, &translator);

    free(files.files);
    free_lexer_output(&lexer_output);

    // TODO: add translator freeing

    printf("Assembling complete!\n");
    return 0;
}
