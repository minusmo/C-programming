#include <stdio.h>
#include <stdlib.h>

/*
링크드 큐는 
추상 데이터 타입인 큐를 링크드 리스트의 구조로 구현한 것이다.
링크드 스택과 유사하며,
링크드 스택이 top 포인터만 가지는 것과 달리
링크드 큐는 front, rear 포인터를 가진다.
*/

#define MAX_QUEUES 10
typedef queue* queue_pointer;

typedef struct {
    int key;
} element;

typedef struct
{
    element item;
    queue_pointer link;
} queue;

queue_pointer front[MAX_QUEUES], rear[MAX_QUEUES];
/*
initial condition for the queues:
front[i] = NULL, 0 <= i <= MAX_QUEUES
*/

void add(queue_pointer* front, queue_pointer* rear, element item);
element delete(queue_pointer* front);

void main() {

}

void add(queue_pointer* front, queue_pointer* rear, element item) {
    queue_pointer temp = (queue_pointer)malloc(sizeof(queue));

    if (IS_FULL(temp)) {
        printf(stderr, "The memory is full\n");
        exit(1);
    }
    temp->item = item;
    temp->link = NULL;
    
    if (*front) {
        (*rear)->link = temp;
    }
    else {
        *front = temp;
    }
    *rear = temp;
}

element delete(queue_pointer* front) {
    queue_pointer temp = *front;
    element item;

    if (IS_EMPTY(*front)) {
        printf(stderr, "The queue is empty\n");
        exit(1);
    }
    item = temp->item;
    *front = temp->link;
    free(temp);
    return item;
}