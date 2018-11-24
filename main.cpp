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

vector<city> cities_to_visit;
vector<tour> population;
vector<tour> parents;

double base_fitness {0.0};

random_device rd;
mt19937 eng(rd());

void init(int CITIES_IN_TOUR, int POPULATION_SIZE)
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

    base_fitness = population.front().get_fitness();

    int tour_counter {0};

    for(vector<tour>::iterator it = population.begin(); it != population.end(); ++it)
    {
        for(auto c : it->get_cities())
        {
            cout << "STARTING TOUR " << tour_counter << ": " << c << "\n";
        }
        cout << "DISTANCE = " << it->get_tour_distance() << "\n";
        cout << "FITNESS = " << it->get_fitness() << "\n" << "\n";
        tour_counter++;
    }
}

void select_parents(int NUMBER_OF_PARENTS, int NUMBER_OF_ELITES, int POPULATION_SIZE, int PARENT_POOL_SIZE)
{
    vector<tour> temp;
    vector<tour> parent_pool;
    while(temp.size() != (unsigned)NUMBER_OF_PARENTS)
    {
        uniform_int_distribution<> distr(NUMBER_OF_ELITES, POPULATION_SIZE-1);

        int parent_number = distr(eng);

        for(int i = 0; i < PARENT_POOL_SIZE; ++i)
        {
            parent_pool.push_back(population[parent_number]);
        }

        sort(parent_pool.begin(), parent_pool.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});


        if(!(find(parents.begin(), parents.end(), parent_pool.front()) != parents.end()))
            temp.push_back(parent_pool.front());
    }

    parents = temp;
}

bool contains_city(vector<city> cities, city city)
{
    return find(cities.begin(), cities.end(), city) != cities.end();
}

tour crossover(int NUMBER_OF_PARENTS, int CITIES_IN_TOUR, int MUTATION_RATE)
{
    vector<city> child_cities;
    int number_of_indices = NUMBER_OF_PARENTS - 1;
    vector<int> selection_indices;

    for(int i = 0; i < number_of_indices; ++i)
    {
        uniform_int_distribution<> distr(0, CITIES_IN_TOUR);

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

    while (child_cities.size() < (unsigned)CITIES_IN_TOUR)
    {
        for(auto city : it->get_cities())
        {
            if(!(contains_city(child_cities, city)))
                child_cities.push_back(city);
        }
    }

    tour *child = new tour(child_cities);

    child->mutate(MUTATION_RATE);

    return *child;
}

void repopulate(int NUMBER_OF_ELITES, int POPULATION_SIZE, int NUMBER_OF_PARENTS, int CITIES_IN_TOUR, int MUTATION_RATE)
{
    vector<tour> new_population;
    for(int i = 0; i < NUMBER_OF_ELITES; ++i)
        new_population.push_back(population[i]);

    for(int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i)
        new_population.push_back(crossover(NUMBER_OF_PARENTS, CITIES_IN_TOUR, MUTATION_RATE));

    population = new_population;

    sort(population.begin(), population.end(), [](tour a, tour b) {return a.get_fitness() > b.get_fitness();});
}

int main() {
    cout << setprecision(2) << fixed;

//    int CITIES_IN_TOUR {32};
//    int POPULATION_SIZE (32);
//    int NUMBER_OF_ELITES {1};
//    int PARENT_POOL_SIZE {5};
//    int NUMBER_OF_PARENTS {2};
//    double MUTATION_RATE {0.05};
//    int ITERATIONS {1000};

    int CITIES_IN_TOUR;
    int POPULATION_SIZE;
    int NUMBER_OF_ELITES;
    int PARENT_POOL_SIZE;
    int NUMBER_OF_PARENTS;
    double MUTATION_RATE;
    int ITERATIONS;

    while(true)
    {
        cout << "Enter the amount of cities in each tour: ";
        cin >> CITIES_IN_TOUR;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid integer." << "\n";
            continue;
        }
        if(CITIES_IN_TOUR < 2)
        {
            cout << "You need at least 2 cities in each tour." << "\n";
            continue;
        }
        else
            break;
    }

    while(true)
    {
        cout << "\n" << "Enter the population size: ";
        cin >> POPULATION_SIZE;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid integer." << "\n";
            continue;
        }
        if(POPULATION_SIZE < 2)
        {
            cout << "You need at least 2 tours in the population." << "\n";
            continue;
        }
        else
            break;
    }

    while(true)
    {
        cout << "\n" << "Enter the number of elites per generation: ";
        cin >> NUMBER_OF_ELITES;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid integer." << "\n";
            continue;
        }
        if(NUMBER_OF_ELITES >= POPULATION_SIZE)
        {
            cout << "You need less elites than the population size." << "\n";
            cout << "Please enter an integer less than " << POPULATION_SIZE << ".\n";
            continue;
        }
        if(NUMBER_OF_ELITES < 0)
        {
            cout << "You cannot have less than 0 elites." << "\n";
            continue;
        }
        else
            break;
    }

    while(true)
    {
        cout << "\n" << "Enter the parent pool size from which to choose a new parent: ";
        cin >> PARENT_POOL_SIZE;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid integer." << "\n";
            continue;
        }
        if(PARENT_POOL_SIZE > POPULATION_SIZE)
        {
            cout << "Your cannot have a larger parent pool than population size." << "\n";
            cout << "Please enter an integer less than " << POPULATION_SIZE << ".\n";
            continue;
        }
        if(PARENT_POOL_SIZE < 1)
        {
            cout << "You must have at least 1 parent in the parent pool." << "\n";
            continue;
        }
        else
            break;
    }

    while(true)
    {
        cout << "\n" << "Enter the number of parents needed to create a new tour: ";
        cin >> NUMBER_OF_PARENTS;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid integer." << "\n";
            continue;
        }
        if(NUMBER_OF_PARENTS > POPULATION_SIZE)
        {
            cout << "Your can only choose as many parents as the population size." << "\n";
            cout << "Please enter an integer less than " << POPULATION_SIZE << ".\n";
            continue;
        }
        if(NUMBER_OF_PARENTS < 2)
        {
            cout << "You need at least 2 parents to spawn a tour." << "\n";
            continue;
        }
        else
            break;
    }

    while(true)
    {
        cout << "\n" << "Enter the mutation rate for new tours: ";
        cin >> MUTATION_RATE;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid double." << "\n";
            continue;
        }
        if(MUTATION_RATE < 0 || MUTATION_RATE > 1)
        {
            cout << "Mutation rate needs to be a double between 0 and 1 (inclusive)." << "\n";
            continue;
        }
        else
            break;
    }

    while(true)
    {
        cout << "\n" << "Enter the number of iterations you want to run: ";
        cin >> ITERATIONS;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Please enter a valid integer." << "\n";
            continue;
        }
        if(ITERATIONS < 1)
        {
            cout << "You need at least 1 iteration." << "\n";
            continue;
        }
        else
            break;
    }

    init(CITIES_IN_TOUR, POPULATION_SIZE);

    int counter = 0;

    for(int i = 0; i < ITERATIONS; i++)
    {
        select_parents(NUMBER_OF_PARENTS, NUMBER_OF_ELITES, POPULATION_SIZE, PARENT_POOL_SIZE);
        repopulate(NUMBER_OF_ELITES, POPULATION_SIZE, NUMBER_OF_PARENTS, CITIES_IN_TOUR, MUTATION_RATE);
        counter++;
    }

    for(int i = 0; i < POPULATION_SIZE; ++i)
    {
        for(auto c : population[i].get_cities())
        {
            cout << "FINAL TOUR " << i << ": " << c << "\n";
        }
        cout << "DISTANCE = " << population[i].get_tour_distance() << "\n";
        cout << "FITNESS = " << population[i].get_fitness() << "\n" << "\n";
    }

    cout << "Genetic Algorithm was run " << counter << " times" << "\n";

    cout << "New fitness level: " << population.front().get_fitness() << "\n";
    cout << "Old fitness level: " << base_fitness << "\n";

    return 0;
}