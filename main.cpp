#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "boids.hpp"

void initialise_boids(unsigned int num_boids, Boid **boid_array) {
    // Returns a pointer to an array of pointers to boids, indexed by boid_ID

    for (unsigned int i = 0; i < num_boids; i++) {
        Boid *new_boid_ptr = new Boid(i);
        boid_array[i] = new_boid_ptr;
    }

    std::cout << "Returning pointer to boid_array\n";

}

void calculate_distance_matrix(distance_info *boid_list) {
    // Return an array containing the distance for all pairs of
    // boids, indexed by their boid_ID
}

int main(int argc, char **argv) {

    unsigned int num_boids = 5;

    Boid **boid_array = new Boid*[num_boids];

    initialise_boids(num_boids, boid_array);

    delete[] boid_array;

    return 0;
}
