#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int front, rear, size;
    int capacity;
    int* array;
} Queue;

Queue* createQ(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;

    queue->rear = capacity - 1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enQ(Queue* queue, int item) {
    if (isFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size +1;
    printf("%d enqueued to queue\d", item);
    return;
}

int deQ(Queue* queue) {
    if (isEmpty(queue)) {
        return INT_MIN;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int front(Queue* queue) {
    if (isEmpty(queue)) {
        return INT_MIN;
    }
    return queue->array[queue->front];
}

int rear(Queue* queue) {
    if (isEmpty(queue)) {
        return INT_MIN;
    }
    return queue->array[queue->rear];
}

void main() {
    Queue* queue = createQ(100);
    enQ(queue, 10);
    return;
}