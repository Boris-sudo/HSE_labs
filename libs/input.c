#include "input.h"
#include <stdio.h>

int isWhiteSpace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

int isInputValid() {
    int c;
    while ((c = getchar()) != '\n') {
        if (!isWhiteSpace(c)) {
            while ((c = getchar()) != '\n');
            return 0;
        }
    }
    return 1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void input_int(int *value, const char *mes, const char *error, int_validator_func validator) {
    int isDataValid;

    do {
        printf(mes);

        int scanResult = scanf("%d", value);

        if (scanResult != 1) {
            clearInputBuffer();
            isDataValid = 0;
        } else if (!isInputValid()) {
            isDataValid = 0;
        } else {
            isDataValid = validator(*value);
        }

        if (!isDataValid) {
            printf(error);
            printf("\n");
        }
    } while (!isDataValid);
}

void input_double(double *value, const char *mes, const char *error, double_validator_func validator) {
    int isDataValid;

    do {
        printf(mes);

        int scanResult = scanf("%lf", value);

        if (scanResult != 1) {
            clearInputBuffer();
            isDataValid = 0;
        } else if (!isInputValid()) {
            isDataValid = 0;
        } else {
            isDataValid = validator(*value);
        }

        if (!isDataValid) {
            printf(error);
            printf("\n");
        }
    } while (!isDataValid);
}

void input_char(char *value, const char *mes, const char *error, char_validator_func validator) {
    int isDataValid;

    do {
        printf(mes);

        int scanResult = scanf("%c", value);

        if (scanResult != 1) {
            clearInputBuffer();
            isDataValid = 0;
        } else if (!isInputValid()) {
            isDataValid = 0;
        } else {
            isDataValid = validator(*value);
        }

        if (!isDataValid) {
            printf(error);
            printf("\n");
        }
    } while (!isDataValid);
}
