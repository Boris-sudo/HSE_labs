#include <stdio.h>
#include <ctype.h>
#define forn(i,n) for(int i=0;i<n;++i)
#define fornn(i,l,r) for(int i=l;i<=r;++i)
#define ford(i,n) for(int i=n-1;i>=0;--i)
#define sz(a) sizeof(a) / sizeof(a[0])
const double eps = 1e-12;

/**
 * Enum для понимания какой тип данных вводится
 */
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE
} variable_type_t;


/**
 * Union с int и double для ввода // менять только одно значение
 */
typedef union {
    int int_value;
    double double_value;
} variable_numeric_t;

/**
 * Структура для сложного ввода
 */
typedef struct {
    variable_type_t type;
    variable_numeric_t number;
} generic_input;

/**
 * Тип указателя на функцию
 */
typedef int (*validator_func)(const generic_input);

/**
 * Абсолютное значение числа
 * @param n число
 * @return модуль `n`
 */
double abs(double n) {
    return (n > 0) ? n : -n;
}

/**
 * Макрос для минимума из двух чисел
 * @param a первое число
 * @param b второе число
 */
#define min(a, b) (a < b ? a : b)

/**
 * Макрос для максимума из двух чисел
 * @param a первое число
 * @param b второе число
 */
#define max(a,b) (a < b ? b : a)

/**
 * Проверяет что `c` - символ пробела
 * @param c вводимый символ
 * @return 1 если `c` это символ пробела, 0 иначе
 */
int isWhiteSpace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

/**
 * Проверяет что дальше в строке ничего не находится
 * @return 1 если ввод корректер, 0 иначе
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
 * Функция очищение буффера
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Ввод переменной int/double с защитой от дурака
 * @param input ссылка на вводимую переменную
 * @param mes текст, который будет отображаться перед вводом
 * @param error текст, который будет показываться, когда пользователь совершает ошибку во время ввода
 * @param validator функция валидации вводимой переменной
 */
void input(generic_input *input, const char *mes, const char *error, validator_func validator) {
    int isDataValid;
    int scanResult;

    do {
        printf(mes);

        if (input->type == TYPE_INT)
            scanResult = scanf("%d", &input->number.int_value);
        else
            scanResult = scanf("%lf", &input->number.double_value);

        if (scanResult != 1) {
            clearInputBuffer();
            isDataValid = 0;
        } else if (!isInputValid()) {
            isDataValid = 0;
        } else {
            isDataValid = validator(*input);
        }

        if (!isDataValid) {
            printf(error);
            printf("\n");
        }
    } while (!isDataValid);
}

/**
 * Макрос для введения переменной типа int
 * @param var вводимая переменная
 * @param prompt текст, который будет показываться перед вводом
 * @param error текст ошибки
 * @param validator функция валидации
 */
#define INPUT_INT(var, prompt, error, validator) do { \
    generic_input res = { .type = TYPE_INT, .number = {.int_value = 0, .double_value = 0} }; \
    input(&res, prompt, error, validator); \
    var = res.number.int_value; \
} while(0)

/**
 * Макрос для введения переменной типа double
 * @param var вводимая переменная
 * @param prompt текст, который будет показываться перед вводом
 * @param error текст ошибки
 * @param validator функция валидации
 */
#define INPUT_DOUBLE(var, prompt, error, validator) do { \
    generic_input res = { .type = TYPE_DOUBLE, .number = {.int_value = 0, .double_value = 0} }; \
    input(&res, prompt, error, validator); \
    var = res.number.double_value; \
} while(0)

/**
 * Макрос для вывода массима, чтобы независеть от типа данных
 * @param arr массив, который должен быть выведен
 */
#define print_array(arr) do { \
    int size = sizeof(arr) / sizeof(arr[0]); \
    printf("Введенный массив: "); \
    forn(i, size) { \
        printf("%lf ", arr[i]); \
    } \
    printf("\n"); \
} while (0)

int main() {
    // ввод длинны массива
    int array_length;
    int (*array_length_validator)(generic_input) = ( {
        int func(generic_input x) { return x.number.int_value > 0 && x.number.int_value < 100000; };
        func;
    });
    INPUT_INT(array_length, "Введите длину массива от 1 до 100'000: ", "Введите целое число",
              array_length_validator);

    // блок для ввода самого массива
    double arr[array_length];
    int (*array_validator)(generic_input) = ( {
        int func(generic_input x)
        {
            return x.number.double_value > -10000 && x.number.double_value < 10000;
        };
        func;
    });
    forn(i, array_length)
        INPUT_DOUBLE(arr[i], "Введите значение элемента массива от -10'000 до 10'000: ", "Введите вещественное число",
                 array_validator);
    print_array(arr);

    // Ввод значение X
    double X;
    int (*X_validator)(generic_input) = ( {
        int func(generic_input x)
        {
            return x.number.double_value > -10000 && x.number.double_value < 10000;
        };
        func;
    });
    INPUT_DOUBLE(X, "Введите вещественное число от -10'000 до 10'000: ", "Введите вещественное число", X_validator);

    // решение первого задания
    double result = 1e9;
    int size = sizeof(arr) / sizeof(arr[0]);
    forn(i, size) if (arr[i] > X && result > arr[i]) result = arr[i];
    if (abs(result - 1e9) < eps)
        printf("В списке нет элементов больших X\n");
    else
        printf("Результатам на первый вопрос является: %lf\n", result);

    // решение второго задания
    int l = -1, r = 0;
    forn(i, size) {
        int arr_int = arr[i];
        if (arr_int % 2 == 0 && abs(arr_int - arr[i]) < eps)
            l = min((l == -1 ? i : l), i);
        if (arr[i] < arr[r] || abs(arr[i] - arr[r]) < eps)
            r = max(r, i);
    }
    if (l == -1)
        printf("В массиве отсутствуют четные числа, массив некорректен для второй задачи\n");
    else if (r - l <= 1)
        printf("Между минимальным правым и первым четным нет чисел, массив некорректен для второй задачи\n");
    else {
        double ans = 0;
        int count = 0;
        fornn(i, l+1, r-1) {
            ans += arr[i];
            count++;
        }
        ans /= count;
        printf("Ответ на вторую задачу: %lf\n", ans);
    }

    return 0;
}
