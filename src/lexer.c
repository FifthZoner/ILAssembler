#include "lexer.h"

#include <iso646.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER 512

#define WHITE_SPACE_CHARACTERS_AMOUNT 2
const char white_space_characters[WHITE_SPACE_CHARACTERS_AMOUNT] = { ' ', '\t' };
const char comment_character = ';';

bool prepare_token(char* token, uint32_t length, LexerToken* location) {

    return true;
}

LexerLine split_line(char* line) {
    // the main lexer function actually
    // takes the line and changes it into tokens
    // TODO: ADD MEMORY DEALLOCATION AFTER ASSEMBLING

    LexerLine output;
    output.token_amount = 0;
    output.capacity = 2;
    output.tokens = (LexerToken*)malloc(2 * sizeof(LexerToken));
    uint32_t line_length = strnlen(line, LINE_BUFFER);

    // now that it's ready for data let's analyse the line
    // FEATURE: different encoding support like UTF-8 could be added here
    for (uint32_t current_index = 0, start = 0; current_index < line_length; current_index++) {
        bool is_white_space = false;
        for (uint32_t n = 0; n < WHITE_SPACE_CHARACTERS_AMOUNT; n++) {
            if (line[current_index] == white_space_characters[n]) {
                is_white_space = true;
                break;
            }
        }
        // if there was only a white space continue
        if (is_white_space and start == current_index) {
            start++;
            continue;
        }

        if (not is_white_space and current_index != line_length - 1) {
            continue;
        }

        // if there was something there isolate it
        if (output.capacity == output.token_amount) {
            output.capacity *= 2;
            output.tokens = (LexerToken*)realloc(output.tokens, sizeof(LexerToken) * output.capacity);
        }

        if (not prepare_token(line + start, current_index - start, output.tokens + output.token_amount)) {
            printf("Error: Lexer could not handle token, aborting!\n");
            free(output.tokens);
            output.token_amount = 0;
            output.capacity = 0;
            return output;
        }
        //output.tokens[output.token_amount].length = current_index - start;
        //char* temp = (char*)malloc((output.tokens[output.token_amount].length + 1) * sizeof(char));
        //strncpy(temp, line + start, output.tokens[output.token_amount].length);
        //temp[output.tokens[output.token_amount].length] = '\0';
        //output.tokens[output.token_amount++].token.text = temp;
        start = current_index + 1;
    }

    return output;
}

bool lex_file(const CommandArguments* arguments, FILE* file, LexerOutput* output, LexerFiles* files) {
    // might want to put that to the function below
    const auto line = (char*)malloc(LINE_BUFFER * sizeof(char));
    while (not feof(file)) {
        fgets(line, LINE_BUFFER, file);

        if (line[0] == comment_character) {
            continue;
        }

        if (output->capacity == output->lines_amount) {
            // in that case more space is needed, let's double it
            output->lines = (LexerLine*)realloc(output->lines, sizeof(LexerLine) * output->capacity * 2);
            output->capacity *= 2;
        }
        output->lines[output->lines_amount] = split_line(line);
        if (output->lines[output->lines_amount++].capacity == 0) {
            // TODO: add individual token freeing here
            free(line);
            return false;
        }

        // FEATURE: data about line's position in file could be added here
    }
    free(line);
    return true;
}

LexerOutput run_lexer(const CommandArguments* arguments, LexerFiles* files) {
    LexerOutput output;
    output.capacity = 0;
    output.lines_amount = 0;
    output.lines = nullptr;

    files->files = (char**)malloc(sizeof(char*));
    files->capacity = 1;
    files->file_amount = 1;
    files->files[0] = (char*)arguments->source_file;

    for (uint64_t file_index = 0; file_index < files->file_amount; file_index++) {
        FILE* current = fopen(files->files[file_index], "r");

        if (current == nullptr) {
            printf("Error: File \"%s\" could not be opened!\n", files->files[file_index]);
            if (output.capacity > 0) {
                free(output.lines);
            }
            output.lines_amount = 0;
            return output;
        }

        if (not lex_file(arguments, current, &output, files)) {
            printf("Error: File \"%s\" could not be converted by lexer!\n", files->files[file_index]);
            if (output.capacity > 0) {
                free(output.lines);
            }
            output.lines_amount = 0;
            fclose(current);
            return output;
        }
    }


    
    return output;
}
