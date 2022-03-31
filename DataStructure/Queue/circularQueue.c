#include <stdio.h>
/*
원형 큐는 큐의 일종으로써,
정해진 메모리 공간에 순환적으로 데이터를 추가, 삭제할 수 있는 자료구조이다.

*/

#define MAX_QUEUE_SIZE 6
typedef struct
{
    int key;
} element;

element* createQ(int max_queue_size);
void addQ(element* qPtr, int front, int* rear, element item);
element deleteQ(element* qPtr, int* front, int rear);
void queue_full(int* rear);
element queue_empty();

void main() {

}

element* createQ(int max_queue_size) {
    element* qPtr = (element*)malloc(max_queue_size * sizeof(element));
    return qPtr;
}

void addQ(element* qPtr, int front, int* rear, element item) {
    *rear = (*rear+1) % MAX_QUEUE_SIZE;
    if (front == *rear) {
        queue_full(rear); //reset rear and print error
        return;
    }
    qPtr[*rear] = item;
}

element deleteQ(element* qPtr, int* front, int rear) {
    element item;
    if (*front == rear) {
        return queue_empty(); //returns an error key
    }
    *front = (*front+1) % MAX_QUEUE_SIZE;
    return qPtr[*front];
}

void queue_full(int* rear) {
    if (*rear == 0) {
        *rear = MAX_QUEUE_SIZE - 1;
    }
    else {
        *rear = *rear - 1;
    }
    printf("queue is full");
}

element queue_empty() {
    element errorKey;
    errorKey.key = -1;
    return errorKey;
}