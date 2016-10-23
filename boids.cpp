#include <iostream>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
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

void Boid::compute_new_position(float max_x, float max_y) {
    vect old_position = get_position();
    vect velocity = get_velocity();
    vect new_position = old_position + velocity;

    float fmodded_x = fmod(new_position.x, max_x);
    float fmodded_y = fmod(new_position.y, max_y);

    // Required so that the new position is not negative
    // Effective makes fmod behave like the regular modulo function
    while (fmodded_x < 0) {
        fmodded_x += max_x;
    }
    while (fmodded_y < 0) {
        fmodded_y += max_y;
    }

    set_position(fmodded_x, fmodded_y);
}
