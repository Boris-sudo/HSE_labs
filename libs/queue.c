#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}

void push(Queue *q, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q))
        q->front = q->rear = newNode;
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int pop(Queue *q) {
    if (isEmpty(q)) {
        printf("Очередь пуста\n");
        return -1;
    }

    Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int front(Queue *q) {
    if (isEmpty(q)) {
        printf("Очередь пуста\n");
        return -1;
    }
    return q->front->data;
}

void printQueue(Queue *q) {
    Node *current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

int queueSize(Queue *q) {
    int count = 0;
    Node *current = q->front;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void freeQueue(Queue *q) {
    while (!isEmpty(q)) {
        pop(q);
    }
}
