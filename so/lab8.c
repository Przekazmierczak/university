#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <windows.h>
#include <time.h>

#define MAX_LINES 370200
#define NUM_LETTERS 26

typedef struct {
    int start;
    int end;
} StartEnd;

char **words;
int words_cnt;
int globalHistogram[NUM_LETTERS] = {0};
HANDLE mutex; 

int validatedStoi(char* arg) {
    char *end;
    long num = strtol(arg, &end, 10);
    if (*end == '\0' && num >= 0 && num <= 16) {
        return (int)num;
    }
    return -1;
}

void fillWords() {
	words = malloc(sizeof(char *) * MAX_LINES);
	FILE *f = fopen("words_alpha.txt", "r");
	assert(f != NULL);
	char line[255];

	for(words_cnt = 0; words_cnt < MAX_LINES; words_cnt++) {
		if(fgets(line, sizeof(line), f)){
			words[words_cnt] = strdup(line);
		} else {
			break;
        }
    }

    fclose(f);
}

void freeWords() {
	for(int i = 0; i < words_cnt; i++)
		free(words[i]);
	free(words);
}

void fillHistogram(int histogram[], int start, int end) {
    for (int curr = start; curr < end; curr++) {
        char* currentLetter = words[curr];
        while (*currentLetter != '\0') {
            int index = (int)(*currentLetter++) - 'a';
            if (index >= 0 && index < NUM_LETTERS) {
                histogram[index]++;
            }
        }
    }
}

DWORD WINAPI countLetters(LPVOID data) {
    StartEnd *startEnd = (StartEnd *) data;
    DWORD self = GetCurrentThreadId();
    int locaHistogram[NUM_LETTERS] = {0};

    printf("Thread #%lu started start=%d, end=%d\n", (unsigned long)self, startEnd->start, startEnd->end - 1);

    fillHistogram(locaHistogram, startEnd->start, startEnd->end);

    WaitForSingleObject(mutex, INFINITE);
    for (int i = 0; i < NUM_LETTERS; i++) {
        globalHistogram[i] += locaHistogram[i];
    }
    ReleaseMutex(mutex);

    printf("Thread #%lu stopped\n", (unsigned long)self);

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "The program requires exactly one argument.\n");
        return 201;
    }

    int nums = validatedStoi(argv[1]);
    if (nums == -1) {
        fprintf(stderr, "The argument is not a number in the range [0-16].\n");
        return 202;
    }

    fillWords();

    clock_t tstart = clock();

    if (nums == 0) {
        fillHistogram(globalHistogram, 0, words_cnt);
    } else {
        HANDLE threads[nums];
        DWORD thrdids[nums];
        StartEnd data[nums];

        mutex = CreateMutex(NULL, FALSE, NULL);

        int range = words_cnt / nums;
        int currStart = 0;

        for(int i = 0; i < nums; i++) {
            data[i].start = currStart;
            currStart += range;
            data[i].end = (i < nums - 1) ? currStart : words_cnt;

            threads[i] = CreateThread(
                NULL, // LPSECURITY_ATTRIBUTES lpThreadAttributes,
                0, // SIZE_T dwStackSize,
                countLetters, // LPTHREAD_START_ROUTINE lpStartAddress,
                data + i,// LPVOID lpParameter,
                0, // DWORD dwCreationFlags,
                thrdids +i // LPDWORD lpThreadId
            );
        }

        WaitForMultipleObjects(nums, threads, 1, INFINITE);
    }

    clock_t tend = clock();
    printf("Execution time: %.3f s\n", (double)(tend - tstart) / CLOCKS_PER_SEC);

    for (int i = 0; i < NUM_LETTERS; i++) {
        printf("%c : %6d", (char)('a' + i), globalHistogram[i]);
        (i % 5 == 4) ? printf("\n") : printf("     ");
    }
    printf("\n");

    freeWords();

	return 0;
}