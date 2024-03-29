#ifndef OTHER_MISC_HPP

#define OTHER_MISC_HPP

int smoothed_delta(float value, float tolerance);
float positive_fmod(float x, float max);
sf::Color generate_random_colour();
std::string create_window_title(argument_struct args);
float quick_random_num_generator();
float find_max_dist(float **dist_array, unsigned int num_boids);

#endif // OTHER_MISC_HPP
