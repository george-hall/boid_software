#include <string>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"

std::string velocity_to_str(vect v) {
    // Convert a velocity (of type vect) to a string, expressed as
    // the sum of the vector's i and j components
    std::string to_return;
    to_return = std::to_string(v.x) + "i + " + std::to_string(v.y) + "j";
    return to_return;
}
