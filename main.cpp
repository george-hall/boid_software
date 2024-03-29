#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "command_line_parsing.hpp"
#include "other_misc.hpp"
#include "boids.hpp"
#include "boid_file_io.hpp"
#include "main.hpp"

#define PI 3.14159265


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

    float x_diff;
    float y_diff;

    x_diff = std::min(positive_fmod(boid_1_pos.x - boid_2_pos.x, max_x),
                      positive_fmod(boid_2_pos.x - boid_1_pos.x, max_x));

    y_diff = std::min(positive_fmod(boid_1_pos.y - boid_2_pos.y, max_y),
                      positive_fmod(boid_2_pos.y - boid_1_pos.y, max_y));

    return sqrt((x_diff*x_diff) + (y_diff * y_diff));
}


void calculate_dist_matrix(Boid **boid_array, float **dist_matrix,
                               unsigned int num_boids, float max_x,
                               float max_y) {
    // Recieves an array from main into which it inserts the distance for all
    // pairs of boids, indexed by their boid_ID. That is, dist_matrix[i][j]
    // contains the distance between the boid with boid_ID i and the boid with
    // boid_ID j.

    for (unsigned int i = 0; i < num_boids; i++) {
        for (unsigned int j = 0; j < num_boids; j++) {
            float distance;
            distance = distance_between_boids(boid_array[i], boid_array[j],
                                              max_x, max_y);
            dist_matrix[i][j] = distance;
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
    sf::ConvexShape arrow;
    arrow.setPointCount(3);
    arrow.setPoint(0, sf::Vector2f(0, 0));
    arrow.setPoint(1, sf::Vector2f(3, 1));
    arrow.setPoint(2, sf::Vector2f(0, 2));
    for (unsigned int i = 0; i < num_boids; i++) {
        Boid *ptr_to_boid = boid_array[i];
        arrow.setPosition(ptr_to_boid->get_position());
        vect current_velocity = ptr_to_boid->get_velocity();
        float velocity_mag = calculate_vector_magnitude(current_velocity);
        // Calculate the angle between the velocity and the vector (1,0) (i.e.
        // a horizontal vector).
        float rotation = std::acos(current_velocity.x / velocity_mag);
        // Convert to degrees
        rotation = rotation * 180.0f / PI;
        // As acos only returns values in the range [0, pi], we need to
        // differentiate between velocities which are pointing upwards and
        // those which are pointing downwards. This section does that.
        if (current_velocity.y < 0) {
            rotation = 360.0f - rotation;
        }
        arrow.setRotation(rotation);
        sf::Color boid_colour = ptr_to_boid->get_colour();
        arrow.setFillColor(boid_colour);
        window->draw(arrow);
    }
}


void print_all_boids(Boid **boid_array, unsigned int num_boids) {
    for (unsigned int i = 0; i < num_boids; i++) {
        boid_array[i]->print();
    }
}


void print_dist_matrix(float **dist_matrix, unsigned int num_boids) {
    for (unsigned int i = 0; i < num_boids; i++) {
        for (unsigned int j = 0; j < num_boids; j++) {
            std::cout << dist_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void update_all_boids(argument_struct args, Boid **boid_array,
                      float max_x, float max_y, float **dist_matrix) {

    // Updates the velocity and then the position for all boids

    vect new_velocity, new_position;
    Boid *ptr_to_boid;

    // Update all boids' velocities
    for (unsigned int i = 0; i < args.num_boids; i++) {
        ptr_to_boid = boid_array[i];
        new_velocity = ptr_to_boid->compute_new_velocity(args, dist_matrix,
                                                         boid_array, max_x,
                                                         max_y);
        ptr_to_boid->set_velocity(new_velocity.x, new_velocity.y);
    }

    // Update all boids' positions
    for (unsigned int i = 0; i < args.num_boids; i++) {
        ptr_to_boid = boid_array[i];
        new_position = ptr_to_boid->compute_new_position();
        if (args.use_periodic) {
            ptr_to_boid->set_position(positive_fmod(new_position.x, max_x),
                                      positive_fmod(new_position.y, max_y));
        }
        else {
            if (new_position.x > max_x) {
                new_position.x = max_x;
            }
            else if (new_position.x < 0) {
                new_position.x = 0;
            }
            if (new_position.y > max_y) {
                new_position.y = max_y;
            }
            else if (new_position.y < 0) {
                new_position.y = 0;
            }
            ptr_to_boid->set_position(new_position.x, new_position.y);
        }
    }

}


Boid **create_boid_array(argument_struct args) {

    Boid **boid_array = new Boid*[args.num_boids];

    initialise_boids(args.num_boids, boid_array);

    if (args.in_file_name == "") {
        set_random_attributes(args.num_boids, boid_array, args.board_width,
                              args.board_height);
    }
    else {
        read_boids_from_file(args, boid_array);
    }

    if (args.verbose) {
        print_all_boids(boid_array, args.num_boids);
    }

    return boid_array;
}


float **create_dist_matrix(argument_struct args, Boid **boid_array,
                           float max_x, float max_y) {

    float **dist_matrix = new float*[args.num_boids];

    for (unsigned int i = 0; i < args.num_boids; i++) {
        dist_matrix[i] = new float[args.num_boids];
    }

    calculate_dist_matrix(boid_array, dist_matrix, args.num_boids, max_x,
                          max_y);

    return dist_matrix;
}


vect calculate_mean_velocity(Boid **boid_array, unsigned int num_boids) {
    vect running_total(0, 0);
    Boid *ptr_to_boid;

    for (unsigned int i = 0; i < num_boids; i++) {
        ptr_to_boid = boid_array[i];
        running_total += ptr_to_boid->get_velocity();
    }

    return (running_total / (float) num_boids);
}


float calculate_polarisation(Boid **boid_array, unsigned int num_boids) {
    vect running_total(0, 0);
    Boid *ptr_to_boid;

    for (unsigned int i = 0; i < num_boids; i++) {
        ptr_to_boid = boid_array[i];
        vect boid_velocity = ptr_to_boid->get_velocity();
        running_total += change_vector_magnitude(boid_velocity, 1);
    }

    float polarisation = calculate_vector_magnitude(running_total / (float) num_boids);

    return polarisation;
}


void update_fluctuations(argument_struct args, Boid **boid_array, vect *fluctuations_matrix) {
    vect flock_mean_velocity = calculate_mean_velocity(boid_array, args.num_boids);

    for (unsigned int i = 0; i < args.num_boids; i++) {
        Boid *boid_ptr = boid_array[i];
        fluctuations_matrix[boid_ptr->get_boid_ID()] = boid_ptr->get_velocity() - flock_mean_velocity;
    }
}


void save_state(argument_struct args, Boid **boid_array) {
    // Write the current state of the board to file

    std::string file_name;

    std::cout << "What do you want to call the data file? ";
    std::cin >> file_name;

    std::ofstream out_file(file_name);

    if (out_file.is_open()) {
        for (unsigned int i = 0; i < args.num_boids; i++) {
            Boid *ptr_to_boid = boid_array[i];
            vect boid_pos = ptr_to_boid->get_position();
            vect boid_vel = ptr_to_boid->get_velocity();
            out_file << boid_pos.x << " " << boid_pos.y << " ";
            out_file << boid_vel.x << " " << boid_vel.y << std::endl;
        }
        out_file.close();
    }

    return;
}


float calc_correlation(argument_struct args, vect *fluctuations, float **dist_matrix, float distance, float tolerance) {

    float numerator = 0.0f;
    float number_points_summed = 0.0f;

    for (unsigned int i = 0; i < args.num_boids; i++) {
        vect f1 = fluctuations[i];
        for (unsigned int j = 0; j < args.num_boids; j++) {
            if ((dist_matrix[i][j] <= distance + tolerance) && (dist_matrix[i][j] >= distance - tolerance)) {
                vect f2 = fluctuations[j];
                numerator += dot_product(f1, f2);
                number_points_summed++;
            }
        }
    }
    if (number_points_summed == 0) {
        return 5000.0f;
    }
    else {
        numerator /= number_points_summed;
        float denominator = 0.0f;
        for (unsigned int i = 0; i < args.num_boids; i++) {
            vect fluc = fluctuations[i];
            denominator += dot_product(fluc, fluc);
        }
        denominator /= args.num_boids;
        return (numerator / denominator);
    }
}


float calc_corr_length(argument_struct args, vect *fluctuations, float **dist_matrix) {
    float tolerance = 10.0f;
    int lengths_negative = 0;
    for (float length = 1.0f; length < args.max_x; length++) {
        float correlation = calc_correlation(args, fluctuations, dist_matrix, length, tolerance);
        if (correlation <= 0.0f) {
            lengths_negative += 1;
            if (lengths_negative == 5) {
                return length - 5;
            }
        }
        else {
            lengths_negative = 0;
        }
    }
    return args.max_x;
}


void display_stats(sf::RenderWindow *window, sf::Font font, int iterations_completed, float polarisation, float corr_len) {
    sf::Text iterations_str;
    iterations_str.setString("Iteration: " + std::to_string(iterations_completed));
    iterations_str.setFont(font);
    iterations_str.setCharacterSize(16);
    iterations_str.setColor(sf::Color::Red);
    window->draw(iterations_str);

    // Display polarisation
    sf::Text polarisation_str;
    polarisation_str.setString("Polarisation: " + std::to_string(polarisation));
    polarisation_str.setFont(font);
    polarisation_str.setCharacterSize(16);
    polarisation_str.setColor(sf::Color::Red);
    polarisation_str.setPosition(0, 25);
    window->draw(polarisation_str);

    // Display correlation length
    sf::Text flock_corr_str;
    flock_corr_str.setString("Correlation length: " + std::to_string(corr_len));
    flock_corr_str.setFont(font);
    flock_corr_str.setCharacterSize(16);
    flock_corr_str.setColor(sf::Color::Red);
    flock_corr_str.setPosition(0, 50);
    window->draw(flock_corr_str);
}


int main(int argc, char **argv) {
    argument_struct args = parse_args(argc, argv);

    Boid **boid_array = create_boid_array(args);
    float **dist_matrix = create_dist_matrix(args, boid_array, args.max_x, args.max_y);

    // Stores fluctuations of boids' velocities around the flock's mean velocity
    vect *fluctuations_matrix = new vect[args.num_boids];

    sf::Font font;
    std::string window_title = create_window_title(args);
    sf::RenderWindow window(sf::VideoMode(args.board_width, args.board_height),
                        window_title);
    if (args.quiet) {window.close();}

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "ERROR: Unable to locate font file required to display ";
        std::cerr << "the flock's polarisation." << std::endl;
    }

    int iterations_completed = 0;
    int num_iters_high_polarisation = 0;
    int num_iters_sub_polar_thresh = 0;
    float curr_max_corr_len = 0.0f;
    float corr_len = 5000;
    float flock_size_with_max_cl = 0.0f;
    while (true) {
        if (!args.quiet) {
            // Check for window being closed
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close(); return 0;
                }

                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        save_state(args, boid_array);
                    }
                }
            }
            window.clear(sf::Color::Black); // Fill window with black
        }

        calculate_dist_matrix(boid_array, dist_matrix, args.num_boids, args.max_x,
                              args.max_y);
        update_all_boids(args, boid_array, args.max_x, args.max_y, dist_matrix);
        update_fluctuations(args, boid_array, fluctuations_matrix);

        float polarisation = calculate_polarisation(boid_array, args.num_boids);
        if (args.print_corrs) {
            if (polarisation <= 0.99f) {
                num_iters_sub_polar_thresh++;
                corr_len = calc_corr_length(args, fluctuations_matrix, dist_matrix);
                if (corr_len > curr_max_corr_len) {
                    curr_max_corr_len = corr_len;
                    flock_size_with_max_cl = find_max_dist(dist_matrix, args.num_boids);
                }
            }
            else {
                if (curr_max_corr_len != 0.0f && num_iters_sub_polar_thresh >= 5) {
                    std::cout << flock_size_with_max_cl << " " << curr_max_corr_len << std::endl;
                }
                curr_max_corr_len = 0.0f;
                num_iters_sub_polar_thresh = 0;
            }
            // std::cout << iterations_completed << " " << corr_len << std::endl;
        }

        if (args.quiet) {
            int iterations_cutoff = 50000; // Number of iterations until we give up trying to produce a flock
            if (iterations_completed <= iterations_cutoff) {
                if (polarisation >= 0.98f) {
                    num_iters_high_polarisation++;
                    if (num_iters_high_polarisation == 51) {
                        std::cout << "num_boids: " << args.num_boids << " max_x: " << args.max_x << " max_y: " << args.max_y << " vision_angle: " << args.vision_angle << " iterations: " << iterations_completed - 50 << std::endl; break;
                    }
                }
                else {
                    num_iters_high_polarisation = 0;
                }
            }
            else {
                std::cout << "num_boids: " << args.num_boids << " max_x: " << args.max_x << " max_y: " << args.max_y << " vision_angle: " << args.vision_angle << " iterations: " << iterations_completed - 50 << std::endl; break;
            }
        }
        iterations_completed++;

        if (args.verbose) {
            print_dist_matrix(dist_matrix, args.num_boids);
            print_all_boids(boid_array, args.num_boids);
        }

        if (!args.quiet) {
            display_all_boids(boid_array, args.num_boids, &window);
            display_stats(&window, font, iterations_completed, polarisation, corr_len);
            window.display();
        }
    }

    free_boid_instance_memory(boid_array, args.num_boids);
    delete[] boid_array;

    return 0;
}
