#include <string>

#include "vector_misc.cpp"

std::string vtos(vect v) {
    // Convert a vect to a string, expressed as the sum of the vector's i
    // and j components
    std::string to_return;
    to_return = std::to_string(v.x) + "i + " + std::to_string(v.y) + "j";
    return to_return;
}
