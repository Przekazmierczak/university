#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int validateStrtol(char* arg) {
    char *end;
    long num = strtol(arg, &end, 10);
    if (*end == '\0' && num >= 0 && num <= 100) {
        return (int)num;
    }
    return -1;
}

char** fillArgs(int size, int firstIndex, char** argv) {
    char** args = malloc((size + 2) * sizeof(char*));

    args[0] = argv[0];
    args[size + 1] = NULL;

    for (int i = 0; i < size; i++) {
        args[i + 1] = argv[firstIndex + i];
    }
    return args;
}

void printArgs(char** args) {
    int notFirst = 0;
    (void)*args++;

    printf("[");
    while (*args) {
        if (notFirst) {
            printf(", %s", *args++);
        } else {
            printf("%s", *args++);
            notFirst = 1;
        }
    }
    printf("]");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Program wymaga min. 1 argument.\n");
        return 201;
    }

    for (int i = 1; i < argc; i++) {
        if (validateStrtol(argv[i]) == -1) {
            printf("Jeden z podanych argumentow nie jest liczba z przedzialu 0-100.\n");
            return 202;
        }
    }

    if (argc == 2) {
        return validateStrtol(argv[1]);
    }

    if (argc == 3) {
        int arg1 = validateStrtol(argv[1]);
        int arg2 = validateStrtol(argv[2]);
        return arg1 > arg2 ? arg1 : arg2;
    }

    int sizeR = argc / 2;
    int sizeL = argc - sizeR - 1;

    char** argsL = fillArgs(sizeL, 1, argv);
    char** argsR = fillArgs(sizeR, sizeL + 1, argv);

    pid_t id1 = fork();
    if (id1 == 0) {
        execv(argv[0], argsL);
    }

    pid_t id2 = fork();
    if (id2 == 0) {
        execv(argv[0], argsR);
    }

    pid_t parentId = getpid();
    int status1, child1 = waitpid(id1, &status1, 0);
    int status2, child2 = waitpid(id2, &status2, 0);
    if (WIFEXITED(status1)) status1 = WEXITSTATUS(status1);
    if (WIFEXITED(status2)) status2 = WEXITSTATUS(status2);

    printf("P: %d, Ch1: %d, Res: %d, Args: ", parentId, child1, status1);
    printArgs(argsL);
    printf("\n");

    printf("P: %d, Ch2: %d, Res: %d, Args: ", parentId, child2, status2);
    printArgs(argsR);
    printf("\n");

    int maxStatus = (status1 > status2 ? status1 : status2);
    printf("P: %d, Res: %d", parentId, (status1 > status2 ? status1 : status2));
    printf("\n");
    printf("\n");
    
    return maxStatus;
}