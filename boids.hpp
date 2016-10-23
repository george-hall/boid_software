#ifndef BOIDS_HPP

#define BOIDS_HPP

class Boid {
    public:
        vect velocity;
        vect position;

        Boid(unsigned int boid_ID);
        void set_position(float new_x, float new_y);
        void set_velocity(float new_i, float new_j);

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

        void compute_new_position(double max_x, double max_y);

        void print();

    private:
        unsigned int boid_ID;
};

typedef struct {
    unsigned int boid_ID;
    Boid *ptr_to_boid;
} distance_info;

#endif // BOIDS_HPP
