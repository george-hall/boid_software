#ifndef MAIN_HPP

#define MAIN_HPP

void calculate_dist_matrix(Boid **boid_array, float **dist_matrix, unsigned int num_boids, float max_x, float max_y);
Boid **create_boid_array(argument_struct args);
float **create_dist_matrix(argument_struct args, Boid **boid_array, float max_x, float max_y);
void display_all_boids(Boid **boid_array, unsigned int num_boids, sf::RenderWindow *window);
float distance_between_boids(Boid *boid_1, Boid *boid_2, float max_x, float max_y);
void free_boid_instance_memory(Boid **boid_array, unsigned int num_boids);
void initialise_boids(unsigned int num_boids, Boid **boid_array);
int main(int argc, char **argv);
int main_program(argument_struct args, float max_x, float max_y);
void print_all_boids(Boid **boid_array, unsigned int num_boids);
void print_board(Boid **boid_array, unsigned int num_boids, unsigned int max_x, unsigned int max_y);
void print_dist_matrix(float **dist_matrix, unsigned int num_boids);
void set_random_attributes(unsigned int num_boids, Boid **boid_array, unsigned int board_width, unsigned int board_height);
void update_all_positions(argument_struct args, Boid **boid_array, float max_x, float max_y, float **dist_matrix);

#endif // MAIN_HPP
