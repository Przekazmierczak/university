#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <pthread.h>
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
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

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

void *countLetters(void *data) {
    StartEnd *startEnd = (StartEnd *) data;
    pthread_t self = pthread_self();
    int locaHistogram[NUM_LETTERS] = {0};

    printf("Thread #%lu started start=%d, end=%d\n", (unsigned long)self, startEnd->start, startEnd->end - 1);

    fillHistogram(locaHistogram, startEnd->start, startEnd->end);

    pthread_mutex_lock(&mymutex);
    for (int i = 0; i < NUM_LETTERS; i++) {
        globalHistogram[i] += locaHistogram[i];
    }
    pthread_mutex_unlock(&mymutex);

    printf("Thread #%lu stopped\n", (unsigned long)self);

    return NULL;
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

    struct timespec tstart, tend;

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    if (nums == 0) {
        fillHistogram(globalHistogram, 0, words_cnt);
    } else {
        pthread_t threads[nums];
        StartEnd data[nums];
        int range = words_cnt / nums;
        int currStart = 0;


        for(int i = 0; i < nums; i++) {
            data[i].start = currStart;
            currStart += range;
            data[i].end = (i < nums - 1) ? currStart : words_cnt;

            pthread_create(
                threads + i, // pthread_t *thread,
                NULL, // pthread_attr_t *attr,
                countLetters, // void *(*start_routine) (void *),
                &data[i] // void *arg
            );
        }

        for(int i = 0; i < nums; i++) {
            pthread_join(
                threads[i], // pthread_t thread,
                NULL // void **retval
            );
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &tend);

    time_t sec = tend.tv_sec - tstart.tv_sec;
    long nsec = tend.tv_nsec - tstart.tv_nsec;

    if (nsec < 0) {
        sec--;
        nsec += 1000000000L;
    }

    printf("Execution time: %ld.%09ld s\n", sec, nsec);

    for (int i = 0; i < NUM_LETTERS; i++) {
        printf("%c : %6d", (char)('a' + i), globalHistogram[i]);
        (i % 5 == 4) ? printf("\n") : printf("     ");
    }
    printf("\n");

    freeWords();

	return 0;
}