#include "parse_arguments.h"

#include <ctype.h>
#include <iso646.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const CommandArguments parse_command_arguments(int argc, const char** argv) {
    CommandArguments args;
    args.start_address = 0;
    args.source_file = nullptr;
    args.output_file = nullptr;
    args.splitting_by_dot = false;
    args.display_help = false;
    args.error = false;

    bool must_be_number = false;
    for (uint32_t n = 1; n < argc; n++) {

        uint32_t length = strnlen(argv[n], MAX_ARGUMENT_LENGTH);

        if (must_be_number) {
            if (length > 3 and argv[n][0] == '0' and argv[n][1] == 'x') {
                // hex number
                for (uint32_t k = 2; k < length; k++) {
                    char letter = toupper(argv[n][k]);
                    if ((letter < '0' or letter > '9') and (letter < 'A' or letter > 'F')) {
                        printf("Error: invalid hexadecimal format in argument!\n");
                        args.error = true;
                        return args;
                    }
                }

                // if it got there then the number is correct and can be converted
                args.start_address = strtoull(argv[n] + 2, nullptr, 16);
            }
            else {
                for (uint32_t k = 0; k < length; k++) {
                    if (argv[n][k] < '0' or argv[n][k] > '9') {
                        printf("Error: invalid decimal format in argument!\n");
                        args.error = true;
                        return args;
                    }
                }
                args.start_address = strtoull(argv[n], nullptr, 10);
            }

            must_be_number = false;
            continue;
        }

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
        if (length == 2 and argv[n][0] == '-') {
            // one letter arguments
            switch (argv[n][1]) {
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
                case 's':
                    // the next argument must be a number
                    if (n == argc - 1) {
                        printf("Error: expected an argument after size flag!\n");
                        args.error = true;
                        return args;
                    }
                    must_be_number = true;
                break;
                default:
                    args.error = true;
                return args;
            }
        }
    }

    if (args.source_file == nullptr) {
        args.error = true;
        return args;
    }

    return args;
}
