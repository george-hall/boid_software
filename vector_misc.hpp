#ifndef VECTOR_MISC_HPP

#define VECTOR_MISC_HPP

// Convenience type for vectors
typedef sf::Vector2f vect;

std::string velocity_to_str(vect v);
std::string position_to_str(vect v);

float calculate_vector_magnitude(vect v);
vect constrain_vector(vect v, float max_magnitude);


#endif // VECTOR_MISC_HPP
