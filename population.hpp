//
// Created by Carlo on 2018-11-25.
//

#pragma once

#include "tour.hpp"

class population
{
private:
    int cities_in_tour;
    int population_size;
    int number_of_elites;
    int parent_pool_size;
    int number_of_parents;
    double mutation_rate;
    int iterations;
    double base_distance {0.0};
    std::vector<city> cities_to_visit;
    std::vector<tour> tours;
    std::vector<tour> parents;
public:
//    Overloaded constructor
    population(int cities_in_tour, int population_size, int number_of_elites, int parent_pool_size, int number_of_parents, double mutation_rate, int iterations);
//    Destructor
    virtual ~population();
//    Sets up initial population of tours and base_fitness.  Prints out starting tours to os
    void init(std::ostream &os);
//    Creates a pool of parents from population, excluding elites, and then randomly chooses number_of_parents tours to use as parents for next generation
    void select_parents();
//    Checks if a vector of cities contains a specified city
    bool contains_city(std::vector<city> cities, city city);
//    Creates a new tour using parents, mutates cities in tours if the tours have a corresponding mutation_value below mutation_rate
    tour crossover();
//    replaces initial population with new population after crossovers are complete
    void repopulate();
//    runs the program according to number of iterations specified, calls select_parents() and repopulate()
    void run(std::ostream &os);
//    prints the final population to os, states how many times the genetic algorithm was run and shows a comparison of new and initial highest fitness levels
    void report(std::ostream &os);
};
