#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../libs/input.h"

#define forn(i,n) for(int i=0;i<n;++i)
#define fornn(i,l,r) for(int i=l;i<=r;++i)
#define ford(i,n) for(int i=n-1;i>=0;--i)
#define sz(a) sizeof(a) / sizeof(a[0])5


int size_validator(int size) {
    return size >= 1 && size <= 100;
}

int threshold_validator(double threshold) {
    return threshold >= -1000 && threshold < 0;
}

double *create_array(int size) {
    return (double *) malloc(size * sizeof(double));
}

void fill_array(double *arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        /*int isDataValid;
        do {
            printf("Введите элемент [%d]: ", i);
            int scanResult = scanf("%lf", &arr[i]);
            if (scanResult != 1) {
                clearInputBuffer();
                isDataValid = 0;
            } else if (!isInputValid()) { isDataValid = 0; } else {
                isDataValid = (arr[i] >= -1000 && arr[i] <= 1000);
            }
            if (!isDataValid) {
                printf("Введите элемент массива от -1000 до 1000\n");
            }
        } while (!isDataValid);*/
        arr[i] = (rand() / (double) RAND_MAX) * 200 - 100;
        // if (arr[i] < 0) arr[i] = (int) arr[i];
    }
}

void print_array(double *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%7.2lf ", arr[i]);
    }
    printf("\n");
}

int remove_elements(double **arr, int size, double threshold) {
    int new_size = 0;

    for (int i = 0; i < size; i++) {
        if (!((*arr)[i] < 0 && (*arr)[i] < threshold)) {
            (*arr)[new_size] = (*arr)[i];
            new_size++;
        }
    }

    *arr = (double *) realloc(*arr, new_size * sizeof(double));
    return new_size;
}

int main() {
    int size = 20;
    double threshold;
    double *arr = NULL;

    // input_int(&size, "Введите размер массива: ", "Введите размер массива от 1 до 100", size_validator);
    arr = create_array(size);
    fill_array(arr, size);

    printf("Исходный массив: ");
    print_array(arr, size);

    input_double(&threshold, "Введите пороговое отрицательное число: ", "Введите отрицательное пороговое значение", threshold_validator);
    size = remove_elements(&arr, size, threshold);

    printf("Массив после удаления: ");
    print_array(arr, size);

    free(arr);
    return 0;
}
