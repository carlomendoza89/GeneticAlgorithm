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
constexpr int NUMBER_OF_ELITES {1};
constexpr int PARENT_POOL_SIZE {5};
constexpr int NUMBER_OF_PARENTS {3};

struct sort_by_fitness
{
    bool operator() (const tour & a, const tour & b)
    {
        return a.get_fitness() > b.get_fitness();
    }
};

vector<city> cities_to_visit;
list<tour> population;

void init()
{
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(LOWER, UPPER);

    int city_counter {0};

    for(int i = 0; i < CITIES_IN_TOUR; ++i)
    {
        string name = "city " + to_string(city_counter);
        city *c = new city(name, distribution(generator), distribution(generator));
        cities_to_visit.push_back(*c);
        city_counter++;
    }

    {
        for(int i = 0; i < POPULATION_SIZE; ++i)
        {
            tour *t = new tour(cities_to_visit);
            population.push_back(*t);
        }
    }

    population.sort(sort_by_fitness());

    int tour_counter {0};

    for(list<tour>::iterator it = population.begin(); it != population.end(); ++it)
    {
        for(auto c : it->get_cities())
        {
            cout << "TOUR " << tour_counter << ": " << c << "\n";
        }
        cout << "DISTANCE = " << it->get_tour_distance() << "\n";
        cout << "FITNESS = " << it->get_fitness() << "\n" << "\n";
        tour_counter++;
    }

    double base_distance = population.begin()->get_tour_distance();

    cout << "BASE DISTANCE = " << base_distance << "\n";
}

void evaluate()
{
    tour parent_pool[NUMBER_OF_PARENTS];

    list<tour>::iterator it = population.begin();
    advance(it, NUMBER_OF_ELITES);

    for(int i = 0; i < NUMBER_OF_PARENTS; ++i)
    {
        parent_pool[i] = *it;
        ++it;
    }
}

int main() {
    cout << setprecision(2) << fixed;

    init();
    

    return 0;
}