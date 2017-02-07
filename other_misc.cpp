#include <cmath>
#include <random>

#include <SFML/Graphics.hpp>

#include "other_misc.hpp"

int smoothed_delta(float value, float tolerance) {
    // Returns 1 if value is between +/-tolerance

    if ((value >= (-1 * tolerance)) && (value <= tolerance)) {
        return 1;
    }

    else {
        return 0;
    }
}

float positive_fmod(float x, float max) {
    // Returns the smallest non-negative real number congruent to the value
    // returned by fmod
    return fmod(max + fmod(x, max), max);
}

sf::Color generate_random_colour() {
    // Random colour generation:
    // Set one of RGB to 255
    // Set another to 0
    // Set the final one to a random number in the range 0-255
    std::random_device rd;  // Seed engine
    std::mt19937 rng(rd());  // Use Mersenne Twister
    std::uniform_int_distribution<int> random_0_1_2(0, 2);
    std::uniform_int_distribution<int> random_8bit(0, 255);
    int RGB[3] = {0,0,0};

    int element_set_to_255 = random_0_1_2(rng);
    int element_set_to_random = random_0_1_2(rng);

    while (element_set_to_255 == element_set_to_random) {
        element_set_to_255 = random_0_1_2(rng);
        element_set_to_random = random_0_1_2(rng);
    }
    RGB[element_set_to_255] = 255;
    RGB[element_set_to_random] = random_8bit(rng);

    sf::Color to_return(RGB[0], RGB[1], RGB[2]);

    return to_return;
}
