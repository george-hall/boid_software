#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "command_line_parsing.hpp"
#include "boids.hpp"
#include "main.hpp"
#include "boid_file_io.hpp"

void read_boids_from_file(argument_struct args, Boid **boid_array) {
    std::ifstream in_file(args.in_file_name);
    float x_pos, y_pos, x_vel, y_vel;
    unsigned int lines_read = 0;

    if (in_file.is_open()) {
        while (in_file >> x_pos >> y_pos >> x_vel >> y_vel) {
            if (lines_read == args.num_boids) {
                break;
            }
            Boid *ptr_to_boid = boid_array[lines_read++];
            ptr_to_boid->set_position(x_pos, y_pos);
            ptr_to_boid->set_velocity(x_vel, y_vel);
        }
    }

    // Set any unspecified boids to random values
    if (lines_read < args.num_boids) {
        set_random_attributes(args.num_boids - lines_read, &boid_array[lines_read], args.board_width, args.board_height);
    }
}
