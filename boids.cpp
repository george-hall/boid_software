#include <iostream>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "boids.hpp"

Boid::Boid(unsigned int new_boid_ID) {
    vect velocity;
    velocity.x = 0;
    velocity.y = 0;

    vect position;
    position.x = 0;
    position.y = 0;

    boid_ID = new_boid_ID;

    std::cout << "Created new boid:" << std::endl;
    std::cout << "\t* boid_ID: " << boid_ID << std::endl;
    std::cout << "\t* velocity: " << vtos(velocity) << std::endl;
    std::cout << "\t* position: " << vtos(position) << std::endl;
}

void Boid::set_position(unsigned int new_x, unsigned int new_y) {
    position.x = new_x;
    position.y = new_y;
}

void Boid::set_velocity(unsigned int new_i, unsigned int new_j) {
    velocity.x = new_i;
    velocity.y = new_j;
}
