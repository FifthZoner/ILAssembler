#include "assembler_runner.h"

#include "instruction_translator.h"

bool run_assembling(const LexerOutput* const lexer_output, const CommandArguments* const arguments) {

    // TODO: add some kind of construction function to avoid wrong default values
    InstructionTranslator translator;
    translator.next_level_size = 0;

    InstructionDescriptor desc;
    desc.called_function = nullptr;
    instruction_translator_add(&translator, "test", 4, desc, 0);
    desc.called_function = nullptr;
    instruction_translator_add(&translator, "wow", 3, desc, 0);



    instruction_translator_clear(&translator);
    return true;
}
