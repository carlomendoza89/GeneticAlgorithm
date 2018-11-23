//
// Created by Carlo on 2018-11-18.
//

#include "tour.hpp"
#include <algorithm>
#include <random>
#include <math.h>

using namespace std;

constexpr double FITNESS_SCALAR {1000000};

tour::tour() {}
tour::tour(vector<city> cities) : cities{cities}
{
    shuffle_cities();
    fitness = determine_fitness();
}
tour::tour(const tour &c) : cities{c.cities}, fitness(c.fitness) {}
tour::~tour() {}

vector<city> tour::get_cities()
{
    return cities;
}

double tour::get_fitness() const
{
    return fitness;
}

void tour::shuffle_cities()
{
    random_shuffle(this->cities.begin(), this->cities.end());
}

double tour::get_distance_between_cities(city first, city second) const
{
    return sqrt(pow(second.get_x() - first.get_x(), 2) + pow(second.get_y() - first.get_y(), 2));
}

double tour::get_tour_distance() const
{
    double distance {0};

    for(int i = 0; i < cities.size() - 1; ++i)
        distance += get_distance_between_cities(cities[i], cities[i+1]);

    return distance;
}

double tour::determine_fitness()
{
    return (1/get_tour_distance()) * FITNESS_SCALAR;
}