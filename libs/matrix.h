#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

#define MAX_SIZE 6
#define EPSILON 1e-10

// Структура для хранения матрицы
typedef struct {
    double data[MAX_SIZE][MAX_SIZE];
    int rows;
    int cols;
} Matrix;

// Создание и инициализация
Matrix create_matrix(int rows, int cols); // создание матрицы
Matrix input_matrix(void); // ввод матрицы
Matrix copy_matrix(Matrix m); // копирование матрицы

// Основные операции
Matrix add_matrices(Matrix a, Matrix b); // сложение матриц
Matrix subtract_matrices(Matrix a, Matrix b); // вычитание матриц
Matrix multiply_matrices(Matrix a, Matrix b); // умножение матриц
Matrix scalar_multiply(Matrix m, double scalar); // скалярное умножение
Matrix transpose_matrix(Matrix m); // транспозиция матрицы

// Продвинутые операции
Matrix inverse_matrix(Matrix m); // инвертирование матрицы
double determinant(Matrix m); // детерминант матрицы

// Вспомогательные функции
void print_matrix(Matrix m); // вывод матрицы
bool is_square_matrix(Matrix m); // является ли матрица квадратной
bool is_invertible(Matrix m); // проверка на инверсию
Matrix identity_matrix(int n); // создание единичной матрицы

// Матричные преобразования
Matrix matrix_of_minors(Matrix m); // создание матрицы миноров
Matrix matrix_of_algebraic_additions(Matrix m); // создание матрицы алгебраических дополнений
Matrix stepwise(Matrix m); // приведение к ступенчатому виду

#endif // MATRIX_H