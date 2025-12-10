#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int validatedStoi(char* arg) {
    char *end;
    long num = strtol(arg, &end, 10);
    if (*end == '\0' && num >= 0 && num <= 100) {
        return (int)num;
    }
    return -1;
}

char* fillArgs(int size, int firstIndex, char** argv) {
    int stringLen = strlen(argv[0]) + 1;
    for (int i = 0; i < size; i++) {
        stringLen += strlen(argv[firstIndex + i]) + 1;
    }

    char* args = malloc(stringLen);
    if (!args) return NULL;

    char* ptrToEnd = args;

    char* ptrCurrArg = argv[0];
    while (*ptrCurrArg) {
        *(ptrToEnd++) = *(ptrCurrArg++);
    }
    *(ptrToEnd++) = ' ';

    for (int i = 0; i < size; i++) {
        ptrCurrArg = argv[firstIndex + i];
        while (*ptrCurrArg) {
            *(ptrToEnd++) = *(ptrCurrArg++);
        }

        if (i < size - 1) {
            *(ptrToEnd++) = ' ';
        }
    }
    *ptrToEnd = '\0';
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
    printf("%d\n", argc);
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

    char* argsL = fillArgs(sizeL, 1, argv);
    printf("%s\n", argsL);
    char* argsR = fillArgs(sizeR, sizeL + 1, argv);
    printf("%s\n", argsR);
    if (!argsL || !argsR ) {
        fprintf(stderr, "Malloc failed.");
        free(argsL);
        free(argsR);
        return 203;
    }

    STARTUPINFOA si1;
    PROCESS_INFORMATION pi1;
    memset(&si1, 0, sizeof(si1));
    memset(&pi1, 0, sizeof(pi1));
    si1.cb = sizeof(si1);

    if (CreateProcessA(
        NULL, // char *lpApplicationName
        argsL, // char *lpCommandLine
        NULL, // SECURITY_ATTRIBUTES *lpProcessAttributes
        NULL, // SECURITY_ATTRIBUTES *lpThreadAttributes
        0, // int bInheritHandles
        0, // int dwCreationFlags
        NULL, // void *lpEnvironment
        NULL, // char *lpCurrentDirectory
        &si1, // STARTUPINFOA *lpStartupInfo
        &pi1// PPROCESS_INFORMATION *lpProcessInformation
    ) == 0) {
        printf( "CreateProcess #%d failed (%d).\n", 1, GetLastError() );
        return 204;
    };

    STARTUPINFOA si2;
    PROCESS_INFORMATION pi2;
    memset(&si2, 0, sizeof(si2));
    memset(&pi2, 0, sizeof(pi2));
    si2.cb = sizeof(si2);

    if (CreateProcessA(
        NULL, // char *lpApplicationName
        argsR, // char *lpCommandLine
        NULL, // SECURITY_ATTRIBUTES *lpProcessAttributes
        NULL, // SECURITY_ATTRIBUTES *lpThreadAttributes
        0, // int bInheritHandles
        0, // int dwCreationFlags
        NULL, // void *lpEnvironment
        NULL, // char *lpCurrentDirectory
        &si2, // STARTUPINFOA *lpStartupInfo
        &pi2// PPROCESS_INFORMATION *lpProcessInformation
    ) == 0) {
        printf( "CreateProcess #%d failed (%d).\n", 2, GetLastError() );
        return 204;
    };

    // if (id1 == 0) execv(argv[0], argsL);
    // pid_t id2 = fork();
    // if (id2 == 0) execv(argv[0], argsR);

    // pid_t parentId = getpid();
    // int status1, child1 = waitpid(id1, &status1, 0);
    // int status2, child2 = waitpid(id2, &status2, 0);
    // if (WIFEXITED(status1)) status1 = WEXITSTATUS(status1);
    // if (WIFEXITED(status2)) status2 = WEXITSTATUS(status2);

    // printf("P: %d, Ch1: %d, Res: %d, Args: ", parentId, child1, status1);
    // printArgs(argsL);
    // printf("\n");

    // printf("P: %d, Ch2: %d, Res: %d, Args: ", parentId, child2, status2);
    // printArgs(argsR);
    // printf("\n");

    // int maxStatus = (status1 > status2 ? status1 : status2);
    // printf("P: %d, Res: %d\n\n", parentId, maxStatus);

    // free(argsL);
    // free(argsR);
    
    return 1;
}