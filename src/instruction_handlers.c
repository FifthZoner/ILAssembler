#include "instruction_handlers.h"

#include <iso646.h>


// questions:
// JMP IY r value

// LOAD INSTRUCTIONS

// LDIY
// load literal into IY
InstructionContainer instruction_handler_LDIY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 2
        or line->tokens[1].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_b.op = 0b11010000;
    container.type_b.s  = line->tokens[1].token.integer;

    container.meta.is_valid = true;
    return container;
}

// LDIX
// load literal into IX
InstructionContainer instruction_handler_LDIX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 2
        or line->tokens[1].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b11000000;
    container.type_b.s  = line->tokens[1].token.integer;

    container.meta.is_valid = true;
    return container;
}

// LDAL
// load literal into ACC and data type into T if d == 1
InstructionContainer instruction_handler_LDAL(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = a;
    if (line->token_amount != 6
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or not line->tokens[5].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_a.op = 0b100;
    container.type_a.s  = line->tokens[1].token.numeric;
    container.type_a.t  = line->tokens[3].token.numeric;
    container.type_a.d  = line->tokens[5].token.boolean;


    container.meta.is_valid = true;
    return container;
}

// LDA
// load variable into ACC and data type into T if d == 1
InstructionContainer instruction_handler_LDA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;

    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000000100;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// LDAN
// load negation of variable into ACC and data type into T in d == 1
InstructionContainer instruction_handler_LDAN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;

    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000000110;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// LDAX
// load given member of structure starting with value of IX into ACC and data type into T in d == 1
InstructionContainer instruction_handler_LDAX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;

    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000001000;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// LDANX
// load negation of given member of structure starting with value of IX into ACC and data type into T in d == 1
InstructionContainer instruction_handler_LDANX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;

    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000001010;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// LDAY
// load given member of structure starting with value of IY into ACC and data type into T in d == 1
InstructionContainer instruction_handler_LDAY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;

    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000001100;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// LDANY
// load negation of given member of structure starting with value of IY into ACC and data type into T in d == 1
InstructionContainer instruction_handler_LDANY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;

    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000001110;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// LDAIO
// load ACC with data from external bus at specified address
InstructionContainer instruction_handler_LDAIO(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = d;
    if (line->token_amount != 2
        or line->tokens[1].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_d.op = 0b01101001;
    container.type_d.x = 0;
    container.type_d.r = line->tokens[1].token.address;

    container.meta.is_valid = true;
    return container;
}



// STORE INSTRUCTIONS

// ST
// store value from ACC in given variable
InstructionContainer instruction_handler_ST(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000010100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// STN
// store negation of value from ACC in given variable
InstructionContainer instruction_handler_STN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000010110;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// STX
// store value from ACC in member of structure starting at address in IX
InstructionContainer instruction_handler_STX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000011000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// STNX
// store negation of value from ACC in member of structure starting at address in IX
InstructionContainer instruction_handler_STNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000011010;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// STY
// store value from ACC in member of structure starting at address in IY
InstructionContainer instruction_handler_STY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
   }

    container.type_c.op = 0b0000011100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// STNY
// store negation of value from ACC in member of structure starting at address in IY
InstructionContainer instruction_handler_STNY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000011110;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// STIO
// store value from ACC in external data something
InstructionContainer instruction_handler_STIO(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = d;
    if (line->token_amount != 2
        or line->tokens[1].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
}

    container.type_d.op = 0b01101000;
    container.type_d.x = 0;
    container.type_d.r = line->tokens[1].token.address;

    container.meta.is_valid = true;
    return container;
}

// CST
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

// CSTN
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

// CSTX
// store value in CAR in member of structure starting at address in IX
InstructionContainer instruction_handler_CSTX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000011001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// CSTNX
// store negation of value in CAR in member of structure starting at address in IX
InstructionContainer instruction_handler_CSTNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0000011011;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// CSTY
// store value in CAR in member of structure starting at address in IY
InstructionContainer instruction_handler_CSTY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0000011101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// CSTNY
// store negation of value in CAR in member of structure starting at address in IY
InstructionContainer instruction_handler_CSTNY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0000011111;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// BIT SET/RESET INSTRUCTIONS

// S <r>, <b>
// set bit at r.b to 1 if ACC == 1
InstructionContainer instruction_handler_S(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = e;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_e.op = 0b00001000;
    container.type_e.r = line->tokens[1].token.address;
    container.type_e.b = line->tokens[3].token.numeric;
    container.type_e.x = 0;

    container.meta.is_valid = true;
    return container;
}

// SX <r>, <b>
// set bit at IX + r.b to 1 if ACC == 1
InstructionContainer instruction_handler_SX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = e;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_e.op = 0b00001001;
    container.type_e.r = line->tokens[1].token.address;
    container.type_e.b = line->tokens[3].token.numeric;
    container.type_e.x = 0;

    container.meta.is_valid = true;
    return container;
}

// SY <r>, <b>
// set bit at IY + r.b to 1 if ACC == 1
InstructionContainer instruction_handler_SY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = e;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_e.op = 0b00001010;
    container.type_e.r = line->tokens[1].token.address;
    container.type_e.b = line->tokens[3].token.numeric;
    container.type_e.x = 0;

    container.meta.is_valid = true;
    return container;
}

// R <r>, <b>
// reset bit at r.b to 1 if ACC == 1
InstructionContainer instruction_handler_R(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = e;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_e.op = 0b00001011;
    container.type_e.r = line->tokens[1].token.address;
    container.type_e.b = line->tokens[3].token.numeric;
    container.type_e.x = 0;

    container.meta.is_valid = true;
    return container;
}

// RX <r>, <b>
// reset bit at IX + r.b to 1 if ACC == 1
InstructionContainer instruction_handler_RX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = e;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_e.op = 0b00001011;
    container.type_e.r = line->tokens[1].token.address;
    container.type_e.b = line->tokens[3].token.numeric;
    container.type_e.x = 0;

    container.meta.is_valid = true;
    return container;
}

// RY <r>, <b>
// reset bit at IY + r.b to 1 if ACC == 1
InstructionContainer instruction_handler_RY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = e;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_e.op = 0b00001101;
    container.type_e.r = line->tokens[1].token.address;
    container.type_e.b = line->tokens[3].token.numeric;
    container.type_e.x = 0;

    container.meta.is_valid = true;
    return container;
}

// JUMP INSTRUCTIONS

// JMP <r>/IY
// set program counter to r or IY
InstructionContainer instruction_handler_JMP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = f;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric
        and line->tokens[1].data.general_type != IY)) {
        container.meta.is_valid = false;
        return container;
    }


    container.type_f.op = 0b000011100000000;
    if (line->tokens[1].data.general_type == numeric) {
        container.type_f.r = line->tokens[1].token.address;
    }
    else {
        const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
        // TODO: handle the case where a label is at first address
        if (result->content.jump_address == 0) {
            container.meta.is_valid = false;
            return container;
        }
        container.type_f.r = result->content.jump_address;
    }
    container.type_f.x = 0;

    container.meta.is_valid = true;
    return container;
}

// JMPC <r>/IY
// set program counter to r or IY if ACC == 1
InstructionContainer instruction_handler_JMPC(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = f;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric
        and line->tokens[1].data.general_type != IY)) {
        container.meta.is_valid = false;
        return container;
    }

    if (line->tokens[1].data.general_type == IY) {
        container.type_f.op = 0b000011100010000;
        container.type_f.r = 0; // where to take the address from?
    }
    else {
        container.type_f.op = 0b000011100100000;
        if (line->tokens[1].data.general_type == numeric) {
            container.type_f.r = line->tokens[1].token.address;
        }
        else {
            const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
            // TODO: handle the case where a label is at first address
            if (result->content.jump_address == 0) {
                container.meta.is_valid = false;
                return container;
            }
            container.type_f.r = result->content.jump_address;
        }
    }

    container.type_f.x = 0;

    container.meta.is_valid = true;
    return container;
}

// JMPCN <r>/IY
// set program counter to r or IY if ACC == 0
InstructionContainer instruction_handler_JMPCN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = f;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric
        and line->tokens[1].data.general_type != IY)) {
        container.meta.is_valid = false;
        return container;
    }

    if (line->tokens[1].data.general_type == IY) {
        container.type_f.op = 0b000011100110000;
        container.type_f.r = 0; // where to take the address from?
    }
    else {
        container.type_f.op = 0b000011101000000;
        if (line->tokens[1].data.general_type == numeric) {
            container.type_f.r = line->tokens[1].token.address;
        }
        else {
            const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
            // TODO: handle the case where a label is at first address
            if (result->content.jump_address == 0) {
                container.meta.is_valid = false;
                return container;
            }
            container.type_f.r = result->content.jump_address;
        }
    }

    container.type_f.x = 0;

    container.meta.is_valid = true;
    return container;
}

// RJMP <r>
// set program counter to r
InstructionContainer instruction_handler_RJMP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = f;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric)) {
        container.meta.is_valid = false;
        return container;
    }

    if (line->tokens[1].data.general_type == IY) {
        container.type_f.op = 0b000011100010000;
        container.type_f.r = 0; // where to take the address from?
    }
    else {
        container.type_f.op = 0b000011101010000;
        if (line->tokens[1].data.general_type == numeric) {
            container.type_f.r = line->tokens[1].token.address;
        }
        else {
            const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
            // TODO: handle the case where a label is at first address
            if (result->content.jump_address == 0) {
                container.meta.is_valid = false;
                return container;
            }
            container.type_f.r = result->content.jump_address;
        }
    }
    container.type_f.x = 0;

    container.meta.is_valid = true;
    return container;
}

// RJMPC <r>
// set program counter to r if ACC == 1
InstructionContainer instruction_handler_RJMPC(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = f;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric)) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_f.op = 0b000011100100001;
    if (line->tokens[1].data.general_type == numeric) {
        container.type_f.r = line->tokens[1].token.address;
    }
    else {
        const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
        // TODO: handle the case where a label is at first address
        if (result->content.jump_address == 0) {
            container.meta.is_valid = false;
            return container;
        }
        container.type_f.r = result->content.jump_address;
    }
    container.type_f.x = 0;

    container.meta.is_valid = true;
    return container;
}

// RJMPCN <r>
// set program counter to r if ACC == 0
InstructionContainer instruction_handler_RJMPCN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = f;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric)) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_f.op = 0b000011101000001;
    if (line->tokens[1].data.general_type == numeric) {
        container.type_f.r = line->tokens[1].token.address;
    }
    else {
        const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
        // TODO: handle the case where a label is at first address
        if (result->content.jump_address == 0) {
            container.meta.is_valid = false;
            return container;
        }
        container.type_f.r = result->content.jump_address;
    }
    container.type_f.x = 0;

    container.meta.is_valid = true;
    return container;
}

// CALL <r>
// call r
InstructionContainer instruction_handler_CALL(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric)) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0000111100;
    if (line->tokens[1].data.general_type == numeric) {
        container.type_c.r = line->tokens[1].token.address;
    }
    else {
        const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
        // TODO: handle the case where a label is at first address
        if (result->content.jump_address == 0) {
            container.meta.is_valid = false;
            return container;
        }
        container.type_c.r = result->content.jump_address;
    }
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// CALLC <r>
// call r in ACC == 1
InstructionContainer instruction_handler_CALLC(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric)) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0000111101;
    if (line->tokens[1].data.general_type == numeric) {
        container.type_c.r = line->tokens[1].token.address;
    }
    else {
        const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
        // TODO: handle the case where a label is at first address
        if (result->content.jump_address == 0) {
            container.meta.is_valid = false;
            return container;
        }
        container.type_c.r = result->content.jump_address;
    }
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// CALLCN <r>
// call r if ACC == 0
InstructionContainer instruction_handler_CALLCN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 2
        or (line->tokens[1].data.general_type != jump_label
        and line->tokens[1].data.general_type != numeric)) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0000111110;
    if (line->tokens[1].data.general_type == numeric) {
        container.type_c.r = line->tokens[1].token.address;
    }
    else {
        const TranslatorEntry* result = translator_get(translator, line->tokens[1].token.text, line->tokens[1].length, 0);
        // TODO: handle the case where a label is at first address
        if (result->content.jump_address == 0) {
            container.meta.is_valid = false;
            return container;
        }
        container.type_c.r = result->content.jump_address;
    }
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// RET
// return
InstructionContainer instruction_handler_RET(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0001000000;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// RETC
// return if ACC == 1
InstructionContainer instruction_handler_RETC(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001000001;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// RETCN
// return if ACC == 0
InstructionContainer instruction_handler_RETCN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001000010;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// RETLA <s>
// return if ACC == 0
InstructionContainer instruction_handler_RETLA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 1 or
        line->tokens[1].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b0001000010;
    container.type_b.s = line->tokens[1].token.numeric;

    container.meta.is_valid = true;
    return container;
}

// PUSH/POP INSTRUCTIONS

// PUSHA
// push A
InstructionContainer instruction_handler_PUSHA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001001000;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// PUSHX
// push IX
InstructionContainer instruction_handler_PUSHX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001001001;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// PUSHY
// push IY
InstructionContainer instruction_handler_PUSHY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001001010;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// POPA
// pop A
InstructionContainer instruction_handler_POPA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001001100;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// POPX
// pop IX
InstructionContainer instruction_handler_POPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001001101;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// POPY
// pop IY
InstructionContainer instruction_handler_POPY(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0001001110;
    container.type_c.r = 0;
    container.type_c.t = 0;
    container.type_c.b = 0;

    container.meta.is_valid = true;
    return container;
}

// LOGICAL INSTRUCTIONS

// AND <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_AND(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b0001000010;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0010010100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}

// ANDX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
    }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010011000;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// ANDN <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010010110;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// ANDNX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010011010;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// ANDP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010010101;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// ANDPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010011001;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// ANDNP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDNP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010010111;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// ANDNPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ANDNPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }
    container.meta.configuration_type = c;
    container.type_c.op = 0b0010011011;
    container.type_c.r = line->tokens[1].token.numeric;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// CAND <r>,<b>
InstructionContainer instruction_handler_CAND(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_c.op = 0b0100000100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// CANDX <r>,<b>
InstructionContainer instruction_handler_CANDX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0100001000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// OR <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_OR(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b00101000;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0010100100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// ORX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010101000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ORN <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010100110;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ORNX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010101010;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ORP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010100101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ORPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010101001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ORNP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORNP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010100111;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ORNPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ORNPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010100111;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// XOR <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XOR(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b00101100;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0010110100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// XORX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010111000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// XORN <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORN(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010111000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// XORNX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORNX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010111010;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// XORP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010110101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// XORPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010111001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// XORNP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORNP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010110111;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// XORNPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_XORNPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0010111011;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// MATHEMATICAL INSTRUCTIONS

// ADD <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ADD(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b00110000;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0011000100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// ADDX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ADDX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011001000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ADDP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ADDP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011000101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// ADDPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_ADDPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011001001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// SUB <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_SUB(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b0011010100;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0011000100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// SUBX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_SUBX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011011000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// SUBP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_SUBP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011010101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// SUBPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_SUBPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011011001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// MUL <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_MUL(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b00111000;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0011100100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// MULX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_MULX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011101000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// MULP <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_MULP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011100101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// MULPX <r>,<b>,<t>,<d>
InstructionContainer instruction_handler_MULPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011101001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// DIV <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_DIV(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b00111100;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount != 8) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0011110100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
        container.type_c.t = line->tokens[5].token.numeric;
        container.type_c.d = line->tokens[7].token.boolean;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// DIVX <r>,<b>
InstructionContainer instruction_handler_DIVX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 8
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric
        or line->tokens[4].data.general_type != divider
        or line->tokens[5].data.general_type != numeric
        or line->tokens[6].data.general_type != divider
        or line->tokens[7].data.general_type != numeric
        or not line->tokens[7].data.valid_boolean) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011111000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// DIVP <r>,<b>
InstructionContainer instruction_handler_DIVP(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011110101;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}
// DIVPX <r>,<b>
InstructionContainer instruction_handler_DIVPX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0011111001;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.t = line->tokens[5].token.numeric;
    container.type_c.d = line->tokens[7].token.boolean;

    container.meta.is_valid = true;
    return container;
}

// COMPARISON INSTRUCTIONS

// GT <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_GT(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b01001000;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount == 4) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0100100100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// GTX <r>,<b>
InstructionContainer instruction_handler_GTX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0100101000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// GTE <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_GTE(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b01001011;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount == 4) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0100100110;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// GTEX <r>,<b>
InstructionContainer instruction_handler_GTEX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0100101010;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// EQ <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_EQ(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b01001100;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount == 4) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0100110100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// EQX <r>,<b>
InstructionContainer instruction_handler_EQX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0100111000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// NE <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_NE(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b01001111;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount == 4) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0100110110;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// NEX <r>,<b>
InstructionContainer instruction_handler_NEX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0100111010;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// LT <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_LT(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b01010000;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount == 4) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0101000100;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// LTX <r>,<b>
InstructionContainer instruction_handler_LTX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0101001000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// LTE <s>/<r>,<b>,<t>,<d>
InstructionContainer instruction_handler_LTE(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    if (line->token_amount == 2) {
        if (line->tokens[1].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = b;
        container.type_b.op = 0b01010011;
        container.type_b.s = line->tokens[1].token.numeric;
    }
    else if (line->token_amount == 4) {
        if (line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
            container.meta.is_valid = false;
            return container;
        }
        container.meta.configuration_type = c;
        container.type_c.op = 0b0101000110;
        container.type_c.r = line->tokens[1].token.numeric;
        container.type_c.b = line->tokens[3].token.numeric;
    }
    else {
        container.meta.is_valid = false;
        return container;
    }

    container.meta.is_valid = true;
    return container;
}
// LTEX <r>,<b>
InstructionContainer instruction_handler_LTEX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0101001010;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// EDO INSTRUCTION

// EDO
InstructionContainer instruction_handler_EDO(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b01000000;
    container.type_b.s = 0;

    container.meta.is_valid = true;
    return container;
}

// SHIFT INSTRUCTIONS

// SHLA
InstructionContainer instruction_handler_SHLA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b01011000;
    container.type_b.s = 0;

    container.meta.is_valid = true;
    return container;
}
// SHL <r>,<b>
InstructionContainer instruction_handler_SHL(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0101100100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}
// SHLX <r>,<b>
InstructionContainer instruction_handler_SHLX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0101101000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// SHRA
InstructionContainer instruction_handler_SHRA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b01011100;
    container.type_b.s = 0;

    container.meta.is_valid = true;
    return container;
}
// SHR <r>,<b>
InstructionContainer instruction_handler_SHR(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0101110100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}
// SHRX <r>,<b>
InstructionContainer instruction_handler_SHRX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0101111000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// ROTATE INSTRUCTIONS

// ROLA
InstructionContainer instruction_handler_ROLA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b01100000;
    container.type_b.s = 0;

    container.meta.is_valid = true;
    return container;
}
// ROL <r>,<b>
InstructionContainer instruction_handler_ROL(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0110000100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}
// ROLX <r>,<b>
InstructionContainer instruction_handler_ROLX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0110001000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

// RORA
InstructionContainer instruction_handler_RORA(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = b;
    if (line->token_amount != 1) {
        container.meta.is_valid = false;
        return container;
    }

    container.type_b.op = 0b01100100;
    container.type_b.s = 0;

    container.meta.is_valid = true;
    return container;
}
// ROR <r>,<b>
InstructionContainer instruction_handler_ROR(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0110010100;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}
// RORX <r>,<b>
InstructionContainer instruction_handler_RORX(LexerLine* line, Translator* translator) {
    InstructionContainer container;
    container.meta.configuration_type = c;
    if (line->token_amount != 4
        or line->tokens[1].data.general_type != numeric
        or line->tokens[2].data.general_type != divider
        or line->tokens[3].data.general_type != numeric) {
        container.meta.is_valid = false;
        return container;
        }

    container.type_c.op = 0b0110011000;
    container.type_c.r = line->tokens[1].token.address;
    container.type_c.b = line->tokens[3].token.numeric;
    container.type_c.d = 0;
    container.type_c.t = 0;

    container.meta.is_valid = true;
    return container;
}

void add_instruction_handlers(Translator* translator) {
    TranslatorEntry entry;
    // load instructions
    entry.content.called_function = &instruction_handler_LDIX;
    translator_add(translator, "LDIX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_LDIY;
    translator_add(translator, "LDIY", 4, entry, 0);
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
    entry.content.called_function = &instruction_handler_LDAY;
    translator_add(translator, "LDAY", 4, entry, 0);
    entry.content.called_function = &instruction_handler_LDANY;
    translator_add(translator, "LDANY", 5, entry, 0);
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
    entry.content.called_function = &instruction_handler_STY;
    translator_add(translator, "STY", 3, entry, 0);
    entry.content.called_function = &instruction_handler_STNY;
    translator_add(translator, "STNY", 4, entry, 0);
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
    entry.content.called_function = &instruction_handler_CSTY;
    translator_add(translator, "CSTY", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CSTNY;
    translator_add(translator, "CSTNY", 5, entry, 0);
    // bit set/reset instructions
    entry.content.called_function = &instruction_handler_S;
    translator_add(translator, "S", 1, entry, 0);
    entry.content.called_function = &instruction_handler_SX;
    translator_add(translator, "SX", 2, entry, 0);
    entry.content.called_function = &instruction_handler_SY;
    translator_add(translator, "SY", 2, entry, 0);
    entry.content.called_function = &instruction_handler_R;
    translator_add(translator, "R", 1, entry, 0);
    entry.content.called_function = &instruction_handler_RX;
    translator_add(translator, "RX", 2, entry, 0);
    entry.content.called_function = &instruction_handler_RY;
    translator_add(translator, "RY", 2, entry, 0);
    // jump instructions
    entry.content.called_function = &instruction_handler_JMP;
    translator_add(translator, "JMP", 3, entry, 0);
    entry.content.called_function = &instruction_handler_JMPC;
    translator_add(translator, "JMPC", 4, entry, 0);
    entry.content.called_function = &instruction_handler_JMPCN;
    translator_add(translator, "JMPCN", 5, entry, 0);
    entry.content.called_function = &instruction_handler_RJMP;
    translator_add(translator, "RJMP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_RJMPC;
    translator_add(translator, "RJMPC", 5, entry, 0);
    entry.content.called_function = &instruction_handler_RJMPCN;
    translator_add(translator, "RJMPCN", 6, entry, 0);
    entry.content.called_function = &instruction_handler_CALL;
    translator_add(translator, "CALL", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CALLC;
    translator_add(translator, "CALLC", 5, entry, 0);
    entry.content.called_function = &instruction_handler_CALLCN;
    translator_add(translator, "CALLCN", 6, entry, 0);
    entry.content.called_function = &instruction_handler_RET;
    translator_add(translator, "RET", 3, entry, 0);
    entry.content.called_function = &instruction_handler_RETC;
    translator_add(translator, "RETC", 4, entry, 0);
    entry.content.called_function = &instruction_handler_RETCN;
    translator_add(translator, "RETCN", 5, entry, 0);
    entry.content.called_function = &instruction_handler_RETLA;
    translator_add(translator, "RETLA", 5, entry, 0);
    // push/pop instructions
    entry.content.called_function = &instruction_handler_PUSHA;
    translator_add(translator, "PUSHA", 5, entry, 0);
    entry.content.called_function = &instruction_handler_PUSHX;
    translator_add(translator, "PUSHX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_PUSHY;
    translator_add(translator, "PUSHY", 5, entry, 0);
    entry.content.called_function = &instruction_handler_POPA;
    translator_add(translator, "POPA", 4, entry, 0);
    entry.content.called_function = &instruction_handler_POPX;
    translator_add(translator, "POPX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_POPY;
    translator_add(translator, "POPY", 4, entry, 0);
    // logical instructions
    entry.content.called_function = &instruction_handler_AND;
    translator_add(translator, "AND", 3, entry, 0);
    entry.content.called_function = &instruction_handler_ANDX;
    translator_add(translator, "ANDX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ANDN;
    translator_add(translator, "ANDN", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ANDNX;
    translator_add(translator, "ANDNX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_ANDP;
    translator_add(translator, "ANDP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ANDPX;
    translator_add(translator, "ANDPX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_ANDNP;
    translator_add(translator, "ANDNP", 5, entry, 0);
    entry.content.called_function = &instruction_handler_ANDNPX;
    translator_add(translator, "ANDNPX", 6, entry, 0);
    entry.content.called_function = &instruction_handler_CAND;
    translator_add(translator, "CAND", 4, entry, 0);
    entry.content.called_function = &instruction_handler_CANDX;
    translator_add(translator, "CANDX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_OR;
    translator_add(translator, "OR", 2, entry, 0);
    entry.content.called_function = &instruction_handler_ORX;
    translator_add(translator, "ORX", 3, entry, 0);
    entry.content.called_function = &instruction_handler_ORN;
    translator_add(translator, "ORN", 3, entry, 0);
    entry.content.called_function = &instruction_handler_ORNX;
    translator_add(translator, "ORNX",  4, entry, 0);
    entry.content.called_function = &instruction_handler_ORP;
    translator_add(translator, "ORP", 3, entry, 0);
    entry.content.called_function = &instruction_handler_ORPX;
    translator_add(translator, "ORPX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ORNP;
    translator_add(translator, "ORNP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ORNPX;
    translator_add(translator, "ORNPX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_XOR;
    translator_add(translator, "XOR", 3, entry, 0);
    entry.content.called_function = &instruction_handler_XORX;
    translator_add(translator, "XORX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_XORN;
    translator_add(translator, "XORN", 4, entry, 0);
    entry.content.called_function = &instruction_handler_XORNX;
    translator_add(translator, "XORNX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_XORP;
    translator_add(translator, "XORP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_XORPX;
    translator_add(translator, "XORPX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_XORNP;
    translator_add(translator, "XORNP", 5, entry, 0);
    entry.content.called_function = &instruction_handler_XORNPX;
    translator_add(translator, "XORNPX", 6, entry, 0);
    // mathematical instructions
    entry.content.called_function = &instruction_handler_ADD;
    translator_add(translator, "ADD", 3, entry, 0);
    entry.content.called_function = &instruction_handler_ADDX;
    translator_add(translator, "ADDX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ADDP;
    translator_add(translator, "ADDP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ADDPX;
    translator_add(translator, "ADDPX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_SUB;
    translator_add(translator, "SUB", 3, entry, 0);
    entry.content.called_function = &instruction_handler_SUBX;
    translator_add(translator, "SUBX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_SUBP;
    translator_add(translator, "SUBP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_SUBPX;
    translator_add(translator, "SUBPX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_MUL;
    translator_add(translator, "MUL", 3, entry, 0);
    entry.content.called_function = &instruction_handler_MULX;
    translator_add(translator, "MULX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_MULP;
    translator_add(translator, "MULP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_MULPX;
    translator_add(translator, "MULPX", 5, entry, 0);
    entry.content.called_function = &instruction_handler_DIV;
    translator_add(translator, "DIV", 3, entry, 0);
    entry.content.called_function = &instruction_handler_DIVX;
    translator_add(translator, "DIVX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_DIVP;
    translator_add(translator, "DIVP", 4, entry, 0);
    entry.content.called_function = &instruction_handler_DIVPX;
    translator_add(translator, "DIVPX", 5, entry, 0);
    // comparison instructions
    entry.content.called_function = &instruction_handler_GT;
    translator_add(translator, "GT", 2, entry, 0);
    entry.content.called_function = &instruction_handler_GTX;
    translator_add(translator, "GTX", 3, entry, 0);
    entry.content.called_function = &instruction_handler_GTE;
    translator_add(translator, "GTE", 3, entry, 0);
    entry.content.called_function = &instruction_handler_GTEX;
    translator_add(translator, "GTEX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_EQ;
    translator_add(translator, "EQ", 2, entry, 0);
    entry.content.called_function = &instruction_handler_EQX;
    translator_add(translator, "EQX", 3, entry, 0);
    entry.content.called_function = &instruction_handler_NE;
    translator_add(translator, "NE", 2, entry, 0);
    entry.content.called_function = &instruction_handler_NEX;
    translator_add(translator, "NEX", 3, entry, 0);
    entry.content.called_function = &instruction_handler_LT;
    translator_add(translator, "LT", 2, entry, 0);
    entry.content.called_function = &instruction_handler_LTX;
    translator_add(translator, "LTX", 3, entry, 0);
    entry.content.called_function = &instruction_handler_LTE;
    translator_add(translator, "LTE", 3, entry, 0);
    entry.content.called_function = &instruction_handler_LTEX;
    translator_add(translator, "LTEX", 4, entry, 0);
    // EDO
    entry.content.called_function = &instruction_handler_EDO;
    translator_add(translator, "EDO", 3, entry, 0);
    // shift instructions
    entry.content.called_function = &instruction_handler_SHLA;
    translator_add(translator, "SHLA", 4, entry, 0);
    entry.content.called_function = &instruction_handler_SHL;
    translator_add(translator, "SHL", 3, entry, 0);
    entry.content.called_function = &instruction_handler_SHLX;
    translator_add(translator, "SHLX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_SHRA;
    translator_add(translator, "SHRA", 4, entry, 0);
    entry.content.called_function = &instruction_handler_SHR;
    translator_add(translator, "SHR", 3, entry, 0);
    entry.content.called_function = &instruction_handler_SHRX;
    translator_add(translator, "SHRX", 4, entry, 0);
    // rotate instructions
    entry.content.called_function = &instruction_handler_ROLA;
    translator_add(translator, "ROLA", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ROL;
    translator_add(translator, "ROL", 3, entry, 0);
    entry.content.called_function = &instruction_handler_ROLX;
    translator_add(translator, "ROLX", 4, entry, 0);
    entry.content.called_function = &instruction_handler_RORA;
    translator_add(translator, "RORA", 4, entry, 0);
    entry.content.called_function = &instruction_handler_ROR;
    translator_add(translator, "ROR", 3, entry, 0);
    entry.content.called_function = &instruction_handler_RORX;
    translator_add(translator, "RORX", 4, entry, 0);
}