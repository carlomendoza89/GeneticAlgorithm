cmake_minimum_required(VERSION 3.12)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(GeneticAlgorithm main.cpp city.cpp city.hpp tour.cpp tour.hpp population.cpp population.hpp)