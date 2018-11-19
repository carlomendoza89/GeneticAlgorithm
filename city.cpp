//
// Created by Carlo on 2018-11-18.
//

#include "city.hpp"

using namespace std;

constexpr int min_range {0};
constexpr int max_range {1000};

city::city()
{
    set_x(min_range);
    set_y(min_range);
}

city::city(std::string name, int x, int y) : name{name}
{
    set_x(x);
    set_y(y);
}

city::city(const city &c) : name{c.name}, x{c.x}, y{c.y}
{}

city::~city() {}

string city::get_name()
{
    return name;
}

int city::get_x()
{
    return x;
}

int city::get_y()
{
    return y;
}

void city::set_name(string name)
{
    this->name = name;
}

void city::set_x(int x)
{
    if(x < min_range)
        throw "x value is too small";
    if(x > max_range)
        throw "x value is too high";
    this->x = x;
}

void city::set_y(int y)
{
    if(y < min_range)
        throw "x value is too small";
    if(y > max_range)
        throw "x value is too high";
    this->y = y;
}

city& city::operator=(const city &c)
{
    name = c.name;
    set_x(c.x);
    set_y(c.y);

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