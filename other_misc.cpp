#include <cmath>

#include "other_misc.hpp"

float positive_fmod(float x, float max) {
    // Returns the smallest non-negative real number congruent to the value
    // returned by fmod
    return fmod(max + fmod(x, max), max);
}
