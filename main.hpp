#ifndef MAIN_HPP

#define MAIN_HPP

void calculate_dist_matrix(Boid **boid_array, float **dist_matrix,
                           unsigned int num_boids, float max_x, float max_y);

Boid **create_boid_array(argument_struct args);

float **create_dist_matrix(argument_struct args, Boid **boid_array,
                           float max_x, float max_y);

void display_all_boids(Boid **boid_array, unsigned int num_boids,
                       sf::RenderWindow *window);

float distance_between_boids(Boid *boid_1, Boid *boid_2, float max_x,
                             float max_y);

void free_boid_instance_memory(Boid **boid_array, unsigned int num_boids);

void initialise_boids(unsigned int num_boids, Boid **boid_array);

void save_state(argument_struct args, Boid **boid_array);

int main(int argc, char **argv);

void print_all_boids(Boid **boid_array, unsigned int num_boids);

void print_board(Boid **boid_array, unsigned int num_boids, unsigned int max_x,
                 unsigned int max_y);

void print_dist_matrix(float **dist_matrix, unsigned int num_boids);

void set_random_attributes(unsigned int num_boids, Boid **boid_array,
                           unsigned int board_width,
                           unsigned int board_height);

void update_all_boids(argument_struct args, Boid **boid_array, float max_x,
                      float max_y, float **dist_matrix);

vect calculate_mean_velocity(Boid **boid_array, unsigned int num_boids);

float calculate_polarisation(Boid **boid_array, unsigned int num_boids);

void update_fluctuations(argument_struct args, Boid **boid_array, vect *fluctuations_matrix);

void print_correlations(argument_struct args, vect *fluctuations, float **dist_matrix, Boid **boid_array);

float calc_correlation(argument_struct args, vect *fluctuations, float **dist_matrix, float distance, float tolerance, float mean_flock_velocity_magnitude);

#endif // MAIN_HPP
