#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../libs/utils.h"

#define MAX_N 5
#define MAX_K 6
#define EPS 1e-6

// Reading entire file into a dynamically allocated buffer
char* read_whole_file(const char* filename, long* size) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*)malloc(*size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t read = fread(buffer, 1, *size, f);
    fclose(f);

    if (read != *size) {
        free(buffer);
        return NULL;
    }
    buffer[*size] = '\0';
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <matrix_file> <solution_file>\n", argv[0]);
        return 1;
    }

    long size1, size2;
    char* mat_data = read_whole_file(argv[1], &size1);
    char* sol_data = read_whole_file(argv[2], &size2);
    char* convert_errors;

    if (!mat_data || !sol_data) {
        printf("Error opening or reading files.\n");
        free(mat_data);
        free(sol_data);
        return 1;
    }

    // Parse first file (matrices sizes)
    char* token = strtok(mat_data, " \t\n\r");
    if (!token) {
        printf("Error: matrix file is empty.\n");
        free(mat_data);
        free(sol_data);
        return 1;
    }
    int n = strtol(token, &convert_errors, 10);

    token = strtok(NULL, " \t\n\r");
    if (!token) {
        printf("Error: insufficient data for k.\n");
        free(mat_data);
        free(sol_data);
        return 1;
    }
    int k = strtol(token, &convert_errors, 10);

    if (n <= 0 || n > MAX_N || k <= 0 || k > MAX_K || strlen(convert_errors) > 0) {
        printf("Invalid values: n = %d, k = %d (allowed: n 1..%d, k 1..%d)\n",
               n, k, MAX_N, MAX_K);
        free(mat_data);
        free(sol_data);
        return 1;
    }

    // Arrays to store data
    double matrix[MAX_K][MAX_N][MAX_N + 1];
    double solutions[MAX_K][MAX_N];

    // Read matrices from the same buffer
    forn(sys, k) {
        forn(row, n) {
            forn(col, n+1) {
                token = strtok(NULL, " \t\n\r");
                convert_errors = NULL;
                matrix[sys][row][col] = strtod(token, &convert_errors);
                if (!token || convert_errors) {
                    printf("Error: insufficient data in matrix file (system %d).\n", sys + 1);
                    free(mat_data);
                    free(sol_data);
                    return 1;
                }
            }
        }
    }
    free(mat_data); // no longer needed

    // Reading solutions from the second buffer
    token = strtok(sol_data, " \t\n\r");
    forn(sys, k) {
        forn(comp, n) {
            convert_errors = NULL;
            solutions[sys][comp] = strtod(token, &convert_errors);
            token = strtok(NULL, " \t\n\r");
            if (!token || convert_errors) {
                printf("Error: insufficient data in solution file.\n");
                free(sol_data);
                return 1;
            }
        }
    }
    free(sol_data);

    // Output and verification for each system
    forn(sys, k) {
        printf("System %d:\n", sys + 1);
        // Print equations
        forn(row, n) {
            printf("  %.3f * x1", matrix[sys][row][0]);
            fornn(col, 1, n-1)
                printf(" + %.3f * x%d", matrix[sys][row][col], col + 1);
            printf(" = %.3f\n", matrix[sys][row][n]);
        }

        // Print solution
        printf("Solution:\n");
        forn(comp, n)
            printf("  x%d = %.3f\n", comp + 1, solutions[sys][comp]);

        // Verify by substitution
        int ok = 1;
        forn(row, n) {
            double sum = 0.0;
            forn(col, n)
                sum += matrix[sys][row][col] * solutions[sys][col];
            if (fabs(sum - matrix[sys][row][n]) > EPS) {
                ok = 0;
                break;
            }
        }

        if (!ok) {
            printf("  ERROR: the vector is not a solution!\n");
        }
        printf("\n");
    }

    return 0;
}