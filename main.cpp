#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

#include "tour.hpp"
#include "city.hpp"

using namespace std;

constexpr double LOWER {0.0};
constexpr double UPPER {1000.0};
constexpr int CITIES_IN_TOUR {32};
constexpr int POPULATION_SIZE (32);
constexpr int NUMBER_OF_ELITES {1};
constexpr int PARENT_POOL_SIZE {5};
constexpr int NUMBER_OF_PARENTS {2};
constexpr int TARGET_FITNESS {80};
constexpr int ITERATIONS {10};

vector<city> cities_to_visit;
vector<tour> population;
vector<tour> parents;

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

    sort(population.begin(), population.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});

    int tour_counter {0};

    for(vector<tour>::iterator it = population.begin(); it != population.end(); ++it)
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



void set_parents()
{
    vector<tour> temp;
    vector<tour> parent_pool;
    while(temp.size() != NUMBER_OF_PARENTS)
    {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(NUMBER_OF_ELITES, POPULATION_SIZE-1);

        int parent_number = distr(eng);

        for(int i = 0; i < PARENT_POOL_SIZE; ++i)
        {
            parent_pool.push_back(population[parent_number]);
        }

        for(int i = 0; i < PARENT_POOL_SIZE; ++i)
        {
            for(auto c : parent_pool[i].get_cities())
                cout << "PARENT POOL" << i << ": " << c << "\n";
        }

        sort(parent_pool.begin(), parent_pool.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});


        if(!(find(parents.begin(), parents.end(), parent_pool.front()) != parents.end()))
            temp.push_back(parent_pool.front());
    }

    parents = temp;

    for(int i = 0; i < NUMBER_OF_PARENTS; ++i)
    {
        for(auto c : parents[i].get_cities())
            cout << "PARENT" << i << ": " << c << "\n";
    }
}

tour breed()
{
    vector<city> child_cities;
    int number_of_indices = NUMBER_OF_PARENTS - 1;
    vector<int> selection_indices;

    for(int i = 0; i < number_of_indices; ++i)
    {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(0, CITIES_IN_TOUR);

        int index = distr(eng);

        selection_indices.push_back(index);
    }

    for(int i = 0; i < number_of_indices; ++i)
    {
        for (int j = 0; j < selection_indices[i]; ++j)
            child_cities.push_back(parents[i].get_cities()[j]);

        if(i == number_of_indices - 1)
        {
            int index = selection_indices[i];

            while (child_cities.size() < CITIES_IN_TOUR)
            {
                if (!(find(child_cities.begin(), child_cities.end(), parents[i + 1].get_cities()[index]) !=
                      child_cities.end()))
                    child_cities.push_back(parents[i + 1].get_cities()[index]);
                index++;
                if (index == CITIES_IN_TOUR)
                    index = 0;
            }
        }
    }

    tour *child = new tour(child_cities);

    static int tracker {0};

    for(auto c : child->get_cities())
        cout << "NEW CHILD" << tracker << ": " << c << "\n";

    tracker++;

    return *child;
}

void repopulate()
{
    vector<tour> new_population;
    for(int i = 0; i < NUMBER_OF_ELITES; ++i)
        new_population.push_back(population[i]);

    for(int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i)
        new_population.push_back(breed());

    population = new_population;

    sort(population.begin(), population.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});
}

int main() {
    cout << setprecision(2) << fixed;

    init();

    double base_fitness = population.front().get_fitness();

    int counter = 0;

    for(int i = 0; i < ITERATIONS; i++)
    {
        set_parents();
        repopulate();
        counter++;
    }

    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        for(auto c : population[i].get_cities())
        {
            cout << "NEW TOUR " << i << ": " << c << "\n";
        }
        cout << "DISTANCE = " << population[i].get_tour_distance() << "\n";
        cout << "FITNESS = " << population[i].get_fitness() << "\n" << "\n";
    }

    cout << "Genetic Algorithm was run " << counter << " times" << "\n";

    cout << "New fitness level: " << population.front().get_fitness() << "\n";
    cout << "Old fitness level: " << base_fitness << "\n";

    return 0;
}