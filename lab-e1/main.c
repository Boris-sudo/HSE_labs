#include <stdio.h>
#include "../libs/input.h"
#define forn(i,n) for(int i=0;i<n;++i)
#define fornn(i,l,r) for(int i=l;i<=r;++i)
#define ford(i,n) for(int i=n-1;i>=0;--i)

void print(char str[100]) {
    int toprint=0;
    forn(i,100) {
        if (str[i] != 0) {
            toprint = 1;
            break;
        }
    }
    if (toprint == 0) return;
    printf("%s\n", str);
}

int symbol_validator(char c) {
    return 1;
}

signed main() {
    const int n = 100;
    char str[n];
    printf("Введите строку для форматирования: ");
    fgets(str, sizeof(str), stdin);

    char c;
    input_char(&c, "Введите символ: ", "Введите один символ!", symbol_validator);

    char string[n];
    forn(i,n) string[i] = 0;
    int index = 0;
    int printed = 1;

    printf("Результат форматирования:\n");
    forn(i, n) {
        if (str[i] == 0) break;
        if (str[i] == ' ') {
            if (printed == 1) print(string);
            forn(j, 100) string[j] = 0;
            printed = 1;
            index = 0;
            continue;
        }
        if (str[i] == c) printed = 0;
        string[index++] = str[i];
    }
    if (printed == 1) print(string);
}
