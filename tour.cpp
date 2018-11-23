//
// Created by Carlo on 2018-11-18.
//

#include "tour.hpp"

using namespace std;

tour::tour() {}
tour::tour(set<city> cities) : cities{cities} {}
tour::tour(const tour &c) : cities{c.cities} {}
tour::~tour() {}

set<city> tour::get_cities()
{
    return cities;
}

//double tour::get_fitness()
//{
//    double sum {0.0};
//    for( set<city>::iterator it = cities.begin(); it != cities.end(); ++it)
//    {
//        sum += it->get_x() + it->get_y();
//    }
//}