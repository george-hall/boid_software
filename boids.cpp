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
