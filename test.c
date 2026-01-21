#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define forn(i,n) for(int i = 0; i < n; i++)

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

signed main() {
    int n = 10;
    const int size = n * 3 + (n-1);
    int arr[n + 10];
    forn(i, n + 10) arr[i] = 0;
    arr[0] = arr[1] = 1;
    forn(i, n) {
        int temp[n + 10];
        forn(j, n + 10) temp[j] = arr[j];
        forn(j, i + 1) {
            if (j == 0 || j == i) arr[j] = 1;
            else arr[j] = temp[j] + temp[j - 1];
        }

        int cnt = (i * 3 + (i-1));
        int spaces = (size - cnt) / 2;
        forn(k, spaces) printf(" ");
        forn(j,i + 1) {
            printf("%3d ", arr[j]);
        }
        printf("\n");
    }

    return 0;
}
