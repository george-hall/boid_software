#include <iostream>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "boids.hpp"

Boid::Boid(unsigned int new_boid_ID) {
    vect velocity(0,0);
    vect position(0,0);

    boid_ID = new_boid_ID;

    std::cout << "Created new boid:" << std::endl;
    print();
}

void Boid::set_position(unsigned int new_x, unsigned int new_y) {
    vect new_position(new_x, new_y);
    position = new_position;
}

void Boid::set_velocity(unsigned int new_i, unsigned int new_j) {
    vect new_velocity(new_i, new_j);
    velocity = new_velocity;
}

void Boid::print() {
    std::cout << "\t* boid_ID: " << boid_ID << std::endl;
    std::cout << "\t* velocity: " << vtos(velocity) << std::endl;
    std::cout << "\t* position: " << vtos(position) << std::endl;
}
