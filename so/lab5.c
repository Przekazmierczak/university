#include <stdio.h>
#include <stdlib.h>

int validate(char* arg) {
    char *end;
    long num = strtol(arg, &end, 10);
    if (*end == '\0' && num >= 0 && num <= 100) {
        return (int)num;
    }
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Program wymaga min. 1 argument.\n");
        return 201;
    }

    for (int i = 1; i < argc; i++) {
        if (validate(argv[i]) == -1) {
            printf("Jeden z podanych argumentow nie jest liczba z przedzialu 0-100.\n");
            return 202;
        }
    }

    if (argc == 2) {
        return validate(argv[1]);
    }

    if (argc == 3) {
        int arg1 = validate(argv[1]);
        int arg2 = validate(argv[2]);
        return arg1 > arg2 ? arg1 : arg2;
    }


    return 0;
}