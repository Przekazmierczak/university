//g++-15 -fopenmp *.cpp

#include <iostream>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 100; i++) {
        sum += i;
    }

    std::cout << sum << std::endl;

    return 0;
}