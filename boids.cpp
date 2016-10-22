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

void Boid::set_position(unsigned int new_x, unsigned int new_y) {
    vect new_position(new_x, new_y);
    position = new_position;
}

void Boid::set_velocity(unsigned int new_i, unsigned int new_j) {
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

void Boid::compute_new_position(double max_x, double max_y) {
    vect old_position = get_position();
    vect velocity = get_velocity();
    vect new_position = old_position + velocity;
    set_position(fmod(new_position.x, max_x), fmod(new_position.y, max_y));
}
