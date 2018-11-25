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
    double base_fitness {0.0};
    std::vector<city> cities_to_visit;
    std::vector<tour> tours;
    std::vector<tour> parents;
public:
    population(int cities_in_tour, int population_size, int number_of_elites, int parent_pool_size, int number_of_parents, double mutation_rate, int iterations);
    virtual ~population();

    void init(std::ostream &os);
    void select_parents();
    bool contains_city(std::vector<city> cities, city city);
    tour crossover();
    void repopulate();

    void run(std::ostream &os);
};
