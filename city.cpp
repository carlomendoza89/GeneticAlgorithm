//
// Created by Carlo on 2018-11-18.
//

#include "city.hpp"

using namespace std;

city::city() {}

city::city(string name, double x, double y) : name{name}, x{x}, y{y} {}

city::city(const city &c) : name{c.name}, x{c.x}, y{c.y} {}

city::~city() {}

string city::get_name()
{
    return name;
}

double city::get_x()
{
    return x;
}

double city::get_y()
{
    return y;
}

//void city::set_name(string name)
//{
//    this->name = name;
//}
//
//void city::set_x(double x)
//{
//    this->x = x;
//}
//
//void city::set_y(double y)
//{
//    this->y = y;
//}

city& city::operator=(const city &c)
{
    name = c.name;
    x = c.x;
    y = c.y;

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

bool city::operator< (const city & c) const
{
    if(name < c.name)
        return true;
//    if(c.name < name)
//        return  false;
//    if(x < c.x)
//        return true;
//    if(c.x < x)
//        return false;
//    if(y < c.y)
//        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, const city & c) {
    out << c.name << " (" << c.x << ", " << c.y << ")";
    return out;
}