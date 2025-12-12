#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void printArgs(char* args) {
    while (*args++ != ' ');
    printf("[");
    printf("%s", args);
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

    char* args[2];

    args[0] = fillArgs(sizeL, 1, argv);
    args[1] = fillArgs(sizeR, sizeL + 1, argv);
    if (!args[0] || !args[1] ) {
        fprintf(stderr, "Malloc failed.");
        free(args[0]); free(args[1]);
        return 203;
    }

    STARTUPINFOA si;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi[2];

    for (int i = 0; i < 2; i++) {
        memset(&pi[i], 0, sizeof(pi[i]));
    
        if (CreateProcessA(
            NULL, // char *lpApplicationName
            args[i], // char *lpCommandLine
            NULL, // SECURITY_ATTRIBUTES *lpProcessAttributes
            NULL, // SECURITY_ATTRIBUTES *lpThreadAttributes
            0, // int bInheritHandles
            0, // int dwCreationFlags
            NULL, // void *lpEnvironment
            NULL, // char *lpCurrentDirectory
            &si, // STARTUPINFOA *lpStartupInfo
            &pi[i]// PPROCESS_INFORMATION *lpProcessInformation
        ) == 0) {
            printf( "CreateProcess #%d failed (%lu).\n", i + 1, GetLastError() );
            free(args[0]); free(args[1]);
            return 204;
        };
    }

    HANDLE children[2] = { pi[0].hProcess, pi[1].hProcess };
    WaitForMultipleObjects(2, children, 1, INFINITE);
    
    DWORD parentId = GetCurrentProcessId();
    DWORD code[2] = { 0, 0 };
    int status[2];

    for (int i = 0; i < 2; i++) {
        GetExitCodeProcess(pi[i].hProcess, &code[i]);

        CloseHandle( pi[i].hProcess );
        CloseHandle( pi[i].hThread );
        
        if (code[i] == STILL_ACTIVE) {
            fprintf(stderr, "Something went wrong with waiting for child #%d.\n", i + 1);
            free(args[0]); free(args[1]);
            if (i == 0) {
                CloseHandle( pi[1].hProcess );
                CloseHandle( pi[1].hThread );
            }
            return 205;
        }
        status[i] = (int)code[i];
    
        printf("P: %lu, Ch%d: %lu, Res: %d, Args: ", parentId, i + 1, pi[i].dwProcessId, status[i]);
        printArgs(args[i]);
        printf("\n");
    }

    int maxStatus = (status[0] > status[1] ? status[0] : status[1]);
    printf("P: %lu, Res: %d\n\n", parentId, maxStatus);

    free(args[0]); free(args[1]);
    
    return maxStatus;
}