#include "instruction_handlers.h"

#include <iso646.h>

// instructions from https://www.mdpi.com/2079-9292/12/19/4052



// LOAD INSTRUCTIONS

// LDIX <value>
// load literal into IX
InstructionContainer instruction_handler_LDIX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 2 or not line->tokens[1].data.valid_numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b11000000;
    container.type_b.s  = line->tokens[1].token.integer;

    container.meta.is_valid = true;
    return container;
}

// LDAL <value>
// load literal into ACC and data type into T in d == 1 (where d is defined is unknown)
InstructionContainer instruction_handler_LDAL(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = a;
    if (line->token_amount != 2 or not line->tokens[1].data.valid_numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_a.op = 0; // opcode unknown
    container.type_a.s  = line->tokens[1].token.integer;
    container.type_a.d  = 0; // source unknown
    container.type_a.t  = 0; // values unknown

    container.meta.is_valid = true;
    return container;
}

// LDA <variable>
// load variable into ACC and data type into T in d == 1 (where d is defined is unknown)
InstructionContainer instruction_handler_LDA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address
    container.type_c.t = 0; // values unknown
    container.type_c.d = 0; // source unknown

    container.meta.is_valid = true;
    return container;
}

// LDAN <variable>
// load negation of variable into ACC and data type into T in d == 1 (where d is defined is unknown)
InstructionContainer instruction_handler_LDAN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address
    container.type_c.t = 0; // values unknown
    container.type_c.d = 0; // source unknown

    container.meta.is_valid = true;
    return container;
}

// LDAX <variable>
// load given member of structure starting with value of IX into ACC and data type into T in d == 1 (where d is defined is unknown)
InstructionContainer instruction_handler_LDAX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address
    container.type_c.t = 0; // values unknown
    container.type_c.d = 0; // source unknown

    container.meta.is_valid = true;
    return container;
}

// LDANX <member>
// load negation of given member of structure starting with value of IX into ACC and data type into T in d == 1 (where d is defined is unknown)
InstructionContainer instruction_handler_LDANX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address
    container.type_c.t = 0; // values unknown
    container.type_c.d = 0; // source unknown

    container.meta.is_valid = true;
    return container;
}

// LDAIO <address>
// load ACC with data from external bus at specified address
InstructionContainer instruction_handler_LDAIO(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or not line->tokens[1].data.valid_numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = line->tokens[1].token.address; // external address

    container.meta.is_valid = true;
    return container;
}



// STORE INSTRUCTIONS

// ST <variable>
// store value from ACC in given variable
InstructionContainer instruction_handler_ST(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// STN <variable>
// store negation of value from ACC in given variable
InstructionContainer instruction_handler_STN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// STX <variable>
// store value from ACC in member of structure starting at address in IX
InstructionContainer instruction_handler_STX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    // TODO: variable or offset?
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// STNX <variable>
// store negation of value from ACC in member of structure starting at address in IX
InstructionContainer instruction_handler_STNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    // TODO: variable or offset?
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// STIO <address>
// store value from ACC in external data something
InstructionContainer instruction_handler_STIO(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or not line->tokens[1].data.valid_numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = line->tokens[1].token.address; // external address

    container.meta.is_valid = true;
    return container;
}

// CST <variable>
// store value in CAR in given variable and set CAR to 0
InstructionContainer instruction_handler_CST(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// CSTN <variable>
// store negation of value in CAR in given variable and set CAR to 0
InstructionContainer instruction_handler_CSTN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// CSTX <variable>
// store value in CAR in member of structure starting at address in IX
InstructionContainer instruction_handler_CSTX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    // TODO: add members
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

// CSTNX <variable>
// store negation of value in CAR in member of structure starting at address in IX
InstructionContainer instruction_handler_CSTNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    // TODO: add members
    if (line->token_amount != 2 or line->tokens[1].data.general_type != variable) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0; // opcode unknown
    container.type_c.r = 0; // var address, not implemented
    container.type_c.b = 0; // probably tied to var address

    container.meta.is_valid = true;
    return container;
}

void add_instruction_handlers(Translator* translator) {
    TranslatorEntry entry;
    // load instructions
    entry.content.called_function = &instruction_handler_LDIX;
    translator_add(translator, "LDIX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_LDAL;
    translator_add(translator, "LDAL", 4, entry, 0);
    entry.content.called_function = &instruction_handler_LDA;
    translator_add(translator, "LDA", 3, entry, 0);
    entry.content.called_function = &instruction_handler_LDAN;
    translator_add(translator, "LDAN", 4, entry, 0);
    entry.content.called_function = &instruction_handler_LDAX;
    translator_add(translator, "LDAX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_LDANX;
    translator_add(translator, "LDANX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_LDAIO;
    translator_add(translator, "LDAIO", 5, entry, 0);
    // store instructions
    entry.content.called_function = &instruction_handler_ST;
    translator_add(translator, "ST", 2, entry, 0);
    entry.content.called_function = &instruction_handler_STN;
    translator_add(translator, "STN", 3, entry, 0);
    entry.content.called_function = &instruction_handler_STX;
    translator_add(translator, "STX", 3, entry, 0);
    entry.content.called_function = &instruction_handler_STNX;
    translator_add(translator, "STNX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_STIO;
    translator_add(translator, "STIO", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CST;
    translator_add(translator, "LCST", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CSTN;
    translator_add(translator, "CSTN", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CSTX;
    translator_add(translator, "CSTX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CSTNX;
    translator_add(translator, "CSTNX", 5, entry, 0);
}