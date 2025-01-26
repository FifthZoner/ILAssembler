#include "lexer.h"

#include <ctype.h>
#include <iso646.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

// loosely based on
// https://cache.industry.siemens.com/dl/files/748/109476748/att_845621/v1/IEC_61131_compliance_en_US.pdf
// as the proposed language seems to have different functionality

// Update the defines after modifying values below!
#define LINE_BUFFER 512

#define WHITE_SPACE_CHARACTERS_AMOUNT 3
struct Translator;
constexpr char white_space_characters[WHITE_SPACE_CHARACTERS_AMOUNT] = { ' ', '\t', '\n' };

#define SPLITTING_CHARACTERS_AMOUNT 5
constexpr char splitting_characters[SPLITTING_CHARACTERS_AMOUNT] = { '.', ',', '#', ':', ';' };

// IL seems to only support one line comments
#define COMMENT_STRING_LENGTH 2
const char* comment_string = "//";

#define REAL_NUMBER_DIVIDER 'f'

char instruction_dividing_character = ',';

// used to offset label addresses as they are not actually in code
uint64_t label_amount = 0;
uint64_t program_start_offset = 0;

bool detect_token_types(LexerLine* line, struct Translator* translator, uint64_t index) {
    // first let's do initial preprocessing like length calculation and letter case change
    for (uint32_t current_token_index = 0; current_token_index < line->token_amount; current_token_index++) {
        LexerToken* current_token = line->tokens + current_token_index;
        current_token->length = strnlen(current_token->token.text, LINE_BUFFER);

        // TODO: determine whether or not co convert all tokens into uppercase like in FD, for now all will be uppercase
        // lower case a, b, c ???
        for (uint32_t n = 0; n < current_token->length; n++) {
            current_token->token.text[n] = (char)toupper(current_token->token.text[n]);
        }


        // numeric checks, could probably be made more efficient

        // checking for invalid negative
        current_token->data.valid_numeric = true;
        current_token->data.is_copied = false;
        for (uint32_t n = 0; n < current_token->length; n++) {
            if (current_token->token.text[n] == '-' and n != 0) {
                current_token->data.valid_numeric = false;
                current_token->data.valid_binary = false;
                current_token->data.valid_octal = false;
                current_token->data.valid_hex = false;
                current_token->data.valid_decimal = false;
                current_token->data.valid_boolean = false;
                current_token->data.valid_real = false;
                break;
            }
        }
        if (not current_token->data.valid_numeric) {
            continue;
        }

        // initial
        current_token->data.valid_binary = false;
        current_token->data.valid_octal = false;
        current_token->data.valid_hex = false;
        current_token->data.valid_decimal = true;
        current_token->data.valid_boolean = false;
        current_token->data.valid_real = true;

        // checking for booleans
        if (current_token->length == 1) {
            if (current_token->token.text[0] == '0' or current_token->token.text[0] == '1') {
                current_token->data.valid_boolean = true;
            }
        }
        else if (current_token->length == 4) {
            if (strncmp(current_token->token.text, "TRUE", 4) == 0) {
                current_token->data.valid_boolean = true;
                current_token->data.valid_numeric = false;
                current_token->data.valid_binary = false;
                current_token->data.valid_octal = false;
                current_token->data.valid_hex = false;
                current_token->data.valid_decimal = false;
                current_token->data.valid_real = false;
                current_token->token.text[0] = '1';
                current_token->token.text[1] = '\0';
                current_token->length = 1;
                continue;
            }
        }
        else if (current_token->length == 5) {
            if (strncmp(current_token->token.text, "FALSE", 5) == 0) {
                current_token->data.valid_boolean = true;
                current_token->data.valid_numeric = false;
                current_token->data.valid_binary = false;
                current_token->data.valid_octal = false;
                current_token->data.valid_hex = false;
                current_token->data.valid_decimal = false;
                current_token->data.valid_real = false;
                current_token->token.text[0] = '0';
                current_token->token.text[1] = '\0';
                current_token->length = 1;
                continue;
            }
        }

        // checking for decimals
        for (uint32_t n = 0; n < current_token->length; n++) {
            if ((current_token->token.text[n] < '0' or current_token->token.text[n] > '9') and current_token->token.text[n] != '-') {
                current_token->data.valid_decimal = false;
                break;
            }
        }

        // checking for real numbers
        bool found_real_divider = false;
        for (uint32_t n = 0; n < current_token->length; n++) {
            if (current_token->token.text[n] == REAL_NUMBER_DIVIDER) {
                if (found_real_divider) {
                    current_token->data.valid_real = false;
                    break;
                }
                found_real_divider = true;
                continue;
            }
            if ((current_token->token.text[n] < '0' or current_token->token.text[n] > '9') and current_token->token.text[n] != '-') {
                current_token->data.valid_real = false;
                break;
            }
        }

        // checking for base 2/8/16 validity in 0(x/o/b)<number> format
        if (current_token->length > 2 and current_token->token.text[0] == '0') {
            switch (current_token->token.text[1]) {
                case 'X':
                    current_token->data.valid_hex = true;
                    for (uint32_t n = 2; n < current_token->length; n++) {
                        if ((current_token->token.text[n] < '0' or current_token->token.text[n] > '9')
                        and (current_token->token.text[n] > 'F' or current_token->token.text[n] < 'A')) {
                            current_token->data.valid_hex = false;
                            break;
                        }
                    }
                    break;
                case 'O':
                    current_token->data.valid_octal = true;
                    for (uint32_t n = 2; n < current_token->length; n++) {
                        if (current_token->token.text[n] < '0' or current_token->token.text[n] > '7') {
                            current_token->data.valid_octal = false;
                            break;
                        }
                    }
                    break;
                case 'B':
                    current_token->data.valid_binary = true;
                    for (uint32_t n = 2; n < current_token->length; n++) {
                        if (current_token->token.text[n] != '1' and current_token->token.text[n] != '0') {
                            current_token->data.valid_binary = false;
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        current_token->data.valid_numeric = current_token->data.valid_binary | current_token->data.valid_octal | current_token->data.valid_hex | current_token->data.valid_decimal | current_token->data.valid_real;
    }

    // checking for labels
    if (line->token_amount == 2) {
        if (line->tokens[1].length == 1 and line->tokens[1].token.text[0] == ':') {
            // if the line is a label it needs to be inserted into the label translator
            TranslatorEntry entry;
            entry.content.jump_address = index - label_amount++;
            entry.is_variable = false;
            entry.is_jump_label = true;
            line->tokens[0].data.general_type = jump_label + program_start_offset;
            translator_add(translator, line->tokens[0].token.text, line->tokens[0].length, entry, 0);
            return true;
        }
    }

    // now context aware token analysis can start
    for (uint32_t current_token_index = 0; current_token_index < line->token_amount; current_token_index++) {
        LexerToken* current_token = line->tokens + current_token_index;

        if (current_token->length == 1 and current_token->token.text[0] == instruction_dividing_character) {
            free(current_token->token.text);
            current_token->token.text = nullptr;
            current_token->length = 0;
            current_token->data.general_type = divider;
            continue;
        }

        if (current_token->data.valid_boolean) {
            const int32_t value = current_token->token.text[0] - '0';
            free(current_token->token.text);
            current_token->token.text = nullptr;
            current_token->token.boolean = value;
            current_token->length = 0;
            current_token->data.general_type = numeric;
            current_token->data.numeric_type = boolean;
            continue;
        }

        // now the other cases
        if (current_token_index == 0 and not current_token->data.valid_numeric) {
            current_token->data.general_type = instruction;
            continue;
        }
        if (not current_token->data.valid_numeric) {
            if (line->tokens[0].length >= 3 and strncmp(line->tokens[0].token.text, "JMP", 3) == 0) {
                current_token->data.general_type = jump_label;
            }
            else {
                if (current_token->length == 2 and current_token->token.text[0] == 'I' and current_token->token.text[1] == 'Y') {
                    current_token->data.general_type = IY;
                }
                else  if (current_token->length == 3 and current_token->token.text[0] == 'E' and current_token->token.text[1] == 'Q'  and current_token->token.text[2] == 'U') {
                    current_token->data.general_type = EQU;
                }
                else {
                    current_token->data.general_type = variable;
                }
            }
            continue;
        }

        if (current_token->data.valid_numeric) {
            if (current_token->data.valid_decimal) {
                const int32_t value = (int32_t)strtol(current_token->token.text, nullptr, 10);
                free(current_token->token.text);
                current_token->token.text = nullptr;
                current_token->token.integer = value;
                current_token->length = 0;
                current_token->data.general_type = numeric;
                current_token->data.numeric_type = integer;
                continue;
            }

            if (current_token->data.valid_real) {
                const float value = strtof(current_token->token.text, nullptr);
                free(current_token->token.text);
                current_token->token.text = nullptr;
                current_token->token.real = value;
                current_token->length = 0;
                current_token->data.general_type = numeric;
                current_token->data.numeric_type = real;
                continue;
            }

            if (current_token->data.valid_hex) {
                const int32_t value = (int32_t)strtoul(current_token->token.text, nullptr, 16);
                free(current_token->token.text);
                current_token->token.text = nullptr;
                current_token->token.hex = value;
                current_token->length = 0;
                current_token->data.general_type = numeric;
                current_token->data.numeric_type = hex;
                continue;
            }

            if (current_token->data.valid_octal) {
                const int32_t value = (int32_t)strtoul(current_token->token.text, nullptr, 8);
                free(current_token->token.text);
                current_token->token.text = nullptr;
                current_token->token.oct = value;
                current_token->length = 0;
                current_token->data.general_type = numeric;
                current_token->data.numeric_type = oct;
                continue;
            }

            if (current_token->data.valid_binary) {
                const int32_t value = (int32_t)strtoul(current_token->token.text, nullptr, 2);
                free(current_token->token.text);
                current_token->token.text = nullptr;
                current_token->token.bin = value;
                current_token->length = 0;
                current_token->data.general_type = numeric;
                current_token->data.numeric_type = bin;
                continue;
            }
        }

        return false;
    }

    return true;
}

void add_token(const char* address, const uint32_t length, LexerLine* line) {
    // if there was something there isolate it
    if (line->capacity == line->token_amount) {
        line->capacity *= 2;
        LexerToken* temp = (LexerToken*)malloc(sizeof(LexerToken) * line->capacity);
        memcpy(temp, line->tokens, sizeof(LexerToken) * line->token_amount);
        // TODO: figure out why this causes a segfault (double free)
        //free(line->tokens);
        line->tokens = temp;
    }

    line->tokens[line->token_amount].length = length;
    char* temp = (char*)malloc((length + 1) * sizeof(char));
    strncpy(temp, address, length);
    temp[length] = '\0';
    line->tokens[line->token_amount++].token.text = temp;
}

LexerLine split_line(char* line, struct Translator* translator, uint64_t index) {
    // the main lexer function actually
    // takes the line and changes it into tokens

    LexerLine output;
    output.token_amount = 0;
    output.capacity = 2;
    output.tokens = (LexerToken*)malloc(2 * sizeof(LexerToken));
    uint32_t line_length = strnlen(line, LINE_BUFFER);

    // now that it's ready for data let's analyse the line
    // FEATURE: different encoding support like UTF-8 could be added here
    for (uint32_t current_index = 0, start = 0; current_index < line_length; current_index++) {
        bool is_whitespace = false;
        for (uint32_t n = 0; n < WHITE_SPACE_CHARACTERS_AMOUNT; n++) {
            if (line[current_index] == white_space_characters[n]) {
                is_whitespace = true;
                break;
            }
        }

        // if there was only a white space continue
        if (is_whitespace and start == current_index) {
            start++;
            continue;
        }

        bool found_splitting = false;
        // if it's a splitting character we also need to add it's token to the line
        for (uint32_t n = 0; n < SPLITTING_CHARACTERS_AMOUNT; n++) {
            if (line[current_index] == splitting_characters[n]) {
                found_splitting = true;
                break;
            }
        }

        if (found_splitting) {
            add_token(line + start, current_index - start, &output);
            add_token(line + current_index, 1, &output);
            start = current_index + 1;
            continue;
        }

        if (not is_whitespace and current_index != line_length - 1) {
            continue;
        }

        if (is_whitespace) {
            add_token(line + start, current_index - start, &output);
        }
        else {
            add_token(line + start, current_index - start + 1, &output);
        }

        start = current_index + 1;
    }

    if (not detect_token_types(&output, translator, index)) {
        printf("Error: could not proceed during token type detection!\n");
        // TODO: there is a more complex case with deallocation here, will be skipped for now
        output.capacity = 0;
        output.token_amount = 1;
        return output;
    }

    // detecting EQU statements
    if (output.token_amount > 2 and output.tokens[0].data.general_type == instruction and output.tokens[1].data.general_type == EQU) {
        // move the tokens after EQU into a variable entry and insert it into the translator
        TranslatorEntry entry;
        entry.is_variable = true;
        entry.is_jump_label = false;
        entry.content.variable = (VariableEntry*)malloc(sizeof(VariableEntry));
        entry.content.variable->token_amount = output.token_amount - 2;
        entry.content.variable->tokens = (LexerToken*)malloc(entry.content.variable->token_amount * sizeof(LexerToken));
        for (uint32_t n = 2; n < output.token_amount; n++) {
            entry.content.variable->tokens[n - 2] = output.tokens[n];
        }
        translator_add(translator, output.tokens->token.text, output.tokens->length, entry, 0);

        free(output.tokens[0].token.text);
        free(output.tokens[1].token.text);
        free(output.tokens);
        output.capacity = 0;
        output.token_amount = 0;
    }

    return output;
}

bool lex_file(const CommandArguments* arguments, FILE* file, LexerOutput* output, LexerFiles* files, struct Translator* translator) {
    // might want to put that to the function below
    const auto line = (char*)malloc(LINE_BUFFER * sizeof(char));
    while (fgets(line, LINE_BUFFER, file)) {

        // check if it's a comment
        if (strncmp(line, comment_string, COMMENT_STRING_LENGTH) == 0 or line[0] == '\n') {
            continue;
        }

        LexerLine split = split_line(line, translator, output->lines_amount);;
        if (split.token_amount == 0) {
            continue;
        }
        if (split.capacity == 0 and split.token_amount == 1) {
            split.token_amount = 0;
            return false;
        }

        if (output->capacity == output->lines_amount) {
            // in that case more space is needed, let's double it
            if (output->capacity == 0) {
                output->lines = (LexerLine*)malloc(sizeof(LexerLine));
                output->capacity = 1;
            }
            else {
                output->lines = (LexerLine*)realloc(output->lines, sizeof(LexerLine) * output->capacity * 2);
                output->capacity *= 2;
            }
        }

        output->lines[output->lines_amount++] = split;

        // FEATURE: data about line's position in file could be added here
    }
    free(line);
    return true;
}

LexerOutput run_lexer(const CommandArguments* arguments, LexerFiles* files, struct Translator* translator) {
    LexerOutput output;
    output.capacity = 0;
    output.lines_amount = 0;
    output.lines = nullptr;

    // preparing things from arguments
    if (arguments->splitting_by_dot) {
        instruction_dividing_character = '.';
    }
    program_start_offset = arguments->start_address;

    files->files = (char**)malloc(sizeof(char*));
    files->capacity = 1;
    files->file_amount = 1;
    files->files[0] = (char*)arguments->source_file;

    for (uint64_t file_index = 0; file_index < files->file_amount; file_index++) {
        FILE* current = fopen(files->files[file_index], "r");

        if (current == nullptr) {
            printf("Error: File \"%s\" could not be opened!\n", files->files[file_index]);
            free_lexer_output(&output);
            output.lines_amount = 0;
            return output;
        }

        if (not lex_file(arguments, current, &output, files, translator)) {
            printf("Error: File \"%s\" could not be converted by lexer!\n", files->files[file_index]);
            if (output.capacity > 0) {
                free(output.lines);
            }
            output.lines_amount = 0;
            fclose(current);
            return output;
        }
    }

    // translating variables
    for (uint64_t n = 0; n < output.lines_amount; n++) {
        for (uint32_t m = 1; m < output.lines[n].token_amount; m++) {
            if (output.lines[n].tokens[m].data.general_type == variable) {
                // find the variable and replace it with proper tokens
                TranslatorEntry* result = translator_get(translator, output.lines[n].tokens[m].token.text, output.lines[n].tokens[m].length, 0);
                if (result == nullptr or not result->is_variable) {
                    printf("Error: variable identifier not found!\n");
                    return output;
                }
                // inputting the new values
                uint32_t new_size = output.lines[n].token_amount + result->content.variable->token_amount - 1;
                uint32_t delta = new_size - output.lines[n].token_amount;
                if (output.lines[n].capacity < new_size) {
                    output.lines[n].tokens = (LexerToken*)realloc(output.lines[n].tokens, sizeof(LexerToken) * new_size);
                    output.lines[n].capacity = new_size;
                }

                for (uint32_t k = new_size - 1, l = 1; l < output.lines[n].token_amount - m; k--, l++) {
                    output.lines[n].tokens[k] = output.lines[n].tokens[k - delta + 1];
                }
                for (uint32_t k = m, l = 0; l < result->content.variable->token_amount; k++, l++) {
                    output.lines[n].tokens[k] = result->content.variable->tokens[l];
                    output.lines[n].tokens[k].data.is_copied = true; // thanks to that it's memory will not be freed
                }
                output.lines[n].token_amount = new_size;
            }
        }
    }
    return output;
}


// freeing functions
void free_lexer_token(LexerToken* token) {
    if (not token->data.is_copied) {
        if (token->data.general_type != numeric and token->token.text != nullptr) {
            free(token->token.text);
            token->token.text = nullptr;
        }
    }
}

void free_lexer_line(LexerLine* line) {
    for (uint64_t n = 0; n < line->token_amount; n++) {
        free_lexer_token(line->tokens + n);
    }
    if (line->token_amount > 0) {
        free(line->tokens);
        line->tokens = nullptr;
    }
}

void free_lexer_output(LexerOutput* output) {
    for (uint64_t n = 0; n < output->lines_amount; n++) {
        free_lexer_line(output->lines + n);
    }
    if (output->lines_amount > 0) {
        free(output->lines);
        output->lines = nullptr;
    }
}