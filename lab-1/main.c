#include <stdio.h> // добавляем дефолтную библиотеку для C
#define forn(i,n) for(int i=0;i<n;++i)
#define fornn(i,l,r) for(int i=l;i<=r;++i)
#define ford(i,n) for(int i=n-1;i>=0;--i)

/**
 * enum для понимания какой тип данных вводится
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
 * Указатель на функцию
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
    inputHSE_INPUT_H(&res, prompt, error, validator); \
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
 * Функция которая считает примерное значение `ln(1+x)`, по точности
 * @param x переменная, от который будет считаться логарифм
 * @return примерное значение `ln(1+x)`
 */
double accuracyCalculation(double x) {
    double res = 0;
    double accuracy;

    // ввод точности подсчета
    int (*accuracy_validator)(generic_input) = ( {
        int func(generic_input x)
        {
            return x.number.double_value > 0 && x.number.double_value < 1;
        };
        func;
    });
    INPUT_DOUBLE(accuracy, "Введите точность вычислений: ", "Ошибка, введите число большее 0 и меньшее 1",
                 accuracy_validator);

    // подсчет логарифма
    int index = 1;
    double pow = x;
    const int max_iterations = 10000;
    do {
        double current = pow / index;
        if (abs(current) < accuracy) break; // если текущее значение меньше точности, то выходим из цикла
        if (index >= max_iterations) {
            // если количество итераций больше максимального значения, то выходим из цикла
            printf("Слишком много итераций, завершаем работу программы");
            break;
        }
        res += ((index % 2 == 1) ? 1 : -1) * current;
        index++;
        pow *= x;
    } while (1);

    return res;
}

/**
 * Функция которая считает примерное значение `ln(1+x)`, по количеству итераций
 * @param x переменная, от который будет считаться логарифм
 * @return примерное значение `ln(1+x)`
 */
double iterationsCalculation(double x) {
    double res = 0;
    int count;

    // ввод количества итераций
    int (*count_validator)(generic_input) = ( {
        int func(generic_input x)
        {
            return x.number.int_value > 0 && x.number.int_value < 100000;
        };
        func;
    });
    INPUT_INT(count, "Введите количество итераций цикла: ", "Ошибка, введите целое число от 0 до 100'000",
              count_validator);

    // подсчет результата
    double pow = x;
    fornn(i, 1, count) {
        res += ((i % 2 == 1) ? 1 : -1) * pow / i;
        pow *= x;
    }

    return res;
}

int main() {
    double x;
    int choice;

    // вводим значение x
    int (*x_validator)(generic_input) = ( {
        int func(generic_input x)
        {
            return x.number.double_value >= -1 && x.number.double_value <= 1;
        };
        func;
    });
    INPUT_DOUBLE(x, "Введите число из интервала [-1, 1]: ", "Ошибка, введите число из интервала [-1, 1].", x_validator);

    // вводим способ вычисления
    int (*choice_validator)(generic_input) = ( {
        int func(generic_input x)
        {
            return x.number.int_value == 1 || x.number.int_value == 2;
        };
        func;
    });
    INPUT_INT(choice,
              "1 - подсчет с количеством итераций\n2 - подсчет по точности\nВведите 1 или 2 для выбора типа алгоритма: ",
              "Ошибка, введите число 1 или 2.", choice_validator);

    // получаем ответ и выводим его
    double ans;
    if (choice == 1)
        ans = iterationsCalculation(x);
    else
        ans = accuracyCalculation(x);
    printf("Результат работы программы: %lf", ans);

    return 0;
}