#include <iostream>
#include <string>
#include <random>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "other_misc.hpp"
#include "command_line_parsing.hpp"
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
    std::random_device rd;  // Seed engine
    std::mt19937 rng(rd());  // Use Mersenne Twister
    std::uniform_real_distribution<float> rand_x_coord(0, board_width - 1);
    std::uniform_real_distribution<float> rand_y_coord(0, board_height - 1);

    std::uniform_real_distribution<float> rand_velocity(-3, 3);

    for (unsigned int i = 0; i < num_boids; i++) {
        Boid *boid_ptr = boid_array[i];
        boid_ptr->set_position(rand_x_coord(rng), rand_y_coord(rng));
        boid_ptr->set_velocity(rand_velocity(rng), rand_velocity(rng));
    }
}

float distance_between_boids(Boid *boid_1, Boid *boid_2, float max_x,
                             float max_y) {
    // Let the minimum of (+/-) (x0 - x1) mod (max_x) be the x-distance, where
    // x0 and x1 are the x co-ordinates of the two boids, and max_x is the
    // maximum value x can take before looping back to 0. There is an analogous
    // method to compute the difference in y co-ordinates (the 'y-difference').
    // These two distances can then be added together an returned to give the
    // squared distance between the two boids

    vect boid_1_pos = boid_1->get_position();
    vect boid_2_pos = boid_2->get_position();

    float x_diff = std::min(positive_fmod(boid_1_pos.x - boid_2_pos.x, max_x),
                            positive_fmod(boid_2_pos.x - boid_1_pos.x, max_x));

    float y_diff = std::min(positive_fmod(boid_1_pos.y - boid_2_pos.y, max_y),
                            positive_fmod(boid_2_pos.y - boid_1_pos.y, max_y));

    return x_diff + y_diff;
}

void calculate_distance_matrix(Boid **boid_array, float **distance_matrix,
                               unsigned int num_boids, float max_x,
                               float max_y) {
    // Recieves an array from main into which it inserts the distance for all
    // pairs of boids, indexed by their boid_ID. That is, distance_matrix[i][j]
    // contains the distance between the boid with boid_ID i and the boid with
    // boid_ID j.

    for (unsigned int i = 0; i < num_boids; i++) {
        for (unsigned int j = 0; j < num_boids; j++) {
            float distance;
            distance = distance_between_boids(boid_array[i], boid_array[j],
                                              max_x, max_y);
            distance_matrix[i][j] = distance;
        }
    }
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
        vect boid_pos = boid_array[i]->get_position();
        int rounded_x = static_cast<int>(round(boid_pos.x));
        int rounded_y = static_cast<int>(round(boid_pos.y));
        board[rounded_x][rounded_y] = true;
    }

    for (unsigned int i = 0; i < max_y; i++) {
        for (unsigned int j = 0; j < max_x; j++) {
            if (board[j][i] == true) {
                std::cout << "@";
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

void display_all_boids(Boid **boid_array, unsigned int num_boids,
                       sf::RenderWindow *window) {
    sf::CircleShape circle(3, 30);
    circle.setFillColor(sf::Color(100, 250, 50));
    for (unsigned int i = 0; i < num_boids; i++) {
        circle.setPosition(boid_array[i]->get_position());
        window->draw(circle);
    }
}

void print_all_boids(Boid **boid_array, unsigned int num_boids) {
    for (unsigned int i = 0; i < num_boids; i++) {
        boid_array[i]->print();
    }
}

void print_distance_matrix(float **distance_matrix, unsigned int num_boids) {
    for (unsigned int i = 0; i < num_boids; i++) {
        for (unsigned int j = 0; j < num_boids; j++) {
            std::cout << distance_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void update_all_positions(argument_struct args, Boid **boid_array,
                          float max_x, float max_y, float **distance_matrix) {
    for (unsigned int i = 0; i < args.num_boids; i++) {
        boid_array[i]->compute_new_position(args, max_x, max_y,
                                            distance_matrix, boid_array);
    }
}

int main_program(argument_struct args, float max_x, float max_y) {

    Boid **boid_array = new Boid*[args.num_boids];
    float **distance_matrix = new float*[args.num_boids];

    for (unsigned int i = 0; i < args.num_boids; i++) {
        distance_matrix[i] = new float[args.num_boids];
    }

    initialise_boids(args.num_boids, boid_array);
    set_random_attributes(args.num_boids, boid_array, args.board_width,
                          args.board_height);
    if (args.verbose) {
        print_all_boids(boid_array, args.num_boids);
    }

    calculate_distance_matrix(boid_array, distance_matrix, args.num_boids,
                              max_x, max_y);

    sf::RenderWindow window(sf::VideoMode(args.board_width, args.board_height),
                            "Boidz n the Hood");

    while (window.isOpen()) {

        // Check for window being closed
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Fill window with black
        window.clear(sf::Color::Black);

        update_all_positions(args, boid_array, max_x, max_y, distance_matrix);
        calculate_distance_matrix(boid_array, distance_matrix, args.num_boids,
                                  max_x, max_y);
        if (args.verbose) {
            print_distance_matrix(distance_matrix, args.num_boids);
            print_all_boids(boid_array, args.num_boids);
        }

        display_all_boids(boid_array, args.num_boids, &window);
        window.display();
    }

    free_boid_instance_memory(boid_array, args.num_boids);
    delete[] boid_array;

    return 0;
}

int main(int argc, char **argv) {
    argument_struct args;
    args = parse_args(argc, argv);

    // Maximum values x and y can take before looping back to 0
    // Currently, they are just the same as the board height and width in order
    // to keep things simple
    float max_x = static_cast<float>(args.board_width);
    float max_y = static_cast<float>(args.board_height);

    main_program(args, max_x, max_y);

    return 0;
}
