#include <iostream>
#include <iomanip>
#include <random>
#include <set>
#include <list>

#include "tour.hpp"
#include "city.hpp"

using namespace std;

constexpr double LOWER {0.0};
constexpr double UPPER {1000.0};
constexpr int CITIES_IN_TOUR {32};
constexpr int POPULATION_SIZE (32);

int main() {

    cout << setprecision(2) << fixed;

    int counter {0};

    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(LOWER, UPPER);

    set<city> cities;

    for(int i = 0; i < CITIES_IN_TOUR; i++)
    {
        string name = "city " + to_string(counter);
        city *c = new city(name, distribution(generator), distribution(generator));
        cities.insert(*c);
        counter++;
    }

    tour *t = new tour(cities);

    for(auto c : t->get_cities())
        cout << "TOUR: " << c << "\n";

    return 0;
}

//int main() {
//
//    city *a = new city("Vancouver", 100, 200);
//
//    cout << *a << "\n";
//
//    city *b = new city("Burnaby", 10, 999);
//
//    cout << *b << "\n";
//
//    if(*b == *a)
//        cout << "SAME" << "\n";
//    else
//        cout << "NOT SAME" << "\n";
//
//    city *c = new city(*a);
//
//    cout << *c << "\n";
//
//    if(*c == *a)
//        cout << "SAME" << "\n";
//    else
//        cout << "NOT SAME" << "\n";
//
//    *c = *b;
//
//    cout << *c << "\n";
//
//    if(*b == *c)
//        cout << "SAME" << "\n";
//    else
//        cout << "NOT SAME" << "\n";
//
//    return 0;
//}