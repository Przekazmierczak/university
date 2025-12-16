#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <pthread.h>

#define MAX_LINES 370200

char **words;
int words_cnt;
int letters[26];

void countLetters(int curr, int end) {
    for (; curr < end; curr++) {
        char* currentLetter = words[curr];
        while (*currentLetter != '\0') {
            int index = (int)(*currentLetter++) - 'a';
            if (index >= 0 && index <= 26) {
                letters[index]++;
            }
        }
    }
}

int main(int argc, char **argv) {
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

    countLetters(0, words_cnt);
    for (int i = 0; i < 26; i++) {
        printf("%d\n", letters[i]);
    }

	fclose(f);
	printf("lines in file: %d\n", words_cnt);
	for(int i = 0; i < words_cnt; i++)
		free(words[i]);
	free(words);
	return 0;
}