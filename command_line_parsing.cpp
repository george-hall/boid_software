#include <iostream>
#include <string>

#include <cstring>

#include "command_line_parsing.hpp"

// Options:
//  * Board width
//  * Board height
//  * Num boids
//  * Max speed (will do later)
//  * Neighbourhood size (will do later)
//  * Verbose
//  * Help

argument_struct parse_args(int argc, char **argv) {

    argument_struct args;

    // Set struct members to default values
    args.board_width = 400;
    args.board_height = 400;
    args.num_boids = 5;
    args.verbose = false;

    for (int i = 1; i < argc; i++) {

        // Board width
        if (!strcmp(argv[i], "--board-width") || !strcmp(argv[i], "-w")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: board width must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                args.board_width = (unsigned int) strtoul(argv[++i], NULL, 10);
                if (args.board_width == 0) {
                    std::cout << "ERROR: board width must be a positive integer" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Board height
        else if (!strcmp(argv[i], "--board-height") || !strcmp(argv[i], "-h")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: board height must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                args.board_height = (unsigned int) strtoul(argv[++i], NULL, 10);
                if (args.board_height == 0) {
                    std::cout << "ERROR: board height must be a positive integer" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Number of boids
        else if (!strcmp(argv[i], "--num-boids") || !strcmp(argv[i], "-n")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: number of boids must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                args.num_boids = (unsigned int) strtoul(argv[++i], NULL, 10);
                if (args.num_boids == 0) {
                    std::cout << "ERROR: number of boids must be a positive integer" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Verbosity
        else if (!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-v")) {
            args.verbose = true;
        }

        // Argument not recognised
        else {
            std::cout << "ERROR: Argument '" << argv[i] << "' not recognised" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    return args;
}
