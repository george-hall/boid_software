#include <iostream>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "other_misc.hpp"
#include "command_line_parsing.hpp"
#include "boids.hpp"

// Initialiser

Boid::Boid(unsigned int new_boid_ID) {
    vect velocity(0,0);
    vect position(0,0);

    colour = generate_random_colour();

    boid_ID = new_boid_ID;
}

// Setters

void Boid::set_position(float new_x, float new_y) {
    vect new_position(new_x, new_y);
    position = new_position;
}

void Boid::set_velocity(float new_i, float new_j) {
    vect new_velocity(new_i, new_j);
    velocity = new_velocity;
}

// Getters

unsigned int Boid::get_boid_ID() {
    return boid_ID;
}

vect Boid::get_position() {
    return position;
}

vect Boid::get_velocity() {
    return velocity;
}

sf::Color Boid::get_colour() {
    return colour;
}

// Miscellaneous

void Boid::print() {
    std::cout << "\t* boid_ID: " << boid_ID << std::endl;
    std::cout << "\t* velocity: " << velocity_to_str(velocity) << std::endl;
    std::cout << "\t* position: " << position_to_str(position) << std::endl;
}

vect Boid::compute_avoidance_vector(argument_struct args, float **dist_matrix,
                                    Boid **boid_array, float max_x,
                                    float max_y) {
    unsigned int boid_ID = get_boid_ID();
    vect current_position = get_position();
    vect avoidance_vector(0, 0);

    for (unsigned int i = 0; i < args.num_boids; i++) {
        if ((i != boid_ID) && (boid_in_nhood(args, boid_array, dist_matrix, i))) {
            Boid *ptr_to_neighbour = boid_array[i];
            vect neighbour_pos = ptr_to_neighbour->get_position();

            // Compute vector in direction away from neighbour
            vect dis_vect = compute_displacement_vector(neighbour_pos,
                                                        current_position,
                                                        max_x, max_y, args.use_periodic);
            // Make this vector unit length (this means that the avoidance
            // vector for a pair of boids will be the same regardless of their
            // distance from one another)
            vect dis_vect_unit = change_vector_magnitude(dis_vect, 1);

            avoidance_vector += dis_vect_unit;
        }
    }

    return change_vector_magnitude(avoidance_vector, 1);
}


bool Boid::boid_in_nhood(argument_struct args, Boid **boid_array, float **dist_matrix, unsigned int other_boid_ID) {
    if (args.mode == 0) {
        if (dist_matrix[get_boid_ID()][other_boid_ID] < args.nhood_size) {
            return true;
        }

        else {
            return false;
        }
    }

    else {
        std::cerr << "ERROR: Mode not recognised: " << args.mode << std::endl;
        exit(EXIT_FAILURE);
    }
}


vect Boid::compute_alignment_vector(argument_struct args, float **dist_matrix,
                                    Boid **boid_array) {

    unsigned int boid_ID = get_boid_ID();

    // Has to be float to be able to divide vector by this value
    float num_boids_in_nhood = 0;
    vect nhood_average_velocity(0, 0);

    for (unsigned int i = 0; i < args.num_boids; i++) {
        if ((i != boid_ID) && (boid_in_nhood(args, boid_array, dist_matrix, i))) {
            num_boids_in_nhood += 1;
            Boid *ptr_to_neighbour = boid_array[i];
            vect neighbour_velocity = ptr_to_neighbour->get_velocity();

            nhood_average_velocity += neighbour_velocity;
        }
    }

    if (num_boids_in_nhood == 0) {
        // Avoid division by 0
        return nhood_average_velocity;
    }

    vect to_return = (nhood_average_velocity / num_boids_in_nhood);
    return change_vector_magnitude(to_return, 1);
}


vect Boid::compute_nhood_centroid(argument_struct args, float **dist_matrix,
                                  Boid **boid_array, float max_x, float max_y) {

    // Computes the centroid of the boid's neighbourhood. That is, this
    // function returns the position vector of the average position of all
    // boids in the neighbourhood.

    unsigned int boid_ID = get_boid_ID();

    // Has to be float to be able to divide vector by this value
    float num_boids_in_nhood = 0;

    // Running total for simple method (used when neighbourhood does not cross
    // boundaries)
    vect simple_nhood_position_total(0, 0);
    // Running total for complex method (used when neighbourhood does cross
    // boundaries)
    vect complex_nhood_position_total(0, 0);
    // Total to return
    vect nhood_position_total(0, 0);

    // These variables keep track of the highest and lowest x and y values
    // assigned to boids in the neighbourhood. This allows us to determine
    // whether the neighbourhood crosses a boundary, and thus requires the more
    // complex centroid calculation to be used
    float highest_x_in_nhood, lowest_x_in_nhood;
    float highest_y_in_nhood, lowest_y_in_nhood;

    highest_x_in_nhood = get_position().x;
    lowest_x_in_nhood = get_position().x;
    highest_y_in_nhood = get_position().y;
    lowest_y_in_nhood = get_position().y;

    for (unsigned int i = 0; i < args.num_boids; i++) {
        if (dist_matrix[boid_ID][i] < args.nhood_size) {
            num_boids_in_nhood += 1;
            Boid *ptr_to_neighbour = boid_array[i];
            vect neighbour_pos = ptr_to_neighbour->get_position();
            vect complex_neighbour_pos = neighbour_pos;

            if (neighbour_pos.x < lowest_x_in_nhood) {
                lowest_x_in_nhood = neighbour_pos.x;
            }
            if (neighbour_pos.x > highest_x_in_nhood) {
                highest_x_in_nhood = neighbour_pos.x;
            }
            if (neighbour_pos.y < lowest_y_in_nhood) {
                lowest_y_in_nhood = neighbour_pos.y;
            }
            if (neighbour_pos.y > highest_y_in_nhood) {
                highest_y_in_nhood = neighbour_pos.y;
            }

            // Keep complex position total within range [-max_x/2, max_x/2]
            // (resp. y)
            while (complex_neighbour_pos.x > max_x/2.0f) {
                complex_neighbour_pos -= vect(max_x, 0);
            }
            while (complex_neighbour_pos.y > max_y/2.0f) {
                complex_neighbour_pos -= vect(0, max_y);
            }

            simple_nhood_position_total += neighbour_pos;
            complex_nhood_position_total += complex_neighbour_pos;
        }
    }

    if (highest_x_in_nhood - lowest_x_in_nhood > args.nhood_size) {
        // i.e. the neighbourhood must cross a boundary in the x direction
        nhood_position_total.x = complex_nhood_position_total.x;
    }
    else {
        nhood_position_total.x = simple_nhood_position_total.x;
    }

    if (highest_y_in_nhood - lowest_y_in_nhood > args.nhood_size) {
        // i.e. the neighbourhood must cross a boundary in the y direction
        nhood_position_total.y = complex_nhood_position_total.y;
    }
    else {
        nhood_position_total.y = simple_nhood_position_total.y;
    }

    nhood_position_total = nhood_position_total / num_boids_in_nhood;

    // Make centroid deal with periodic boundaries correctly
    nhood_position_total.x = positive_fmod(nhood_position_total.x, max_x);
    nhood_position_total.y = positive_fmod(nhood_position_total.y, max_y);

    return nhood_position_total;
}

vect Boid::compute_cohesion_vector(argument_struct args, float **dist_matrix,
                                   Boid **boid_array, float max_x, float max_y) {

    // This function returns the vector required for the boid to steer towards
    // the centroid (i.e. the average position) of its neighbourhood. It does
    // so in two steps:
    //      1. Compute the neighbourhood's centroid
    //      2. Return the vector to steer the boid in that direction

    vect current_position = get_position();
    vect nhood_centroid = compute_nhood_centroid(args, dist_matrix, boid_array,
                                                 max_x, max_y);

    vect to_return = compute_displacement_vector(current_position, nhood_centroid, max_x, max_y, args.use_periodic);
    return change_vector_magnitude(to_return, 1);
}

bool Boid::in_danger(float **dist_matrix, unsigned int num_boids, float danger_zone) {
    unsigned int boid_ID = get_boid_ID();
    for (unsigned int i = 0; i < num_boids; i++) {
        if ((i != boid_ID) && (dist_matrix[i][boid_ID] <= danger_zone)) {
            return true;
        }
    }
    return false;
}


int Boid::approaching_wall(float max_x, float max_y, float nhood_size) {
    // Return true if the boid is within 1 of a wall

    vect current_position = get_position();

    if (current_position.x <= nhood_size) {
        return 4;
    }
    
    else if (current_position.x >= max_x - nhood_size) {
        return 2;
    }

    else if (current_position.y <= nhood_size) {
        return 1;
    }
    
    else if (current_position.y >= max_y - nhood_size) {
        return 3;
    }

    return 0;
}


vect Boid::direct_away_from_wall(int wall_approach) {
    // wall_approach == 1 => approaching top wall
    // wall_approach == 2 => approaching right wall
    // wall_approach == 3 => approaching bottom wall
    // wall_approach == 4 => approaching left wall

    vect current_velocity = get_velocity();
    if (wall_approach == 1 && current_velocity.y <= 0.0f) {
        current_velocity.y *= -1.0f;
    }
    else if (wall_approach == 3 && current_velocity.y >= 0.0f) {
        current_velocity.y *= -1.0f;
    }
    else if (wall_approach == 2 && current_velocity.x >= 0.0f) {
        current_velocity.x *= -1.0f;
    }
    else if (wall_approach == 4 && current_velocity.x <= 0.0f) {
        current_velocity.x *= -1.0f;
    }

    return current_velocity;
}


vect Boid::compute_new_velocity_classic(argument_struct args,
                                        float **dist_matrix, Boid **boid_array,
                                        float max_x, float max_y) {

    vect new_velocity;
    vect avoidance_vector, cohesion_vector, alignment_vector;

    avoidance_vector = compute_avoidance_vector(args, dist_matrix, boid_array,
                                                max_x, max_y);
    alignment_vector = compute_alignment_vector(args, dist_matrix, boid_array);
    cohesion_vector = compute_cohesion_vector(args, dist_matrix, boid_array,
                                              max_x, max_y);

    if (args.verbose) {
        std::cout << "avoid: " << velocity_to_str(avoidance_vector);
        std::cout << " cohesion: " << velocity_to_str(cohesion_vector);
        std::cout << " alignment: " << velocity_to_str(alignment_vector);
        std::cout << std::endl;
    }

    float weighting[4] = {args.old_velocity_weight, args.avoidance_weight,
                          args.cohesion_weight, args.alignment_weight};
    // weighting[0] is the weighting applied to the boid's old velocity;
    // weighting[1] is avoidance vector weighting; weighting[2] is cohesion
    // vector weighting; weighting[3] is alignment vector weighting;

    if (!args.use_periodic) {
        // wall_approach == 0 => not approaching wall
        int wall_approach = approaching_wall(max_x, max_y, args.nhood_size);
        if (wall_approach != 0) {
            if (args.verbose) {
                std::cout << "Boid " << get_boid_ID() << " avoiding wall" << std::endl;
            }
            return direct_away_from_wall(wall_approach);
        }
    }

    if (!in_danger(dist_matrix, args.num_boids, args.danger_zone)) {
        if (args.verbose) {
            std::cout << "Boid " << get_boid_ID() << " in safe zone" << std::endl;
        }
        new_velocity = (weighting[0] * get_velocity()) + \
                       (weighting[2] * cohesion_vector) + \
                       (weighting[3] * alignment_vector);

        return constrain_vector(new_velocity, 1);
    }

    else {
        if (args.verbose) {
            std::cout << "Boid " << get_boid_ID() << " in danger zone" << std::endl;
        }
        new_velocity = (weighting[0] * get_velocity()) + \
                       (weighting[1] * avoidance_vector) + \
                       (weighting[2] * cohesion_vector) + \
                       (weighting[3] * alignment_vector);

        return constrain_vector(new_velocity, 1);
    }
}


vect Boid::compute_new_velocity(argument_struct args, float **dist_matrix,
                                Boid **boid_array, float max_x, float max_y) {

    if (args.mode == 0) {
        return compute_new_velocity_classic(args, dist_matrix, boid_array,
                                            max_x, max_y);
    }

    else {
        std::cerr << "ERROR: Unrecognised mode option: " << args.mode << std::endl;
        exit(EXIT_FAILURE);
    }
}

vect Boid::compute_new_position() {
    return get_position() + get_velocity();
}
