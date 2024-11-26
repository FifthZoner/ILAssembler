#include "parse_arguments.h"

#include <stdio.h>

const CommandArguments parse_command_arguments(int argc, const char** argv) {
    CommandArguments args;

    // TODO: add flags as needed
    if (argc != 2) {
        args.source_file = nullptr;
        printf("Aborted: invalid target path!\n");
        return args;
    }
    args.source_file = argv[1];
    return args;
}
