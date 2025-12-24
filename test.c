#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

signed main() {
    // creating matrix
    int rows = 10;
    int cols = 5;
    int **m = (int **) malloc(rows * sizeof(int *));

    if (m == NULL) {
        exit(1);
    }

    for (int i = 0; i < rows; ++i) {
        m[i] = (int *) malloc(cols * sizeof(int));
        if (m[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(m[j]);
            }
            free(m);
            exit(1);
        }
    }


    // free matrix
    for (int i = 0; i < rows; ++i) {
        free(m[i]);
    }
    free(m);

    return 0;
}
