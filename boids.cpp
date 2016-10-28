#include <iostream>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "other_misc.hpp"
#include "boids.hpp"

// Initialiser

Boid::Boid(unsigned int new_boid_ID) {
    vect velocity(0,0);
    vect position(0,0);

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

// Miscellaneous

void Boid::print() {
    std::cout << "\t* boid_ID: " << boid_ID << std::endl;
    std::cout << "\t* velocity: " << velocity_to_str(velocity) << std::endl;
    std::cout << "\t* position: " << position_to_str(position) << std::endl;
}

vect Boid::compute_avoidance_vector(float **dist_matrix,
                                    unsigned int num_boids, Boid **boid_array,
                                    float neighbourhood_size) {
    unsigned int boid_ID = get_boid_ID();
    vect current_position = get_position();
    vect avoidance_vector(0, 0);

    for (unsigned int i = 0; i < num_boids; i++) {
        if ((i != boid_ID) && (dist_matrix[boid_ID][i] < neighbourhood_size)) {
            Boid *ptr_to_neighbour = boid_array[i];
            vect neighbour_pos = ptr_to_neighbour->get_position();
            avoidance_vector -= (current_position - neighbour_pos);
        }
    }

    return avoidance_vector;
}

vect Boid::compute_new_velocity(float **distance_matrix,
                                unsigned int num_boids,
                                Boid **boid_array) {
    float neighbourhood_size = 15;

    vect new_velocity;
    vect avoidance_vector;
    //vect avoidance_vector, cohesion_vector, matching_vector;

    avoidance_vector = compute_avoidance_vector(distance_matrix, num_boids,
                                                boid_array,
                                                neighbourhood_size);
    //cohesion_vector = compute_cohesion_vector();
    //matching_vector = compute_matching_vector();

    new_velocity = avoidance_vector;

    return new_velocity;
}

void Boid::compute_new_position(float max_x, float max_y,
                                float **distance_matrix,
                                unsigned int num_boids, Boid **boid_array) {
    vect zero_velocity(0, 0);
    vect old_position = get_position();
    vect new_velocity = compute_new_velocity(distance_matrix, num_boids,
                                             boid_array);

    if (new_velocity == zero_velocity) {
        new_velocity = get_velocity();
    }
    set_velocity(new_velocity.x, new_velocity.y);

    vect new_position = old_position + new_velocity;
    set_position(positive_fmod(new_position.x, max_x),
                 positive_fmod(new_position.y, max_y));
}
