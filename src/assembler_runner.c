#include "assembler_runner.h"

#include <iso646.h>
#include <stdio.h>




bool run_line(LexerLine* line, FILE* out, Translator* translator) {

    // checking what actually is in this line
    if (line->token_amount == 0) {
        printf("Error type: Expression has no tokens!\n");
        return false;
    }

    // if that's true then it's a jump label and as such is not outputted needed
    if (line->tokens[0].data.general_type == jump_label) {
        return true;
    }
    else if (line->tokens[0].data.general_type != instruction) {
        printf("Error type: Expected an instruction as first token of non jump label expression!\n");
        return false;
    }

    // at this point it should be an actual instruction
    const TranslatorEntry* result = translator_get(translator, line->tokens[0].token.text, line->tokens[0].length, 0);

    if (result->content.called_function == nullptr) {
        printf("Error type: Instruction identifier not recognized!\n");
        return false;
    }

    // getting the opcode
    InstructionContainer opcode = result->content.called_function(line, translator);

    if (opcode.meta.is_valid == false) {
        printf("Error type: Invalid instruction syntax!\n");
        return false;
    }

    fwrite(&opcode, 5, 1, out);

    return true;
}

bool run_assembling(const LexerOutput* const lexer_output, const CommandArguments* const arguments, struct Translator* translator) {

    // TODO: add default name

    FILE* out = fopen(arguments->output_file, "wb");
    if (out == nullptr) {
        printf("Could not open output file: \"%s\"\n", arguments->output_file);
        return 0;
    }

    for (uint64_t n = 0; n < lexer_output->lines_amount; n++) {
        if (not run_line(lexer_output->lines + n, out, translator)) {
            printf("Occurred at line %lu\n", n);
            fclose(out);
            translator_clear(translator);
            return false;
        }
    }


    fclose(out);
    translator_clear(translator);
    return true;
}
