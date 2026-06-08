#include <vector>
#include <fstream>
#include <iostream>

#include <omp.h>

struct Philosopher {
    int id;
    int tries = 0;
    int successes = 0;

    Philosopher(int philosopherId) : id(philosopherId) {}

    void print() {
        std::cout << "Philosopher " << id << " Tries: " << tries << " Successes " << successes << std::endl;
    }
};

void eating(Philosopher& philosopher, int& K, int* forks) {
    int right = philosopher.id;
    int left = (philosopher.id + 4) % 5;

    while (K > 0) {
        philosopher.tries++;
        
        #pragma omp critical
        {
            if (forks[right] == -1) {
                forks[right] = philosopher.id;
            }
        }
        #pragma omp critical
        {
            if (forks[left] == -1) {
                forks[left] = philosopher.id;
            }
        }

        if (forks[right] == philosopher.id && forks[left] == philosopher.id) {
            K--;
            philosopher.successes++;
        }

        if (forks[right] == philosopher.id) {
            forks[right] = -1;
        }

        if (forks[left] == philosopher.id) {
            forks[left] = -1;
        }
    }
}

int main() {
    int K = 500;
    int forks[5] = {-1, -1, -1, -1, -1};

    Philosopher philosophers[5] = {Philosopher(0), Philosopher(1), Philosopher(2), Philosopher(3), Philosopher(4)};

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            eating(philosophers[0], K, forks);
        }

        #pragma omp section
        {
            eating(philosophers[1], K, forks);
        }

        #pragma omp section
        {
            eating(philosophers[2], K, forks);
        }

        #pragma omp section
        {
            eating(philosophers[3], K, forks);
        }

        #pragma omp section
        {
            eating(philosophers[4], K, forks);
        }
    }

    int totalTries = 0;
    int totalSuccesses = 0;

    for (Philosopher philosopher : philosophers) {
        philosopher.print();
        totalTries += philosopher.tries;
        totalSuccesses += philosopher.successes;
    }

    std::cout << "Total tries: " << totalTries << " Total successes: " << totalSuccesses << std::endl;
}