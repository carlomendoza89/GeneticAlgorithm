//
// Created by Carlo on 2018-11-25.
//

#include "population.hpp"
#include <random>
#include <algorithm>

using namespace std;

constexpr double LOWER {0.0};
constexpr double UPPER {1000.0};

std::random_device rd;
std::mt19937 eng(rd());

population::population(int cities_in_tour, int population_size, int number_of_elites, int parent_pool_size, int number_of_parents, double mutation_rate, int iterations) :
        cities_in_tour{cities_in_tour}, population_size{population_size}, number_of_elites{number_of_elites}, parent_pool_size{parent_pool_size}, number_of_parents{number_of_parents}, mutation_rate{mutation_rate}, iterations{iterations} {}

population::~population() {}

void population::init(ostream &os)
{
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(LOWER, UPPER);

    int city_counter {0};

    for(int i = 0; i < cities_in_tour; ++i)
    {
        string name = "city " + to_string(city_counter);
        city *c = new city(name, distribution(generator), distribution(generator));
        cities_to_visit.push_back(*c);
        city_counter++;
    }

    {
        for(int i = 0; i < population_size; ++i)
        {
            tour *t = new tour(cities_to_visit);
            tours.push_back(*t);
        }
    }

    sort(tours.begin(), tours.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});

    base_fitness = tours.front().get_fitness();

    int tour_counter {0};

    for(vector<tour>::iterator it = tours.begin(); it != tours.end(); ++it)
    {
        for(auto c : it->get_cities())
        {
            os << "STARTING TOUR " << tour_counter << ": " << c << "\n";
        }
        os << "DISTANCE = " << it->get_tour_distance() << "\n";
        os << "FITNESS = " << it->get_fitness() << "\n" << "\n";
        tour_counter++;
    }
}

void population::select_parents()
{
    vector<tour> temp;
    vector<tour> parent_pool;
    while(temp.size() != (unsigned)number_of_parents)
    {
        uniform_int_distribution<> distr(number_of_elites, population_size-1);

        int parent_number = distr(eng);

        for(int i = 0; i < parent_pool_size; ++i)
        {
            parent_pool.push_back(tours[parent_number]);
        }

        sort(parent_pool.begin(), parent_pool.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});


        if(!(find(parents.begin(), parents.end(), parent_pool.front()) != parents.end()))
            temp.push_back(parent_pool.front());
    }

    parents = temp;
}

bool population::contains_city(vector<city> cities, city city)
{
    return find(cities.begin(), cities.end(), city) != cities.end();
}

tour population::crossover()
{
    vector<city> child_cities;
    int number_of_indices = number_of_parents - 1;
    vector<int> selection_indices;

    for(int i = 0; i < number_of_indices; ++i)
    {
        uniform_int_distribution<> distr(0, cities_in_tour);

        int index = distr(eng);

        selection_indices.push_back(index);
    }

    int counter {0};

    vector<tour>::iterator it;

    for(it = parents.begin(); it != parents.end() - 1; ++it)
    {
        for (int i = 0; i < selection_indices[counter]; ++i)
            if(!contains_city(child_cities, it->get_cities()[i]))
                child_cities.push_back(it->get_cities()[i]);

        counter++;
    }

    while (child_cities.size() < (unsigned)cities_in_tour)
    {
        for(auto city : it->get_cities())
        {
            if(!(contains_city(child_cities, city)))
                child_cities.push_back(city);
        }
    }

    tour *child = new tour(child_cities);

    child->mutate(mutation_rate);

    return *child;
}

void population::repopulate()
{
    vector<tour> new_population;
    for(int i = 0; i < number_of_elites; ++i)
        new_population.push_back(tours[i]);

    for(int i = number_of_elites; i < population_size; ++i)
        new_population.push_back(crossover());

    tours = new_population;

    sort(tours.begin(), tours.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});
}

void population::run(ostream &os)
{
    int counter;

    for(counter = 0; counter < iterations; ++counter)
    {
        select_parents();
        repopulate();
    }

    for(int i {0}; i < population_size; ++i)
    {
        for(auto c : tours[i].get_cities())
        {
            os << "FINAL TOUR " << i << ": " << c << "\n";
        }
        os << "DISTANCE = " << tours[i].get_tour_distance() << "\n";
        os << "FITNESS = " << tours[i].get_fitness() << "\n" << "\n";
    }

    cout << "REPORT:" << "\n";

    cout << "Genetic Algorithm was run " << counter << " times" << "\n";

    cout << "New fitness level: " << tours.front().get_fitness() << "\n";
    cout << "Old fitness level: " << base_fitness << "\n";
}