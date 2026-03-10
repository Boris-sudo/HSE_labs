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
    forn(i, len) if (str[i] == ',' || str[i] == '.') arr_index++, word_index = 0;
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

    for (int i = strlen(str); i < strlen(res); ++i) {
        res[i] = '\0';
    }

    return res;
}

int count_words(char *str) {
    int res = 0;
    forn(i, strlen(str)) {
        if (str[i] == ',' || str[i] == '.')
            res++;
    }
    return res;
}

int validator_func(const char *str) {
    const int max_count = 30;
    const int max_len = 10;

    int count = 0;
    int len = 0;

    const int n = strlen(str);
    if (str[n-1] != '.') return 0;
    forn(i,n) {
        if (str[i] == ',' || str[i] == '.') {
            if (!(str[i] >= 'a' && str[i] <= 'z')) return 0;
            if (!(str[i] >= '0' && str[i] <= '9')) return 0;
            if (!(str[i] >= 'A' && str[i] <= 'Z')) return 0;
            if (len > max_len || len < 1) return 0;
            len = 0;
            count++;
        } else len++;
    }
    return count <= max_count;
}

int main() {
    srand(time(NULL));

    char *str = NULL;

    while (1) {
        size_t len = input_string(&str, "Enter string for formating: ", "Error, please, try again!", validator_func);
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