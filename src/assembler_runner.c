#include "assembler_runner.h"
#include "instruction_translator.h"

bool run_assembling(const LexerOutput* const lexer_output, const CommandArguments* const arguments) {

    InstructionTranslator translator;
    InstructionDescriptor desc;
    desc.placeholder = 0x0123456789ABCDEF;
    instruction_translator_add(&translator, "test", 4, desc, 0);
    instruction_translator_add(&translator, "teest", 5, desc, 0);
    instruction_translator_add(&translator, "wow", 3, desc, 0);

    instruction_translator_clear(&translator);


    return true;
}
