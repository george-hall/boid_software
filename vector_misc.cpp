#include <string>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"

std::string velocity_to_str(vect v) {
    // Convert a velocity (of type vect) to a string, expressed as
    // the sum of the vector's i and j components
    std::string to_return;

    // Deal with negative j to avoid stuff like "6i + -9j"
    std::string j_component_str;
    j_component_str = std::to_string(v.y);
    if (v.y < 0) {
        j_component_str = " - " + j_component_str.erase(0, 1) + "j";
    }
    else {
        j_component_str = " + " + j_component_str + "j";
    }

    to_return = std::to_string(v.x) + "i" + j_component_str;
    return to_return;
}

std::string position_to_str(vect v) {
    // Convert a position (of type vect) to a string, expressed as
    // an (x, y) co-ordinate pair
    std::string to_return;
    to_return = "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    return to_return;
}

float calculate_vector_magnitude(vect v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

vect constrain_vector(vect v, float max_magnitude) {
    // Constrain's a vector's magnitude to be at most max_magnitude
    vect to_return;
    vect zero_vector(0, 0);
    float magnitude;

    if (v == zero_vector) {
        return v;
    }

    magnitude = calculate_vector_magnitude(v);
    to_return = max_magnitude * (v / magnitude);

    return to_return;
}
