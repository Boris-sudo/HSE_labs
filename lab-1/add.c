#include <stdio.h>

double sum(double a, double b) {

}

double sub(double a, double b) {

}

double mul(double a, double b) {

}

double div(double a, double b) {

}

double pow(double x, int n) {

}

double root(double x, int n) {

}

double log(double x) {

}

double exp(double x) {

}

int round(double x) {

}

int main() {
    int a, b, c;
    printf("Введите значение для переменной a: ");
    scanf("%d", &a);
    printf("Введите значение для переменной b: ");
    scanf("%d", &b);
    printf("Введите значение для переменной c: ");
    scanf("%d", &c);

    double r1 = mul(b,a);
    double r2 = div(r1, c);
    double r3 = log(r2);
    double r4 = div(a, r3);
    double r5 = exp(b);
    double r6 = div(r5, c);
    double r7 = pow(r6, 7);
    double r8 = root(r7, 3);
    double r9 = mul(r4, r8);
    double res = round(r9);

    printf("Результат: %lf", res);

    return 0;
}
