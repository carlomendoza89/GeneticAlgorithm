//
// Created by Carlo on 2018-11-18.
//

#pragma once
#include <iostream>

class city
{
private:
    std::string name;
    double x;
    double y;
public:
//    default constructor
    city();
//    overloaded constructor - takes a name and x and y coordinates
    city(std::string name, double x, double y);
//    copy constructor
    city(const city &c);
//    virtual destructor
    virtual ~city();
//    returns the x coordinate
    double get_x();
//    returns the y coordinate
    double get_y();
//    overloaded == operator to compare cities
    bool operator == (const city & c);
//    overloaded << operator to print city name and coordinates
    friend std::ostream& operator<<(std::ostream& out, const city & c);
};
