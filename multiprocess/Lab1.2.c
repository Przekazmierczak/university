#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

struct vector {
    int length;
    int* vector;
};

struct matrix {
    int row;
    int col;
    int* matrix;
};

void singleMultiCompare(void (*fun)(int)) {
    printf("Wywolanie sekwencyjne:\n");
    fun(0);
    printf("Wywolanie rownolegle:\n");
    fun(1);
}

/*
2.1 Napisać semantycznie tożsame programy w OpenMP, które korzystają ze zmiennej
prywatnej zdeklarowanej jawnie i niejawnie (bez zastosowania klauzuli).
*/
void zad_2_1_jawnie(int multi) {
    int nthreads, tid;

    #pragma omp parallel private(nthreads, tid) if(multi)
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

void zad_2_1_niejawnie(int multi) {
    #pragma omp parallel if(multi)
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

/*
2.2 Napisać semantycznie tożsame programy w OpenMP, które korzystają ze zmiennej dzielonej
zdeklarowanej jawnie i niejawnie (bez zastosowania klauzuli).
*/
void zad_2_2_jawnie(int multi) {
    int num = 0;

    #pragma omp parallel shared(num) if(multi)
    {
        num++;
        printf("Num = %d\n", num);
    }
}

void zad_2_2_niejawnie(int multi) {
    int num = 0;

    #pragma omp parallel if(multi)
    {
        num++;
        printf("Num = %d\n", num);
    }
}

/*
Napisać program w OpenMP, który korzysta ze zmiennej firstprivate.
*/
void zad_2_3(int multi) {
    int nthreads, tid;
    int id_increment = 10;

    #pragma omp parallel firstprivate(id_increment) if(multi)
    {
        tid = omp_get_thread_num() + id_increment;
        printf("Hello World from thread = %d\n", tid);

        if (tid == id_increment){
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}

/*
2.4 Napisać program w OpenMP, ktory zawiera zakres statyczny i dynamiczny do znalezienia
summy dwóch wektorów, określić jaki jest zakres każdej zmiennej (prywatny/dzielony) w
regionie równoległym.
*/
void printSumStatic(int multi, struct vector A, struct vector B) {
    struct vector C;
    C.length = A.length;
    int arrayC[C.length];
    C.vector = arrayC;

    #pragma omp parallel for schedule(static) if(multi)
    for (int i = 0; i < A.length; i++) {
        C.vector[i] = A.vector[i] + B.vector[i];
    }

    for (int i = 0; i < C.length; i++) {
        printf("C[%d] = %d\n", i, C.vector[i]);
    }
}

void printSumDynamic(int multi, struct vector A, struct vector B) {
    struct vector C;
    C.length = A.length;
    int arrayC[C.length];
    C.vector = arrayC;

    #pragma omp parallel for schedule(dynamic, 2) num_threads(2) if(multi)
    for (int i = 0; i < A.length; i++) {
        C.vector[i] = A.vector[i] + B.vector[i];
    }

    for (int i = 0; i < C.length; i++) {
        printf("C[%d] = %d\n", i, C.vector[i]);
    }
}

void zad_2_4(int multi) {
    int arrayA[6] = {1, 2, 3, 4, 5, 6};
    struct vector A;
    A.length = 6;
    A.vector = arrayA;

    int arrayB[6] = {6, 5, 4, 3, 2, 1};
    struct vector B;
    B.length = 6;
    B.vector = arrayB;

    printSumStatic(multi, A, B);
    printSumDynamic(multi, A, B);
}

/*
2.5 Napisać program w OpenMP, który zawiera zakres statyczny i dynamiczny do znalezienia
iloczynu skalarnego dwóch wektorów, określić jaki jest zakres każdej zmiennej
(prywatny/dzielony) w regionie równoległym.
*/

void printScalarProductStatic(int multi, struct vector A, struct vector B) {
    int iloczyn = 0;

    #pragma omp parallel for reduction(+:iloczyn) schedule(static) if(multi)
    for (int i = 0; i < A.length; i++) {
        iloczyn += A.vector[i] * B.vector[i];
    }

    printf("Iloczyn skalarny wynosi %d\n", iloczyn);
}

void printScalarProductDynamic(int multi, struct vector A, struct vector B) {
    int iloczyn = 0;

    #pragma omp parallel for reduction(+:iloczyn) schedule(dynamic, 2) num_threads(2) if(multi)
    for (int i = 0; i < A.length; i++) {
        iloczyn += A.vector[i] * B.vector[i];
    }

    printf("Iloczyn skalarny wynosi %d\n", iloczyn);
}

void zad_2_5(int multi) {
    int arrayA[6] = {1, 2, 3, 4, 5, 6};
    struct vector A;
    A.length = 6;
    A.vector = arrayA;

    int arrayB[6] = {6, 5, 4, 3, 2, 1};
    struct vector B;
    B.length = 6;
    B.vector = arrayB;

    printScalarProductStatic(multi, A, B);
    printScalarProductDynamic(multi, A, B);
}

/*
2.6 Napisać program w OpenMP, który zawiera zakres statyczny i dynamiczny do mnożenia
dwóch macierzy, określić jaki jest zakres każdej zmiennej (prywatny/dzielony) w regionie
równoległym.
*/
void printMatrixMulStatic(int multi, struct matrix A, struct matrix B) {
    int arrayC[9] = {0, 0, 0, 0, 0, 0, 0, 0 ,0};
    struct matrix C;
    C.row = A.row;
    C.col = A.col;
    C.matrix = arrayC;

    #pragma omp parallel for schedule(static) collapse(2) if(multi)
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < B.col; j++) {
            C.matrix[i*B.col + j] = 0;

            for (int k = 0; k < A.col; k++) {
                C.matrix[i*B.col + j] +=
                    A.matrix[i*A.col + k] *
                    B.matrix[k*B.col + j];
            }
        }
    }

    for (int i = 0; i < C.row; i++) {
        for (int j = 0; j < C.col; j++) {
            printf("%d ", C.matrix[i*C.col + j]);
        }
        printf("\n");
    }
}

void printMatrixMulDynamic(int multi, struct matrix A, struct matrix B) {
    int arrayC[9] = {0, 0, 0, 0, 0, 0, 0, 0 ,0};
    struct matrix C;
    C.row = A.row;
    C.col = A.col;
    C.matrix = arrayC;

    #pragma omp parallel for schedule(dynamic, 2) num_threads(3) collapse(2) if(multi)
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < B.col; j++) {
            C.matrix[i*B.col + j] = 0;

            for (int k = 0; k < A.col; k++) {
                C.matrix[i*B.col + j] +=
                    A.matrix[i*A.col + k] *
                    B.matrix[k*B.col + j];
            }
        }
    }

    for (int i = 0; i < C.row; i++) {
        for (int j = 0; j < C.col; j++) {
            printf("%d ", C.matrix[i*C.col + j]);
        }
        printf("\n");
    }
}

void zad_2_6(int multi) {
    int arrayA[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct matrix A;
    A.row = 3;
    A.col = 3;
    A.matrix = arrayA;

    int arrayB[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct matrix B;
    B.row = 3;
    B.col = 3;
    B.matrix = arrayB;

    printMatrixMulStatic(multi, A, B);
    printMatrixMulDynamic(multi, A, B);
}

/*
2.7 Napisać program w OpenMP, który zawiera zakres statyczny i dynamiczny do znalezienia
mnożenia macierzy przez wektor, określić jaki jest zakres każdej zmiennej
(prywatny/dzielony) w regionie równoległym.
*/
void printMatrixVectorMulStatic(int multi, struct matrix A, struct vector B) {
    int arrayC[3] = {0};
    struct vector C;
    C.length = A.row;
    C.vector = arrayC;

    #pragma omp parallel for schedule(static) if(multi)
    for (int i = 0; i < A.row; i++) {

        int sum = 0;

        for (int j = 0; j < A.col; j++) {
            sum += A.matrix[i*A.col + j] * B.vector[j];
        }

        C.vector[i] = sum;
    }

    for (int i = 0; i < C.length; i++) {
        printf("%d ", C.vector[i]);
    }
    printf("\n");
}

void printMatrixVectorMulDynamic(int multi, struct matrix A, struct vector B) {
    int arrayC[3] = {0};
    struct vector C;
    C.length = A.row;
    C.vector = arrayC;

    #pragma omp parallel for schedule(dynamic) num_threads(2) if(multi)
    for (int i = 0; i < A.row; i++) {

        int sum = 0;

        for (int j = 0; j < A.col; j++) {
            sum += A.matrix[i*A.col + j] * B.vector[j];
        }

        C.vector[i] = sum;
    }

    for (int i = 0; i < C.length; i++) {
        printf("%d ", C.vector[i]);
    }
    printf("\n");
}

void zad_2_7(int multi) {
    int arrayA[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct matrix A;
    A.row = 3;
    A.col = 3;
    A.matrix = arrayA;

    int arrayB[3] = {1, 2, 3};
    struct vector B;
    B.length = 3;
    B.vector = arrayB;

    printMatrixVectorMulStatic(multi, A, B);
    printMatrixVectorMulDynamic(multi, A, B);
}

/*
2.8 Napisać program w OpenMP do znalezienia sumy wszystkich elementów wektora z
zastosowaniem klauzuli reduction.
*/
void printVectorSum(int multi, struct vector A) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum) schedule(static) if(multi)
    for (int i = 0; i < A.length; i++) {
        sum += A.vector[i];
    }

    printf("Suma wszystkich elementow wektora: %d\n", sum);
}

void zad_2_8(int multi) {
    int arrayA[6] = {1, 2, 3, 4, 5, 6};
    struct vector A;
    A.length = 6;
    A.vector = arrayA;

    printVectorSum(multi, A);
}

/*
2.9 Napisać program w OpenMP do znalezienie liczby znaków łańcucha z zastosowaniem
klauzuli reduction.
*/
void zad_2_9(int multi) {
    char string[] = "Hello World!";
    int length = sizeof(string) / sizeof(string[0]) - 1;
    int count = 0;

    #pragma omp parallel for reduction(+:count) if(multi)
    for (int i = 0; i < length; i++) {
        if (string[i] != ' ') count++;
    }

    printf("Liczba znakow: %d\n", count);
}

/*
2.10 Napisać program w OpenMP do znalezienie liczby słów zdania z zastosowaniem
klauzuli reduction.
*/
void zad_2_10(int multi) {
    char string[] = "Hello World";
    int length = sizeof(string) / sizeof(string[0]) - 1;
    int count = 0;

    if (length > 0) {
        #pragma omp parallel for reduction(+:count) if(multi)
        for (int i = 1; i < length; i++) {
            if (string[i - 1] == ' ' && string[i] != ' ') count++;
        }

        if (string[0] != ' ') count++;
    }

    printf("Liczba slow: %d\n", count);
}

/*
2.11 Napisać program w OpenMP do znalezienie liczby zer w liczbie binarnej z
zastosowaniem klauzuli reduction.
*/
void zad_2_11(int multi) {
    char binary[] = "01010101010010001010";
    int length = sizeof(binary) / sizeof(binary[0]) - 1;
    int count = 0;

    #pragma omp parallel for reduction(+:count) if(multi)
    for (int i = 0; i < length; i++) {
        if (binary[i] == '0') count++;
    }

    printf("Liczba zer: %d\n", count);
}

/*
2.12 Napisać program w OpenMP do znalezienie liczby jedynek w liczbie binarnej z
zastosowaniem klauzuli reduction.
*/
void zad_2_12(int multi) {
    char binary[] = "01010101010010001010";
    int length = sizeof(binary) / sizeof(binary[0]) - 1;
    int count = 0;

    #pragma omp parallel for reduction(+:count) if(multi)
    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') count++;
    }

    printf("Liczba jedynek: %d\n", count);
}

int main(int argc, char *argv[]) {
    // singleMultiCompare(zad_2_1_jawnie);
    // singleMultiCompare(zad_2_1_niejawnie);
    // singleMultiCompare(zad_2_2_jawnie);
    // singleMultiCompare(zad_2_2_niejawnie);
    // singleMultiCompare(zad_2_3);
    // singleMultiCompare(zad_2_4);
    // singleMultiCompare(zad_2_5);
    // singleMultiCompare(zad_2_6);
    // singleMultiCompare(zad_2_7);
    // singleMultiCompare(zad_2_8);
    // singleMultiCompare(zad_2_9);
    // singleMultiCompare(zad_2_10);
    // singleMultiCompare(zad_2_11);
    // singleMultiCompare(zad_2_12);
}