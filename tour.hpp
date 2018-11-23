//
// Created by Carlo on 2018-11-18.
//

#pragma once

#include "city.hpp"
#include <set>

class tour
{
private:
    std::set<city> cities;
public:
    tour();
    tour(std::set<city> cities);
    tour(const tour &c);
    virtual ~tour();
    std::set<city> get_cities();
    double get_fitness();
};
