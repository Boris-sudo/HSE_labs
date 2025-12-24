#include "matrix.h"
#include "utils.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Matrix create_matrix(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    forn(i, rows)
        forn(j, cols) m.data[i][j] = 0.0;
    return m;
}

int cols_rows_validator(int value) {
    return value >= 1 && value <= MAX_SIZE;
}

int matrix_element_validator(double value) {
    return value >= -100 && value <= 100;
}

Matrix input_matrix(void) {
    int rows, cols;
    input_int(&rows, "Введите количество строк: ", "Введите целое число от 0 до 6", cols_rows_validator);
    input_int(&cols, "Введите количество столбцов: ", "Введите целое число от 0 до 6", cols_rows_validator);

    Matrix m = create_matrix(rows, cols);
    forn(i, rows)
        forn(j, cols) {
            input_double(&m.data[i][j], "Введите элемент матрицы: ", "Введите число от -100 до 100",
                         matrix_element_validator);
        }

    return m;
}

void print_matrix(Matrix m) {
    forn(i, m.cols) {
        forn(j, m.rows) {
            if (fabs(m.data[i][j]) < EPSILON)
                printf("%10.4lf ", 0.0);
            else
                printf("%10.4lf ", m.data[i][j]);
        }
        printf("\n");
    }
}

Matrix copy_matrix(Matrix m) {
    Matrix copy = create_matrix(m.rows, m.cols);
    forn(i, m.rows)
        forn(j, m.cols) copy.data[i][j] = m.data[i][j];
    return copy;
}

bool is_square_matrix(Matrix m) {
    return m.rows == m.cols;
}

bool is_invertible(Matrix m) {
    if (!is_square_matrix(m)) return false;
    return fabs(determinant(m)) > EPSILON;
}

Matrix identity_matrix(int n) {
    Matrix m = create_matrix(n, n);
    forn(i, n) m.data[i][i] = 1.0;
    return m;
}

Matrix add_matrices(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Матрицы должны быть одинакового размера!");
        return create_matrix(0, 0);
    }

    Matrix m = create_matrix(a.rows, b.cols);
    forn(i, m.cols)
        forn(j, m.rows) m.data[i][j] = a.data[i][j] + b.data[i][j];
    return m;
}

Matrix scalar_multiply(Matrix m, double scalar) {
    Matrix t = create_matrix(m.rows, m.cols);
    forn(i, m.rows)
        forn(j, m.cols) t.data[i][j] = scalar * m.data[i][j];
    return t;
}

Matrix subtract_matrices(Matrix a, Matrix b) {
    scalar_multiply(b, -1.0);
    return add_matrices(a, b);
}

Matrix multiply_matrices(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        printf("Матрицы не могут быть перемножены из-за несовпадения размерностей!");
        return create_matrix(0, 0);
    }

    Matrix m = create_matrix(a.rows, b.cols);
    forn(i, a.rows)
        forn(j, b.cols)
            forn(k, a.cols)
                m.data[i][j] += a.data[i][k] * b.data[k][j];
    return m;
}

Matrix transpose_matrix(Matrix m) {
    Matrix t = create_matrix(m.cols, m.rows);
    forn(i, m.rows)
        forn(j, m.cols) t.data[j][i] = m.data[i][j];
    return t;
}

double determinant(Matrix m) {
    if (!is_square_matrix(m)) {
        printf("Детерминант может считаться только у квадратных матриц!");
        return 0.0;
    }

    int n = m.rows;
    if (n == 1) return m.data[0][0];
    if (n == 2) return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];

    double det = 0.0;
    forn(p, n) {
        Matrix submatrix = create_matrix(n - 1, n - 1);
        forn(i, n - 1) {
            forn(j, n) {
                if (j == p) continue;
                submatrix.data[i][j + (j >= p ? 1 : 0)] = m.data[i + 1][j];
            }
        }
        det += determinant(submatrix) * m.data[1][p];
    }

    return det;
}

Matrix matrix_of_minors(Matrix m) {
    if (!is_square_matrix(m)) {
        printf("Матрица должна быть квадратной!");
        return create_matrix(0, 0);
    }

    int n = m.rows;
    Matrix t = create_matrix(n, n);
    forn(i, n)
        forn(j, n) {
            Matrix minor = create_matrix(n - 1, n - 1);
            int x = 0;
            forn(i1, n) {
                if (i1 == i) continue;
                int y = 0;
                forn(j1, n) {
                    if (j1 == j) continue;
                    minor.data[x][y] = m.data[i1][j1];
                    y++;
                }
                x += 1;
            }
            t.data[i][j] = determinant(minor);
        }
    return t;
}

Matrix matrix_of_algebraic_additions(Matrix m) {
    if (!is_square_matrix(m)) {
        printf("Матрица должна быть квадратной!");
        return create_matrix(0, 0);
    }
    int n = m.rows;
    Matrix minors = matrix_of_minors(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            minors.data[i][j] *= sign;
        }
    }
    return minors;
}

Matrix inverse_matrix(Matrix m) {
    if (!is_square_matrix(m)) {
        printf("Матрица должна быть квадратной, чтобы ее инвертировать");
        return create_matrix(0, 0);
    }

    double det = determinant(m);

    if (fabs(det) < EPSILON) {
        printf("Матрица не может быть инвертирована");
        return create_matrix(0, 0);
    }

    if (m.cols == 1) {
        Matrix t = create_matrix(1, 1);
        t.data[0][0] = 1.0 / m.data[0][0];
        return t;
    }

    Matrix t = matrix_of_algebraic_additions(m);
    t = transpose_matrix(t);
    t = scalar_multiply(t, 1.0 / det);

    return t;
}

Matrix stepwise(Matrix m) {
    Matrix t = copy_matrix(m);
    int lead = 0;

    for (int r = 0; r < m.rows; r++) {
        if (lead >= m.cols) break;

        int i = r;
        while (fabs(t.data[i][lead]) < EPSILON) {
            i++;
            if (i == m.rows) {
                i = r;
                lead++;
                if (lead == m.cols) return t;
            }
        }

        if (i != r) {
            for (int j = 0; j < m.cols; j++) {
                double temp = t.data[r][j];
                t.data[r][j] = t.data[i][j];
                t.data[i][j] = temp;
            }
        }

        double div = t.data[r][lead];
        if (fabs(div) > EPSILON) {
            for (int j = 0; j < m.cols; j++) {
                t.data[r][j] /= div;
            }
        }

        for (int i = r + 1; i < m.rows; i++) {
            double factor = t.data[i][lead];
            if (fabs(factor) > EPSILON) {
                for (int j = 0; j < m.cols; j++) {
                    t.data[i][j] -= factor * t.data[r][j];
                }
            }
        }
        lead++;
    }

    return t;
}
