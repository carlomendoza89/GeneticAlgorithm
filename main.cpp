#include <iostream>
#include <iomanip>

#include "population.hpp"

using namespace std;

int main() {
    cout << setprecision(2) << fixed;

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

    population *p = new population(CITIES_IN_TOUR, POPULATION_SIZE, NUMBER_OF_ELITES, PARENT_POOL_SIZE, NUMBER_OF_PARENTS, MUTATION_RATE, ITERATIONS);
    p->init(cout);
    p->run(cout);
    p->report(cout);

    return 0;
}