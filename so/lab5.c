#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int validatedStoi(char* arg) {
    char *end;
    long num = strtol(arg, &end, 10);
    if (*end == '\0' && num >= 0 && num <= 100) {
        return (int)num;
    }
    return -1;
}

char** fillArgs(int size, int firstIndex, char** argv) {
    char** args = malloc((size + 2) * sizeof(char*));
    if (!args) return NULL;

    args[0] = argv[0];
    args[size + 1] = NULL;

    for (int i = 0; i < size; i++) { args[i + 1] = argv[firstIndex + i]; }
    return args;
}

void printArgs(char** args) {
    args++;

    int first = 1;
    printf("[");
    while (*args) {
        if (!first) { printf(", %s", *args++); }
        else { printf("%s", *args++); first = 0; }
    }
    printf("]");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "The program requires at least one argument.\n");
        return 201;
    }

    for (int i = 1; i < argc; i++) {
        if (validatedStoi(argv[i]) == -1) {
            fprintf(stderr, "One of the arguments is not a number in the range [0-100].\n");
            return 202;
        }
    }
    
    if (argc == 2) {
        return validatedStoi(argv[1]);
    }

    if (argc == 3) {
        int arg1 = validatedStoi(argv[1]);
        int arg2 = validatedStoi(argv[2]);
        return arg1 > arg2 ? arg1 : arg2;
    }

    int sizeR = argc / 2;
    int sizeL = argc - sizeR - 1;

    char** argsL = fillArgs(sizeL, 1, argv);
    char** argsR = fillArgs(sizeR, sizeL + 1, argv);
    if (!argsL || !argsR ) {
        fprintf(stderr, "Malloc failed.");
        free(argsL);
        free(argsR);
        return 203;
    }

    pid_t id1 = fork();
    if (id1 == 0) execv(argv[0], argsL);
    pid_t id2 = fork();
    if (id2 == 0) execv(argv[0], argsR);

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
    printf("P: %d, Res: %d\n\n", parentId, maxStatus);

    free(argsL);
    free(argsR);
    
    return maxStatus;
}