#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define forn(i,n) for(int i=0;i<n;++i)
#define fornn(i,l,r) for(int i=l;i<=r;++i)
#define ford(i,n) for(int i=n-1;i>=0;--i)
#define sz(a) sizeof(a) / sizeof(a[0])

const int MAX_SIZE = 10;

/**
 * Минимум из двух чисел
 */
int min(int a, int b) { return a < b ? a : b; }

/**
 * Максимум из двух чисел
 */
int max(int a, int b) { return a < b ? b : a; }

/**
 * Проверяет что c - символ пробела
 */
int isWhiteSpace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

/**
 * Проверяет что дальше в строке ничего не находится
 */
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

/**
 * Функция очищение буфера
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Ввод переменной int/double с защитой от дурака
 */
void input(int *input, const char *mes, const char *error) {
    int isDataValid;

    do {
        printf(mes);

        int scanResult = scanf("%d", input);

        if (scanResult != 1) {
            clearInputBuffer();
            isDataValid = 0;
        } else if (!isInputValid()) {
            isDataValid = 0;
        } else {
            isDataValid = (*input >= 2 && *input <= MAX_SIZE);
        }

        if (!isDataValid) {
            printf(error);
            printf("\n");
        }
    } while (!isDataValid);
}

/**
 * Функция рандомной генерации матрицы или ее ввода
 */
void generateMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n, int m, int input_type) {
    srand(time(NULL));
    int odd = 0;
    forn(i, n)
        forn(j, m) {
            if (input_type) {
                int isDataValid =0 ;

                do {
                    printf("Введите элемент [%d][%d] матрицы: ", i, j);

                    int scanResult = scanf("%d", &matrix[i][j]);

                    if (scanResult != 1) {
                        clearInputBuffer();
                        isDataValid = 0;
                    } else if (!isInputValid()) {
                        isDataValid = 0;
                    } else {
                        isDataValid = (matrix[i][j] >= -100 && matrix[i][j] <= 100);
                    }

                    if (!isDataValid) {
                        printf("Введите целое число от -100 до 100");
                        printf("\n");
                    }
                } while (!isDataValid);
            } else {
                matrix[i][j] = (rand() % 200) - 100;
            }
        }
}

/**
 * Функция вывода матрицы в консоль
 */
void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int n, int m) {
    printf("Исходная матрица:\n");
    forn(i, n) {
        forn(j, m) printf("%3d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

/**
 * Функция поиска максимального нечетного числа в строках, в которых на пересечении с главной диагональю стоит отрицательное число
 */
void findMaxOddInNegativeRows(int matrix[MAX_SIZE][MAX_SIZE], int n, int m) {
    int count = 0;
    forn(i, n) {
        if (matrix[i][i] >= 0) continue;
        count++;

        int res = -1e9;
        forn(j, m) if (matrix[i][j] % 2 == 1) res = max(res, matrix[i][j]);

        if (res == -1e9)
            printf("Строка %d, нет нечетных элементов\n", i + 1);
        else
            printf("Строка %d, элемент %d\n", i + 1, res);
    }
    if (count == 0) {
        printf("Нет строк, удовлетворяющих условиям задания.\n");
    }
}

/**
 * Показывает сколько надо добавить к X координате на текущем направлении обхода
 */
int getX(int dir) {
    if (dir == 0) return 0;
    if (dir == 1) return -1;
    if (dir == 2) return 0;
    return 1;
}

/**
 * Показывает сколько надо добавить к Y координате на текущем направлении обхода
 */
int getY(int dir) {
    if (dir == 0) return 1;
    if (dir == 1) return 0;
    if (dir == 2) return -1;
    return 0;
}

/**
 * Функция обхода квадратной подматрицы змейкой
 */
void printMatrixSnakePattern(int matrix[MAX_SIZE][MAX_SIZE], int k) {
    // начальные координаты маршрута
    int x = k / 2, y = k / 2;
    printf("Центр матрицы: [%d][%d] = %d\n", x, y, matrix[x][y]);

    // направление обхода
    int dir = 0;
    // цикл обхода
    forn(count, k*k) {
        // выводим значение текущей клетки и заменяем его на недостижимое
        printf("%d ", matrix[x][y]);
        matrix[x][y] = 1e9;
        // получаем следующее возможное направление и координаты
        int next_dir = (dir + 1) % 4;
        int tox = x + getX(next_dir), toy = y + getY(next_dir);

        if (matrix[tox][toy] != 1e9)
            x = tox, y = toy, dir = next_dir; // если мы не были ещё в клетке смены направления, то идем туда
        else
            x += getX(dir), y += getY(dir); // иначе продолжаем идти прямо
    }
}

int main() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int n = 10, m = 10;

    // input(&n, "Введите количество строк: ", "Число от 2 до 10");
    // input(&m, "Введите количество столбцов: ", "Число от 2 до 10");
    int k = min(m, n);

    generateMatrix(matrix, n, m, 0);
    printMatrix(matrix, n, m);

    // findMaxOddInNegativeRows(matrix, n, m);

    printMatrixSnakePattern(matrix, k);
}
