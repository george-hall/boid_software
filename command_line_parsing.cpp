#include <iostream>
#include <string>

#include <cstring>

#include "command_line_parsing.hpp"

//          Option:        | Short Switch:
// Board width             |      -w
// Board height            |      -h
// Num boids               |      -n
// Neighbourhood size      |      -s
// Danger Zone size        |      -d
// Old velocity weight     |      -o
// Alignment weight        |      -l
// Avoidance weight        |      -a
// Cohesion weight         |      -c
// Periodic boundary conds |      -p
// Print correlations      |      -k
// Input file              |      -f
// Verbose                 |      -v
// Quiet                   |      -q
// Mode                    |      -m
// Max X                   |      -x
// Max Y                   |      -y

argument_struct parse_args(int argc, char **argv) {

    argument_struct args;

    // Set struct members to default values
    args.board_width = 1000;
    args.board_height = 650;
    args.max_x = args.board_width;
    args.max_y = args.board_height;
    args.num_boids = 50;
    args.nhood_size = 50;
    args.danger_zone = 10.0f;
    args.old_velocity_weight = 1.0f;
    args.avoidance_weight = 1.0f;
    args.cohesion_weight = 1.0f;
    args.alignment_weight = 1.0f;
    args.in_file_name = "";
    args.use_periodic = false;
    args.print_corrs = false;
    args.verbose = false;
    args.quiet = false;
    args.mode = 0;

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

        // Max X
        if (!strcmp(argv[i], "--max-x") || !strcmp(argv[i], "-x")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: max x must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                args.max_x = (unsigned int) strtoul(argv[++i], NULL, 10);
                if (args.board_width == 0) {
                    std::cout << "ERROR: max x must be a positive integer" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Max Y
        if (!strcmp(argv[i], "--max-y") || !strcmp(argv[i], "-y")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: max y must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                args.max_y = (unsigned int) strtoul(argv[++i], NULL, 10);
                if (args.board_width == 0) {
                    std::cout << "ERROR: max y must be a positive integer" << std::endl;
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

        // Neighbourhood size
        else if (!strcmp(argv[i], "--nhood-size") || !strcmp(argv[i], "-s")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: neighbourhood size must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            else {
                args.nhood_size = (unsigned int) strtof(argv[++i], NULL);
                if (args.nhood_size == 0) {
                    std::cout << "ERROR: neighbourhood size must be a positive integer" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Danger zone size
        else if (!strcmp(argv[i], "--danger-zone") || !strcmp(argv[i], "-d")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (argv[i+1][0] == '-') {
                std::cout << "ERROR: danger zone size must be a positive integer" << std::endl;
                exit(EXIT_FAILURE);
            }
            args.danger_zone = strtof(argv[++i], NULL);
        }

        // Steer weights
        else if (!strcmp(argv[i], "--old-velocity-weight") || !strcmp(argv[i], "-o")) {
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

        else if (!strcmp(argv[i], "--avoidance-weight") || !strcmp(argv[i], "-a")) {
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

        else if (!strcmp(argv[i], "--cohesion-weight") || !strcmp(argv[i], "-c")) {
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

        else if (!strcmp(argv[i], "--alignment-weight") || !strcmp(argv[i], "-l")) {
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

        // Print correlations
        else if (!strcmp(argv[i], "--print-corrs") || !strcmp(argv[i], "-k")) {
            args.print_corrs = true;
        }

        // Verbosity
        else if (!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-v")) {
            args.verbose = true;
        }

        // Quiet
        else if (!strcmp(argv[i], "--quiet") || !strcmp(argv[i], "-q")) {
            args.quiet = true;
        }

        // In file name
        else if (!strcmp(argv[i], "--in-file") || !strcmp(argv[i], "-f")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            args.in_file_name = argv[++i];
        }

        // Mode
        else if (!strcmp(argv[i], "--mode") || !strcmp(argv[i], "-m")) {
            if (i == argc - 1) {
                std::cout << "ERROR: No corresponding argument with " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            args.mode = atoi(argv[++i]);
        }

        // Argument not recognised
        else {
            std::cout << "ERROR: Argument '" << argv[i] << "' not recognised" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    return args;
}
