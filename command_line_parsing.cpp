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
    args.board_width = 1000;
    args.board_height = 650;
    args.num_boids = 50;
    args.old_velocity_weight = 1.0f;
    args.avoidance_weight = 1.0f;
    args.cohesion_weight = 1.0f;
    args.alignment_weight = 1.0f;
    args.verbose = false;
    args.quiet = false;

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

        // Steer weights
        else if (!strcmp(argv[i], "--old-velocity-weight")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                float weight;
                weight = atof(argv[++i]);
                if (weight < 0) {
                    std::cout << "ERROR: " << argv[i-1] << " must be non-negative" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else {
                    args.old_velocity_weight = weight;
                }
            }
        }

        else if (!strcmp(argv[i], "--avoidance-weight")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                float weight;
                weight = atof(argv[++i]);
                if (weight < 0) {
                    std::cout << "ERROR: " << argv[i-1] << " must be non-negative" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else {
                    args.avoidance_weight = weight;
                }
            }
        }

        else if (!strcmp(argv[i], "--cohesion-weight")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                float weight;
                weight = atof(argv[++i]);
                if (weight < 0) {
                    std::cout << "ERROR: " << argv[i-1] << " must be non-negative" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else {
                    args.cohesion_weight = weight;
                }
            }
        }

        else if (!strcmp(argv[i], "--alignment-weight")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                float weight;
                weight = atof(argv[++i]);
                if (weight < 0) {
                    std::cout << "ERROR: " << argv[i-1] << " must be non-negative" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else {
                    args.alignment_weight = weight;
                }
            }
        }

        // Use periodic boundary conditions
        else if (!strcmp(argv[i], "--periodic") || !strcmp(argv[i], "-p")) {
            args.use_periodic = true;
        }

        // Verbosity
        else if (!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-v")) {
            args.verbose = true;
        }

        // Quiet
        else if (!strcmp(argv[i], "--quiet") || !strcmp(argv[i], "-q")) {
            args.quiet = true;
        }

        // Argument not recognised
        else {
            std::cout << "ERROR: Argument '" << argv[i] << "' not recognised" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    return args;
}
