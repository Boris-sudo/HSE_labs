#include "../libs/matrix.h"
#include <stdio.h>

#include "../libs/input.h"

void print_menu() {
    printf("\n");
    printf("=== МЕНЮ ОПЕРАЦИЙ С МАТРИЦАМИ ===\n");
    printf("1. Сложение матриц\n");
    printf("2. Вычитание матриц\n");
    printf("3. Умножение матриц\n");
    printf("4. Нахождение обратной матрицы\n");
    printf("5. Приведение матрицы к главному ступенчатому виду\n");
    printf("6. Вычисление определителя\n");
    printf("7. Транспонирование матрицы\n");
    printf("8. Выход\n");
}

int choice_validator(int value) { return value >= 1 && value <= 8; }

int main() {
    int choice;

    printf("Программа для операций с матрицами (максимум 6x6)\n");

    do {
        print_menu();
        input_int(&choice, "Выберите операцию: ", "Введите целое число от 1 до 8", choice_validator);

        switch (choice) {
            case 1: {
                printf("\n=== СЛОЖЕНИЕ МАТРИЦ ===\n");
                printf("Введите первую матрицу:\n");
                Matrix A = input_matrix();
                printf("Введите вторую матрицу:\n");
                Matrix B = input_matrix();

                Matrix sum = add_matrices(A, B);
                if (sum.rows > 0) {
                    printf("\nРезультат сложения:\n");
                    print_matrix(sum);
                }
                break;
            }

            case 2: {
                printf("\n=== ВЫЧИТАНИЕ МАТРИЦ ===\n");
                printf("Введите первую матрицу:\n");
                Matrix A = input_matrix();
                printf("Введите вторую матрицу:\n");
                Matrix B = input_matrix();

                Matrix diff = subtract_matrices(A, B);
                if (diff.rows > 0) {
                    printf("\nРезультат вычитания:\n");
                    print_matrix(diff);
                }
                break;
            }

            case 3: {
                printf("\n=== УМНОЖЕНИЕ МАТРИЦ ===\n");
                printf("Введите первую матрицу:\n");
                Matrix A = input_matrix();
                printf("Введите вторую матрицу:\n");
                Matrix B = input_matrix();

                Matrix product = multiply_matrices(A, B);
                if (product.rows > 0) {
                    printf("\nРезультат умножения:\n");
                    print_matrix(product);
                }
                break;
            }

            case 4: {
                printf("\n=== НАХОЖДЕНИЕ ОБРАТНОЙ МАТРИЦЫ ===\n");
                printf("Введите квадратную матрицу:\n");
                Matrix A = input_matrix();

                Matrix inv = inverse_matrix(A);
                if (inv.rows > 0) {
                    printf("\nОбратная матрица:\n");
                    print_matrix(inv);
                }
                break;
            }

            case 5: {
                printf("\n=== ПРИВЕДЕНИЕ К ГЛАВНОМУ СТУПЕНЧАТОМУ ВИДУ ===\n");
                printf("Введите матрицу:\n");
                Matrix A = input_matrix();

                printf("\nИсходная матрица:\n");
                print_matrix(A);

                printf("\nГлавный ступенчатый вид:\n");
                Matrix echelon = stepwise(A);
                print_matrix(echelon);
                break;
            }

            case 6: {
                printf("\n=== ВЫЧИСЛЕНИЕ ОПРЕДЕЛИТЕЛЯ ===\n");
                printf("Введите квадратную матрицу:\n");
                Matrix A = input_matrix();

                double det = determinant(A);
                printf("\nОпределитель матрицы: %.4lf\n", det);
                break;
            }

            case 7: {
                printf("\n=== ТРАНСПОНИРОВАНИЕ МАТРИЦЫ ===\n");
                printf("Введите матрицу:\n");
                Matrix A = input_matrix();

                Matrix transposed = transpose_matrix(A);
                printf("\nТранспонированная матрица:\n");
                print_matrix(transposed);
                break;
            }

            case 8: {
                printf("Выход из программы.\n");
                break;
            }

            default: {
                printf("Неверный выбор! Попробуйте снова.\n");
                break;
            }
        }
    } while (choice != 8);

    return 0;
}
