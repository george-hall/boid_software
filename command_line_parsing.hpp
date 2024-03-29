#ifndef COMMAND_LINE_PARSING_HPP

#define COMMAND_LINE_PARSING_HPP

typedef struct {
    unsigned int board_width;
    unsigned int board_height;
    unsigned int max_x;
    unsigned int max_y;
    float nhood_size;
    float danger_zone;
    float old_velocity_weight;
    float avoidance_weight;
    float cohesion_weight;
    float alignment_weight;
    unsigned int num_boids;
    bool use_periodic;
    bool print_corrs;
    std::string in_file_name;
    bool verbose;
    bool quiet;
    int mode;
    int topological_distance;
    float vision_angle;
} argument_struct;

argument_struct parse_args(int argc, char **argv);

#endif // COMMAND_LINE_PARSING_HPP
