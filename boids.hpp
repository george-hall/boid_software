#ifndef BOIDS_HPP

#define BOIDS_HPP

// Convenience type for vectors
typedef sf::Vector2i vect;

class Boid {
    public:
        vect velocity;
        vect position;

        Boid(unsigned int boid_ID);
        void set_velocity(vect new_velocity);
        void set_position(vect new_coords);

        unsigned int get_boid_ID();
        vect get_velocity();
        vect get_position();

        // I want this to return a list of structs, with each
        // struct containing the boid_ID and distance of all
        // boids within a defined neighbourhood
        void get_visible_boids();

        // Function to calculate a boid's new velocity given influence
        // from the three steering factors of cohesion, collision
        // avoidance, and velocity matching
        vect calculate_new_velocity();

        vect compute_avoidance_vector();
        vect compute_cohesion_vector();
        vect compute_velocity_matching_vector();

    private:
        unsigned int boid_ID;
};

typedef struct {
    unsigned int boid_ID;
    Boid *ptr_to_boid;
} distance_info;

#endif // BOIDS_HPP
