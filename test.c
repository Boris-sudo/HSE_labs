#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Функция для генерации случайного числа в диапазоне [min, max]
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Функция для генерации случайного символа (буква или цифра)
char random_char() {
    int type = rand() % 3;

    if (type == 0) {
        // Цифра
        return '0' + rand() % 10;
    } else if (type == 1) {
        // Строчная буква
        return 'a' + rand() % 26;
    } else {
        // Заглавная буква
        return 'A' + rand() % 26;
    }
}

// Функция для генерации одного слова
void generate_word(char* word, int max_length) {
    int length = random_int(8, max_length);

    for (int i = 0; i < length; i++) {
        word[i] = random_char();
    }
    word[length] = '\0';
}

int main() {
    fileno
}