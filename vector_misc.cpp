#include <string>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "other_misc.hpp"

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

vect change_vector_magnitude(vect v, float desired_magnitude) {
    float magnitude;
    magnitude = calculate_vector_magnitude(v);

    if (magnitude == 0.0f) {
        // Should really be raising an exception here...
        return v;
    }

    else {
        return desired_magnitude * (v / magnitude);
    }
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

    if (magnitude <= max_magnitude) {
        return v;
    }

    else {
        to_return = max_magnitude * (v / magnitude);
        return to_return;
    }
}

vect compute_displacement_vector(vect v1, vect v2, float max_x, float max_y) {
    // Return a vector from vector v1 to vector v2. The point of this function
    // is to take into account the periodic boundary conditions imposed on the
    // board, as the displacement vector between two points should take the
    // shortest path, and this path may cross the boundary
    vect to_return(0, 0);

    if (abs((v2.x - v1.x)) > (max_x/2.0f)) {
        // Shortest path crosses boundary
        to_return.x = v1.x - v2.x;
    }
    else {
        to_return.x = v2.x - v1.x;
    }

    if (abs((v2.y - v1.y)) > (max_y/2.0f)) {
        // Shortest path crosses boundary
        to_return.y = v1.y - v2.y;
    }
    else {
        to_return.y = v2.y - v1.y;
    }

    return to_return;
}
