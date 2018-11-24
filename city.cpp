//
// Created by Carlo on 2018-11-18.
//

#include "city.hpp"

using namespace std;

city::city() = default;

city::city(string name, double x, double y) : name{name}, x{x}, y{y} {}

city::city(const city &c) : name{c.name}, x{c.x}, y{c.y} {}

city::~city() = default;

double city::get_x()
{
    return x;
}

double city::get_y()
{
    return y;
}

bool city::operator==(const city &c)
{
    if(name == c.name)
    {
        if(x == c.x)
        {
            if(y == c.y)
            {
                return true;
            }
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const city & c) {
    out << c.name << " (" << c.x << ", " << c.y << ")";
    return out;
}