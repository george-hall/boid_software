#ifndef VECTOR_MISC_HPP

#define VECTOR_MISC_HPP

// Convenience type for vectors
typedef sf::Vector2f vect;

std::string velocity_to_str(vect v);
std::string position_to_str(vect v);

float calculate_vector_magnitude(vect v);
vect constrain_vector(vect v, float max_magnitude);
vect change_vector_magnitude(vect v, float desired_magnitude);
vect compute_displacement_vector(vect v1, vect v2, float max_x, float max_y, bool use_periodic);

#endif // VECTOR_MISC_HPP
