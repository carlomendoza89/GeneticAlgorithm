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
    tour();
    tour(std::vector<city> cities);
    tour(const tour &c);
    virtual ~tour();

    bool operator< (const tour & t) const;

    std::vector<city> get_cities();
    double get_fitness() const;

    void shuffle_cities();
    double get_distance_between_cities(city first, city second) const;
    double get_tour_distance() const;
    double determine_fitness();

    struct sort_by_fitness
    {
        bool operator() (const tour & a, const tour & b)
        {
            return a.get_fitness() > b.get_fitness();
        }
    };
};
