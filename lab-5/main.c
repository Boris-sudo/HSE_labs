#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libs/input.h"
#include "../libs/utils.h"

char* transform(char* str, size_t len) {

    char arr[50][100];
    forn(i,50) forn(j,100) arr[i][j] = 0;
    int arr_index = 0, word_index = 0;
    forn(i, len) if (str[i]==',' || str[i]=='.') arr_index++, word_index = 0; else arr[arr_index][word_index++] = str[i];

    char *res = str; int index = 0;
    ford(i,50)if (arr[i][0]!=0){forn(j,100)if (arr[i][j]!=0)res[index++]=arr[i][j];if (i!=0)res[index++]=',';}
    res[index]='.';

    return res;
}

int main() {
    srand(time(NULL));

    const int type = 0; // 0 - self test, 1 - auto test
    char *str = NULL;

    while (str != "-") {
        size_t len = input_string(&str, "Введите строку для форматирования: ", "Ошибка, попробуйте ещё раз!");
        char* new_string = transform(str, len);
    }

    return 0;
}