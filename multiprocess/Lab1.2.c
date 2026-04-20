#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int zad_2_1_jawnie() {
    int nthreads, tid;

    #pragma omp parallel private(nthreads, tid)
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

int zad_2_1_niejawnie() {
    #pragma omp parallel
    {
        int nthreads, tid;

        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);
        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

int zad_2_2_jawnie() {
    int nthreads, tid;

    #pragma omp parallel shared(nthreads, tid)
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

int zad_2_2_niejawnie() {
    int nthreads, tid;

    #pragma omp parallel
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

int zad_2_3() {
    int nthreads, tid;
    int id_increment = 10;

    #pragma omp parallel firstprivate(id_increment)
    {
        tid = omp_get_thread_num() + id_increment;
        printf("Hello World from thread = %d\n", tid);

        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

int zad_2_3_static() {
    int A[6] = {1, 2, 3, 4, 5, 6};
    int B[6] = {6, 5, 4, 3, 2, 1};
    int n = 6;

    int C[6];

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }

    for (int i = 0; i < n; i++) {
        printf("C[%d] = %d\n", i, C[i]);
    }
}

int zad_2_3_dynamic() {
    int A[6] = {1, 2, 3, 4, 5, 6};
    int B[6] = {6, 5, 4, 3, 2, 1};
    int n = 6;

    int C[6];

    #pragma omp parallel for schedule(dynamic, 2) num_threads(2)
    for (int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }

    for (int i = 0; i < n; i++) {
        printf("C[%d] = %d\n", i, C[i]);
    }
}

int zad_2_4_static() {
    int A[6] = {1, 2, 3, 4, 5, 6};
    int B[6] = {6, 5, 4, 3, 2, 1};
    int n = 6;

    int iloczyn = 0;

    #pragma omp parallel for reduction(+:iloczyn) schedule(static)
    for (int i = 0; i < n; i++) {
        iloczyn += A[i] + B[i];
    }

    printf("Iloczyn skalarny wynosi %d\n", iloczyn);
}

int zad_2_4_dynamic() {
    int A[6] = {1, 2, 3, 4, 5, 6};
    int B[6] = {6, 5, 4, 3, 2, 1};
    int n = 6;

    int iloczyn = 0;

    #pragma omp parallel for reduction(+:iloczyn) schedule(dynamic, 2) num_threads(2)
    for (int i = 0; i < n; i++) {
        iloczyn += A[i] + B[i];
    }

    printf("Iloczyn skalarny wynosi %d\n", iloczyn);
}

int main(int argc, char *argv[]) {
    //zad_2_1_jawnie();
    //zad_2_1_niejawnie();
    //zad_2_2_jawnie();
    //zad_2_2_niejawnie();
    //zad_2_3();
    // zad_2_3_static();
    // zad_2_3_dynamic();
    zad_2_4_static();
    zad_2_4_dynamic();
}