#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

// Глобальные переменные для параметров многоугольника
int n = 5; // Количество сторон (по умолчанию 5)
float side_length = 0.3; // Длина стороны (по умолчанию 0.3)
float rotation_angle = 45.0; // Угол поворота в градусах (по умолчанию 45°)

// Функция для вычисления радиуса описанной окружности
float calculate_circumradius(float side, int sides) {
    return side / (2 * sin(M_PI / sides));
}

// Функция для вычисления апофемы (радиуса вписанной окружности)
float calculate_apothem(float side, int sides) {
    return side / (2 * tan(M_PI / sides));
}

// Функция отрисовки правильного многоугольника
void draw_polygon(float cx, float cy, float side, int sides, float rotate_angle, int is_rotated) {
    float radius = calculate_circumradius(side, sides);
    float apothem = calculate_apothem(side, sides);

    // Угол между вершинами в радианах
    float angle_step = 2 * M_PI / sides;

    // Если требуется поворот, применяем трансформации
    if (is_rotated) {
        glPushMatrix();
        // Перемещаем в точку центра нижней грани
        glTranslatef(cx, cy - apothem, 0.0);
        // Поворачиваем на заданный угол
        glRotatef(rotate_angle, 0.0, 0.0, 1.0);
        // Возвращаем обратно
        glTranslatef(-cx, -(cy - apothem), 0.0);
    }

    // Начинаем рисовать линию
    glBegin(GL_LINE_LOOP);

    // Вычисляем и рисуем вершины
    for (int i = 0; i < sides; i++) {
        // Начинаем с вершины внизу (для удобства поворота)
        float angle = -M_PI/2 + angle_step * i;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();

    if (is_rotated) {
        glPopMatrix();
    }
}

// Функция отрисовки сцены
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Устанавливаем цвет для обычного многоугольника (синий)
    glColor3f(0.0, 0.0, 1.0);
    draw_polygon(0.0, 0.0, side_length, n, 0.0, 0);

    // Устанавливаем цвет для повернутого многоугольника (красный)
    glColor3f(1.0, 0.0, 0.0);
    draw_polygon(0.0, 0.0, side_length, n, rotation_angle, 1);

    glFlush();
}

// Функция инициализации OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Белый фон
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Устанавливаем ортографическую проекцию
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// Функция для запроса данных у пользователя
void get_user_input() {
    printf("Введите количество сторон n-угольника (n < 15): ");
    scanf("%d", &n);

    if (n < 3 || n >= 15) {
        printf("Некорректное значение. Установлено значение по умолчанию (n=5).\n");
        n = 5;
    }

    printf("Введите длину стороны (рекомендуется от 0.1 до 0.5): ");
    scanf("%f", &side_length);

    if (side_length <= 0) {
        printf("Некорректное значение. Установлено значение по умолчанию (0.3).\n");
        side_length = 0.3;
    }

    printf("Введите угол поворота в градусах: ");
    scanf("%f", &rotation_angle);
}

int main(int argc, char** argv) {
    // Запрашиваем данные у пользователя
    get_user_input();

    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Правильные n-угольники");

    // Регистрация callback-функций
    init();
    glutDisplayFunc(display);

    // Вывод инструкции
    printf("\n=== Инструкция ===\n");
    printf("Синий цвет: исходный многоугольник\n");
    printf("Красный цвет: повернутый многоугольник\n");
    printf("Центр поворота: середина нижней грани\n");
    printf("Направление поворота: против часовой стрелки\n");
    printf("==================\n\n");

    // Запуск главного цикла GLUT
    glutMainLoop();

    return 0;
}