/*
큐는 추상 데이터 타입으로,
정렬된 리스트이고 FIFO의 구조를 가진다.
모든 삽입이 한쪽 끝에서 일어나고,
모든 삭제가 반대 쪽끝에서 일어난다.
큐는 다음의 함수를 구현한다.
CreateQueue(max_queue_size)
IsFullQ(queue, max_queue_size)
AddQ(queue, item)
IsEmptyQ(queue)
DeleteQ(queue)
*/
#include <stdio.h>

#define MAX_QUEUE_SIZE 100

typedef struct
{
    int key;
} Element;

// 동적할당 필요
Element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

typedef Element* Queue;
typedef int boolean;

boolean isEmptyQ(int* rear, int* front);
void addQ(int* rear, Element item);
Element deleteQ(int* front, int rear);
boolean isFullQ(int* rear, int max_queue_size);

void addQ(int* rear, Element item) {
    if (*rear == MAX_QUEUE_SIZE) {
        // raise error
        queue_full();
        return;
    }
    queue[++*rear];
}

Element deleteQ(int* front, int rear) {
    if (*front == rear) {
        // return error key
        return queue_empty();
    }
    return queue[++*front];
}

boolean isEmptyQ(int* rear, int* front) {
    if (*rear == *front) {
        return 0;
    }
    else {
        return 1;
    }
}

boolean isFullQ(int* rear, int max_queue_size) {
    if (*rear == max_queue_size - 1) {
        return 0;
    }
    else {
        return 1;
    }
}