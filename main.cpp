#include <iostream>
#include <string>
#include <random>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "boids.hpp"

void initialise_boids(unsigned int num_boids, Boid **boid_array) {
    // Returns a pointer to an array of pointers to boids, indexed by boid_ID

    for (unsigned int i = 0; i < num_boids; i++) {
        Boid *new_boid_ptr = new Boid(i);
        boid_array[i] = new_boid_ptr;
    }
}

void set_random_attributes(unsigned int num_boids, Boid **boid_array,
                           unsigned int board_width,
                           unsigned int board_height) {

    // Give each boid in boid_array a random position and velocity

    // Set up random number generators
    std::random_device rd; // Seed engine
    std::mt19937 rng(rd()); // Use Mersenne Twister
    std::uniform_int_distribution<int> rand_x_coord(0, board_width);
    std::uniform_int_distribution<int> rand_y_coord(0, board_height);

    std::uniform_int_distribution<int> rand_velocity(-5, 5);

    for (unsigned int i = 0; i < num_boids; i++) {
        Boid *boid_ptr = boid_array[i];
        boid_ptr->set_position(rand_x_coord(rng), rand_y_coord(rng));
        boid_ptr->set_velocity(rand_velocity(rng), rand_velocity(rng));
    }
}

void calculate_distance_matrix(distance_info *boid_list) {
    // Return an array containing the distance for all pairs of
    // boids, indexed by their boid_ID
}

void free_boid_instance_memory(Boid **boid_array, unsigned int num_boids) {
    // Free memory allocated for individual instances of boids
    for (unsigned int i = 0; i < num_boids; i++) {
        delete boid_array[i];
    }
}

void print_board(Boid **boid_array, unsigned int num_boids, unsigned int max_x,
                 unsigned int max_y) {
    bool board[max_x][max_y];
    for (unsigned int i = 0; i < max_x; i++) {
        for (unsigned int j = 0; j < max_y; j++) {
            board[i][j] = false;
        }
    }

    for (unsigned int i = 0; i < num_boids; i++) {
        vect boid_position = boid_array[i]->get_position();
        board[boid_position.x][boid_position.y] = true;
    }

    for (unsigned int i = 0; i < max_y; i++) {
        for (unsigned int j = 0; j < max_x; j++) {
            if (board[i][j] == true) {
                std::cout << "-";
            } else {
                std::cout << "@";
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv) {

    unsigned int num_boids = 5;

    /* Both in px */
    unsigned int board_width = 300;
    unsigned int board_height = 300;

    if (argc != 1) {
        std::cerr << "usage: " << argv[0] << std::endl;
        std::cerr << "note: Takes no command line arguments!" << std::endl;
        return 1;
    }

    Boid **boid_array = new Boid*[num_boids];

    initialise_boids(num_boids, boid_array);
    set_random_attributes(num_boids, boid_array, board_width, board_height);

    free_boid_instance_memory(boid_array, num_boids);
    delete[] boid_array;

    return 0;
}
