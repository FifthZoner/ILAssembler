#include "parse_arguments.h"

#include <stdint.h>
#include <stdio.h>

const CommandArguments parse_command_arguments(int argc, const char** argv) {
    CommandArguments args;

    // TODO: add flags as needed
    if (argc == 1) {
        args.source_file = nullptr;
        printf("Aborted: invalid target path!\n");
        return args;
    }

    // TODO: add loop here to take files and flags
    //for (uint32_t n = 1; n < argc; n++) {
    //
    //}

    args.source_file = argv[1];
    return args;
}
