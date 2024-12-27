#ifndef ASSEMBLER_RUNNER_H
#define ASSEMBLER_RUNNER_H

#include "lexer.h"
#include "translator.h"

bool run_assembling(const LexerOutput* const lexer_output, const CommandArguments* const arguments, struct Translator* translator);

#endif //ASSEMBLER_RUNNER_H
