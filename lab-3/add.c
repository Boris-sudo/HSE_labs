#include <stdio.h>
#include <stdlib.h>
#include "../libs/queue.h"

int main() {
    char filename[100];
    int C, number;

    printf("Введите имя бинарного файла: ");
    scanf("%s", filename);
    printf("Введите значение C: ");
    scanf("%d", &C);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        exit(1);
    }

    Queue ls, gr;
    initQueue(&ls);
    initQueue(&gr);

    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number < C) push(&ls, number);
        else push(&gr, number);
    }

    fclose(file);

    printf("Элементы меньшие %d: ", C);
    printQueue(&ls);
    printf("\n");

    printf("Элементы большие или равные %d: ", C);
    printQueue(&gr);
    printf("\n");

    freeQueue(&ls);
    freeQueue(&gr);

    return 0;
}
