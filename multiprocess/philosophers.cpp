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

void tryFork0(Philosopher& philosopher, int* forks) {
    #pragma omp critical (fork0)
    {
        if (forks[0] == -1) {
            forks[0] = philosopher.id;
        }
    }
}

void tryFork1(Philosopher& philosopher, int* forks) {
    #pragma omp critical (fork1)
    {
        if (forks[1] == -1) {
            forks[1] = philosopher.id;
        }
    }
}

void tryFork2(Philosopher& philosopher, int* forks) {
    #pragma omp critical (fork2)
    {
        if (forks[2] == -1) {
            forks[2] = philosopher.id;
        }
    }
}

void tryFork3(Philosopher& philosopher, int* forks) {
    #pragma omp critical (fork3)
    {
        if (forks[3] == -1) {
            forks[3] = philosopher.id;
        }
    }
}

void tryFork4(Philosopher& philosopher, int* forks) {
    #pragma omp critical (fork4)
    {
        if (forks[4] == -1) {
            forks[4] = philosopher.id;
        }
    }
}

void (*tryForks[5])(Philosopher&, int*) = {
    tryFork0,
    tryFork1,
    tryFork2,
    tryFork3,
    tryFork4
};

void eating(Philosopher& philosopher, int& K, int* forks) {
    int right = philosopher.id;
    int left = (philosopher.id + 4) % 5;

    while (K > 0) {
        philosopher.tries++;

        tryForks[right](philosopher, forks);
        tryForks[left](philosopher, forks);


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
    int K = 100;
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

    for (Philosopher& philosopher : philosophers) {
        philosopher.print();
        totalTries += philosopher.tries;
        totalSuccesses += philosopher.successes;
    }

    std::cout << "Total tries: " << totalTries << " Total successes: " << totalSuccesses << std::endl;
}