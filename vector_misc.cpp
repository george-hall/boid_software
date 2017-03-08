#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "vector_misc.hpp"
#include "command_line_parsing.hpp"
#include "other_misc.hpp"

float angle_between_vects(vect v1, vect v2) {
    float dot_prod = dot_product(v1, v2);
    float v1_mag = calculate_vector_magnitude(v1);
    float v2_mag = calculate_vector_magnitude(v2);

    return (180.0f * acos(dot_prod / (v1_mag * v2_mag))) / 3.14159265f;
}


float dot_product(vect v1, vect v2) {
    return ((v1.x * v2.x) + (v1.y * v2.y));
}


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


vect compute_displacement_vector(vect v1, vect v2, float max_x, float max_y, bool use_periodic) {
    // Return a vector from vector v1 to vector v2. The point of this function
    // is to take into account the periodic boundary conditions imposed on the
    // board, as the displacement vector between two points should take the
    // shortest path, and this path may cross the boundary
    vect to_return(0, 0);

    if (!use_periodic) {
        return v2 - v1;
    }

    if (abs((v2.x - v1.x)) > (max_x/2.0f)) {
        // Shortest path crosses boundary
        to_return.x = v1.x - v2.x;
        // Make magnitude of vector match what expect (the BCs throw it off)
        if (to_return.x < 0) {to_return.x = ((max_x + to_return.x) * -1);}
        else {to_return.x = ((to_return.x - max_x) * -1);}
    }

    else {to_return.x = v2.x - v1.x;}

    if (abs((v2.y - v1.y)) > (max_y/2.0f)) {
        // Shortest path crosses boundary
        to_return.y = v1.y - v2.y;
        // Make magnitude of vector match what expect (the BCs throw it off)
        if (to_return.y < 0) {to_return.y = ((max_y + to_return.y) * -1);}
        else {to_return.y = ((to_return.y - max_y) * -1);}
    }

    else  {to_return.y = v2.y - v1.y;}

    return change_vector_magnitude(to_return, 1);
}
