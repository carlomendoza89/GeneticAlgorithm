//
// Created by Carlo on 2018-11-18.
//

#include "tour.hpp"
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

constexpr double FITNESS_SCALAR {1000000};
constexpr int SHUFFLES {64};

tour::tour() = default;
tour::tour(vector<city> cities) : cities{cities}
{
    shuffle_cities();
    fitness = determine_fitness();
}
tour::tour(const tour &c) = default;
tour::~tour() = default;

vector<city> tour::get_cities()
{
    return cities;
}

double tour::get_fitness() const
{
    return fitness;
}

void tour::shuffle_cities()
{
    for(int i = 0; i < SHUFFLES; i++)
        random_shuffle(this->cities.begin(), this->cities.end());
}

double tour::get_distance_between_cities(city first, city second) const
{
    return sqrt(pow(second.get_x() - first.get_x(), 2) + pow(second.get_y() - first.get_y(), 2));
}

double tour::get_tour_distance() const
{
    double distance {0};

    for(size_t i = 0; i < cities.size() - 1; ++i)
        distance += get_distance_between_cities(cities[i], cities[i+1]);

    return distance;
}

double tour::determine_fitness()
{
    return (1/get_tour_distance()) * FITNESS_SCALAR;
}

void tour::mutate(double mutation_rate)
{
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(0, 1);

    vector<double> mutation_values;

    for(auto city : cities)
    {
        double value = distribution(generator);
        mutation_values.push_back(value);
    }

    for(size_t i = 0; i < mutation_values.size(); ++i)
    {
        if(mutation_values[i] < mutation_rate)
        {
            if(cities[i] == cities.front())
            {
                swap(cities[i], cities[i+1]);
            } else if(cities[i] == cities.back())
            {
                swap((cities[i]), cities[i-1]);
            } else
            {
                random_device rd;
                mt19937 eng(rd());
                uniform_int_distribution<> distr(0, 1);

                int up_or_down = distr(eng);

                if(up_or_down == 1)
                {
                    swap(cities[i], cities[i+1]);
                }
                else
                {
                    swap((cities[i]), cities[i-1]);
                }
            }
        }
    }
    fitness = determine_fitness();
}

bool tour::operator==(const tour & t)
{
    return equal(cities.begin(), cities.end(), t.cities.begin());
}