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

        vect compute_nhood_centroid(argument_struct args, float **dist_matrix,
                                    Boid **boid_array, float max_x, float max_y);

        // Function to calculate a boid's new velocity given influence
        // from the three steering factors of cohesion, collision
        // avoidance, and velocity matching
        vect compute_new_velocity(argument_struct args, float **distance_matrix,
                                  Boid **boid_array, float max_x, float max_y);

        vect compute_avoidance_vector(argument_struct args, float **distance_matrix,
                                      Boid **boid_array, float max_x,
                                      float max_y);
        vect compute_cohesion_vector(argument_struct args, float **dist_matrix,
                                     Boid **boid_array, float max_x,
                                     float max_y);
        vect compute_alignment_vector(argument_struct args, float **dist_matrix,
                                      Boid **boid_array);

        bool in_danger(float **dist_matrix, unsigned int num_boids, float danger_zone);
        int approaching_wall(float max_x, float max_y, float nhood_size);

        vect direct_away_from_wall(int wall_approach);

        vect compute_new_position();

        void print();

        bool boid_in_nhood(argument_struct args, Boid **boid_array,
                           float **dist_matrix, unsigned int other_boid_ID);

        bool boid_in_nhood_classic(argument_struct args, float **dist_matrix, unsigned int other_boid_ID);

        bool boid_in_nhood_vision(argument_struct args, Boid **boid_array, float **dist_matrix, unsigned int other_boid_ID);

        bool boid_in_nhood_nearest_n(argument_struct args, float **dist_matrix, unsigned int other_boid_ID);

        bool boid_in_closest_n_boids(argument_struct args, float **dist_matrix, unsigned int other_boid_ID, int cutoff);

        bool boid_in_nhood_normal_dist(argument_struct args, Boid **boid_array, float **dist_matrix, unsigned int other_boid_ID);

    private:
        unsigned int boid_ID;
};

#endif // BOIDS_HPP
