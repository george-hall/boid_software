#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "boids.hpp"

Boid **initialise_boids(unsigned int num_boids) {
    // Set up all boids with random starting positions and velocities
    // Returns a pointer to an array of pointers to boids, indexed by boid_ID

    Boid **boid_array = new Boid*[num_boids];

    for (unsigned int i = 0; i < num_boids - 1; i++) {
        Boid new_boid = Boid(i);
        boid_array[i] = &new_boid;
    }

    std::cout << "Returning pointer to boid_array\n";

    return boid_array;
}

void calculate_distance_matrix(distance_info *boid_list) {
    // Return an array containing the distance for all pairs of
    // boids, indexed by their boid_ID
}

int main(int argc, char **argv) {
    
    unsigned int num_boids = 5;

    initialise_boids(num_boids);

    return 0;
}
