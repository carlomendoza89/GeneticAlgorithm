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
    city();
    city(std::string name, double x, double y);
    city(const city &c);
    virtual ~city();
    std::string get_name();
    double get_x();
    double get_y();
//    void set_name(std::string name);
//    void set_x(double x);
//    void set_y(double y);
    city & operator= (const city & c);
    bool operator< (const city & c) const;
    bool operator == (const city & c);
    friend std::ostream& operator<<(std::ostream& out, const struct city & c);
};
