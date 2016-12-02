#ifndef BOIDS_HPP

#define BOIDS_HPP

class Boid {
    public:
        vect velocity;
        vect position;
        sf::Color colour;

        Boid(unsigned int boid_ID);
        void set_position(float new_x, float new_y);
        void set_velocity(float new_i, float new_j);

        unsigned int get_boid_ID();
        vect get_velocity();
        vect get_position();
        sf::Color get_colour();

        // I want this to return a list of structs, with each
        // struct containing the boid_ID and distance of all
        // boids within a defined neighbourhood
        void get_visible_boids();

        vect compute_nhood_centroid(float **dist_matrix, float nhood_size,
                                                  Boid **boid_array,
                                                  unsigned int num_boids, float max_x, float max_y);

        // Function to calculate a boid's new velocity given influence
        // from the three steering factors of cohesion, collision
        // avoidance, and velocity matching
        vect compute_new_velocity(argument_struct args, float **distance_matrix,
                                  Boid **boid_array, float max_x, float max_y);

        vect compute_avoidance_vector(float **distance_matrix,
                                      unsigned int num_boids,
                                      Boid **boid_array, float nhood_size, float max_x, float max_y);
        vect compute_cohesion_vector(float **dist_matrix,
                                     unsigned int num_boids, Boid **boid_array,
                                     float nhood_size, float max_x, float max_y);
        vect compute_alignment_vector(float **dist_matrix,
                                      unsigned int num_boids,
                                      Boid **boid_array, float nhood_size);

        bool in_danger(float **dist_matrix, unsigned int num_boids);

        vect compute_new_position();

        void print();

    private:
        unsigned int boid_ID;
};

#endif // BOIDS_HPP
