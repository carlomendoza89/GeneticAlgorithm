//
// Created by Carlo on 2018-11-18.
//

#pragma once
#include <iostream>

class city
{
private:
    std::string name;
    int x;
    int y;
public:
    city();
    city(std::string name, int x, int y);
    city(const city &c);
    virtual ~city();
    std::string get_name();
    int get_x();
    int get_y();
    void set_name(std::string name);
    void set_x(int x);
    void set_y(int y);
    city & operator= (const city & c);
    bool operator == (const city & c);
    friend std::ostream& operator<<(std::ostream& out, const struct city & c);
};
