#include <vector>
#include <fstream>
#include <iostream>

#include <omp.h>

struct Philosopher {
    int id;
    int tries = 0;
    int successes = 0;

    Philosopher(int philosopherId) {
        id = philosopherId;
    }

    void print() {
        std::cout << "Philosopher " << id << " Tries: " << tries << " Successes" << successes << std::endl;
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

        if (forks[right] == philosopher.id && forks[left] == philosopher.id)
        {
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

    Philosopher philosopher0(0);
    Philosopher philosopher1(1);
    Philosopher philosopher2(2);
    Philosopher philosopher3(3);
    Philosopher philosopher4(4);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            eating(philosopher0, K, forks);
        }

        #pragma omp section
        {
            eating(philosopher1, K, forks);
        }

        #pragma omp section
        {
            eating(philosopher2, K, forks);
        }

        #pragma omp section
        {
            eating(philosopher3, K, forks);
        }

        #pragma omp section
        {
            eating(philosopher4, K, forks);
        }
    }

    philosopher0.print();
    philosopher1.print();
    philosopher2.print();
    philosopher3.print();
    philosopher4.print();
}