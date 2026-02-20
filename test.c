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
    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Генерация количества слов (1-30)
    int word_count = random_int(25, 30);

    // Максимальный размер строки (30 слов * 10 символов + 29 запятых + точка + \0)
    char result[30 * 10 + 29 + 1 + 1] = "";
    char word[11]; // 10 символов + \0

    for (int i = 0; i < word_count; i++) {
        // Генерация слова
        generate_word(word, 10);

        // Добавление слова к результату
        strcat(result, word);

        // Добавление запятой (кроме последнего слова)
        if (i < word_count - 1) {
            strcat(result, ",");
        }
    }

    // Добавление точки в конце
    strcat(result, ".");

    // Вывод результата
    printf("%s\n", result);

    return 0;
}