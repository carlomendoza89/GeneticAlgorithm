#include <iostream>
#include <iomanip>
#include <random>
#include <list>

#include "tour.hpp"
#include "city.hpp"

using namespace std;

constexpr double LOWER {0.0};
constexpr double UPPER {1000.0};
constexpr int CITIES_IN_TOUR {32};
constexpr int POPULATION_SIZE (32);
constexpr int ITERATIONS {1000};

int main() {

    cout << setprecision(2) << fixed;

    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(LOWER, UPPER);

    vector<city> cities_to_visit;

    int city_counter {0};

    for(int i = 0; i < CITIES_IN_TOUR; ++i)
    {
        string name = "city " + to_string(city_counter);
        city *c = new city(name, distribution(generator), distribution(generator));
        cities_to_visit.push_back(*c);
        city_counter++;
    }

    list<tour> population;
    {
        for(int i = 0; i < POPULATION_SIZE; ++i)
        {
            tour *t = new tour(cities_to_visit);
            population.push_back(*t);
        }
    }

    population.sort(tour::sort_by_fitness());

    int tour_count {0};

    for(list<tour>::iterator it = population.begin(); it != population.end(); ++it)
    {
        for(auto c : it->get_cities())
        {
            cout << "TOUR " << tour_count << ": " << c << "\n";
        }
        cout << "DISTANCE = " << it->get_tour_distance() << "\n";
        cout << "FITNESS = " << it->get_fitness() << "\n" << "\n";
        tour_count++;
    }

    return 0;
}