#include "parse_arguments.h"

#include <iso646.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARGUMENT_LENGTH 1024

const CommandArguments parse_command_arguments(int argc, const char** argv) {
    CommandArguments args;
    args.source_file = nullptr;
    args.output_file = nullptr;
    args.splitting_by_dot = false;
    args.display_help = false;
    args.error = false;

    for (uint32_t n = 1; n < argc; n++) {

        uint32_t length = strnlen(argv[n], MAX_ARGUMENT_LENGTH);

        // the last path passed will be used as source
        if (length > 0 and argv[n][0] != '-') {
            if (args.source_file != nullptr) {
                if (args.output_file != nullptr) {
                    args.error = true;
                    return args;
                }
                args.output_file = argv[n];
            }
            else {
                args.source_file = argv[n];
            }
            continue;
        }

        // arguments
        if (length > 1 and argv[n][0] == '-') {
            // one letter arguments
            if (argv[n][1] != '-') {
                for (uint32_t m = 1; m < length; m++) {
                    switch (argv[n][m]) {
                        // split by comma
                        case 'c':
                            args.splitting_by_dot = false;
                        break;
                        case 'd':
                            args.splitting_by_dot = true;
                        break;
                        case 'h':
                            args.display_help = true;
                        break;
                        default:
                            args.error = true;
                        return args;
                    }
                }
            }
        }
    }

    if (args.source_file == nullptr) {
        args.error = true;
        return args;
    }

    return args;
}
