#ifndef COMMAND_LINE_PARSING_HPP

#define COMMAND_LINE_PARSING_HPP

typedef struct {
    unsigned int board_width;
    unsigned int board_height;
    unsigned int num_boids;
    bool verbose;
} argument_struct;

argument_struct parse_args(int argc, char **argv);

#endif // COMMAND_LINE_PARSING_HPP