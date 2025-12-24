#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Инициализация очереди
void initQueue(Queue* q);

// Проверка на пустоту очереди
int isEmpty(Queue* q);

// Добавление элемента в очередь
void push(Queue* q, int value);

// Удаление и получение элемента из очереди
int pop(Queue* q);

// Получение первого элемента без удаления
int front(Queue* q);

// Печать всех элементов очереди
void printQueue(Queue* q);

// Получение размера очереди
int queueSize(Queue* q);

// Освобождение памяти, занятой очередью
void freeQueue(Queue* q);

#endif // QUEUE_H