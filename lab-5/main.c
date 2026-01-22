#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libs/input.h"
#include "../libs/utils.h"

char *transform(char *str, size_t len) {
    char arr[50][100];
    forn(i, 50) forn(j, 100) arr[i][j] = 0;
    int arr_index = 0, word_index = 0;
    forn(i, len) if (str[i] == ',' || str[i] == '.')
            arr_index++, word_index = 0;
        else arr[arr_index][word_index++] = str[i];

    char *res = malloc(len);
    int index = 0;
    ford(i, 50) {
        if (arr[i][0] != 0) {
            forn(j, 100) {
                if (arr[i][j] != 0)res[index++] = arr[i][j];
                else break;
            }
            if (i != 0) res[index++] = ',';
        }
    }
    res[index] = '.';

    for(int i=strlen(str); i<strlen(res); ++i) {
        res[i] = '\0';
    }

    return res;
}

int count_words(char *str) {
    int res = 0;
    forn(i,strlen(str)) {
        if (str[i]==',' || str[i]=='.')
            res++;
    }
    return res;
}

int main() {
    srand(time(NULL));

    const int type = 0; // 0 - self test, 1 - auto test
    char *str = NULL;

    while (1) {
        size_t len = input_string(&str, "Enter string for formating: ", "Error, please, try again!");
        if (len == 1 && str[0] == '-') break;
        char *new_string = transform(str, len);

        printf("Result string: %s\n", new_string);

        if (count_words(str) == count_words(new_string))
            printf("Words count is the same\n");
        else
            printf("!!! Words count is not the same\n");

        printf("\n");
    }

    return 0;
}