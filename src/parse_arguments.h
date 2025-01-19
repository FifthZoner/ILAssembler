#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H
#include <stdint.h>

typedef struct  {
    const char* source_file;
    const char* output_file;
    uint8_t splitting_by_dot;
    uint8_t display_help;
    uint8_t error;
}CommandArguments;

const CommandArguments parse_command_arguments(int argc, const char** argv);

#endif //PARSE_ARGUMENTS_H
