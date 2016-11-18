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

vect Boid::compute_avoidance_vector(float **dist_matrix,
                                    unsigned int num_boids, Boid **boid_array,
                                    float nhood_size) {
    unsigned int boid_ID = get_boid_ID();
    vect current_position = get_position();
    vect avoidance_vector(0, 0);

    for (unsigned int i = 0; i < num_boids; i++) {
        if ((i != boid_ID) && (dist_matrix[boid_ID][i] < nhood_size)) {
            Boid *ptr_to_neighbour = boid_array[i];
            vect neighbour_pos = ptr_to_neighbour->get_position();
            // Add vector in opposite direction from neighbour
            avoidance_vector += (current_position - neighbour_pos);
        }
    }

    return constrain_vector(avoidance_vector, 1);
}

vect Boid::compute_alignment_vector(float **dist_matrix, unsigned int num_boids,
                                   Boid **boid_array, float nhood_size) {

    unsigned int boid_ID = get_boid_ID();

    // Has to be float to be able to divide vector by this value
    float num_boids_in_nhood = 0;
    vect nhood_average_velocity(0, 0);

    for (unsigned int i = 0; i < num_boids; i++) {
        if ((i != boid_ID) && (dist_matrix[boid_ID][i] < nhood_size)) {
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
    return constrain_vector(to_return, 1);
}


vect Boid::compute_nhood_centroid(float **dist_matrix, float nhood_size,
                                  Boid **boid_array, unsigned int num_boids) {

    // Computes the centroid of the boid's neighbourhood. That is, this
    // function returns the position vector of the average position of all
    // boids in the neighbourhood.

    unsigned int boid_ID = get_boid_ID();

    // Has to be float to be able to divide vector by this value
    float num_boids_in_nhood = 0;
    vect nhood_position_total(0, 0);

    for (unsigned int i = 0; i < num_boids; i++) {
        if ((i != boid_ID) && (dist_matrix[boid_ID][i] < nhood_size)) {
            num_boids_in_nhood += 1;
            Boid *ptr_to_neighbour = boid_array[i];
            vect neighbour_pos = ptr_to_neighbour->get_position();

            nhood_position_total += neighbour_pos;
        }
    }

    if (num_boids_in_nhood == 0) {
        // In order to avoid division by 0, if there are no boids in the
        // neighbourhood, then I simply return the boid's current position as
        // the neighbourhood's centroid. This means that the cohesion vector
        // is set to 0
        return get_position();
    }

    return (nhood_position_total / num_boids_in_nhood);
}

vect Boid::compute_cohesion_vector(float **dist_matrix, unsigned int num_boids,
                                   Boid **boid_array, float nhood_size) {

    // This function returns the vector required for the boid to steer towards
    // the centroid (i.e. the average position) of its neighbourhood. It does
    // so in two steps:
    //      1. Compute the neighbourhood's centroid
    //      2. Return the vector to steer the boid in that direction

    vect current_position = get_position();
    vect nhood_centroid = compute_nhood_centroid(dist_matrix, nhood_size,
                                                 boid_array, num_boids);

    vect to_return = (nhood_centroid - current_position);
    return constrain_vector(to_return, 1);
}

vect Boid::compute_new_velocity(float **distance_matrix,
                                unsigned int num_boids, Boid **boid_array,
                                bool verbose) {
    float nhood_size = 100;

    vect new_velocity;
    vect avoidance_vector, cohesion_vector, alignment_vector;

    avoidance_vector = compute_avoidance_vector(distance_matrix, num_boids,
                                                boid_array, nhood_size);
    cohesion_vector = compute_cohesion_vector(distance_matrix, num_boids,
                                              boid_array, nhood_size);
    alignment_vector = compute_cohesion_vector(distance_matrix, num_boids,
                                               boid_array, nhood_size);

    if (verbose) {
        std::cout << "avoid: " << velocity_to_str(avoidance_vector);
        std::cout << " cohesion: " << velocity_to_str(cohesion_vector);
        std::cout << " alignment: " << velocity_to_str(alignment_vector);
        std::cout << std::endl;
    }

    float weighting[4] = {1.0f, 0.4f, 0.3f, 0.2f};
    // weighting[0] is the weighting applied to the boid's old velocity;
    // weighting[1] is avoidance vector weighting; weighting[2] is cohesion
    // vector weighting; weighting[3] is alignment vector weighting;

    new_velocity = (weighting[0] * get_velocity()) + \
                   (weighting[1] * avoidance_vector) + \
                   (weighting[2] * cohesion_vector) + \
                   (weighting[3] * alignment_vector);

    return new_velocity;
}

void Boid::compute_new_position(argument_struct args, float max_x, float max_y,
                                float **distance_matrix, Boid **boid_array) {
    vect zero_velocity(0, 0);
    vect old_position = get_position();
    vect new_velocity = compute_new_velocity(distance_matrix, args.num_boids,
                                             boid_array, args.verbose);

    if (new_velocity == zero_velocity) {
        new_velocity = get_velocity();
    }
    else {
        new_velocity = constrain_vector(new_velocity, 1);
    }
    set_velocity(new_velocity.x, new_velocity.y);

    vect new_position = old_position + new_velocity;
    set_position(positive_fmod(new_position.x, max_x),
                 positive_fmod(new_position.y, max_y));
}
