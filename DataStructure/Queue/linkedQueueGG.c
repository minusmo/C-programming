#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct 
{
    int key;
    qNode* next;
} qNode;

typedef struct {
    qNode* front;
    qNode* rear;
} Queue;

qNode* newNode(int key) {
    qNode* temp = (qNode*)malloc(sizeof(qNode));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

Queue* createQ() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enQ(Queue* queue, int key) {
    qNode* temp = newNode(key);
    if (queue->rear == NULL) {
        queue->front = temp;
        queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
    return;
}

int deQ(Queue* queue) {
    if (queue->front == NULL) {
        return INT_MIN;
    }
    qNode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return temp->key;
}