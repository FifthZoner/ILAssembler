#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

typedef struct  {
    const char* source_file;
}CommandArguments;

const CommandArguments parse_command_arguments(int argc, const char** argv);

#endif //PARSE_ARGUMENTS_H
