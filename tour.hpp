//
// Created by Carlo on 2018-11-18.
//

#pragma once

#include "city.hpp"
#include <vector>

class tour
{
private:
    std::vector<city> cities;
    double fitness;
public:
//    default constructor
    tour();
//    overloaded constructor - takes a vector of cities, shuffles cities on instantiation
    tour(std::vector<city> cities);
//    copy constructor
    tour(const tour &c);
//    virtual destructor
    virtual ~tour();
//    returns vector of cities in the tour
    std::vector<city> get_cities();
//    returns the fitness of the tour
    double get_fitness() const;
//    shuffles the cities in the tour SHUFFLES times
    void shuffle_cities();
//    returns as-the-crow-flies distance between two cities - takes in two cities to compare distance
    double get_distance_between_cities(city first, city second) const;
//    returns total distance of tour
    double get_tour_distance() const;
//    calculates fitness of tour (1/distance * 1000000)
    double determine_fitness();
//    creates a vector of mutation values to correspond with each city then swaps all cities either up or down if they have a mutation value lower than mutation_rate
    void mutate(double mutation_rate);
//    overloaded == operator checks if all cities in the tour are the same as tour& t
    bool operator ==(const tour & t);
};
