#include <stdio.h>
#include <stdlib.h>
/*
링크드 리스트를 이용해서 
스택을 구성할 수 있다.
이렇게 하면, 동적으로 새로운 노드를 추가, 제거하기가 쉬우며,
스택이라는 자료구조의 특성을 더 잘 반영하는 자료구조가 된다.
링크드 스택의 추상 인터페이스는 
배열을 이용한 스택과 비슷하며, 
세부적 구현은 링크드 리스트의 삽입, 삭제와 같다.
*/

#define MAX_STACKS 10

typedef struct {
    int key;
} element;

typedef stack* stack_pointer;
typedef struct {
    element item;
    stack_pointer link;
} stack;

stack_pointer top[MAX_STACKS];

/*
initial condition for stack:
top[i] = NULL, 0 <= i <= MAX_STACKS

boundary condition of stack:
top[i] = NULL, if the stack is empty
and
IS_FULL(temp) if the memory is full
*/

void add(stack_pointer* top, element item);
element delete(stack_pointer* top);

void add(stack_pointer* top, element item) {
    stack_pointer temp = (stack_pointer)malloc(sizeof(stack));

    if (IS_FULL(temp)) {
        printf(stderr, "The memory is full\n");
        exit(1);
    }
    temp->item = item;
    temp->link = *top;
    *top = temp;
}

element delete(stack_pointer* top) {
    stack_pointer temp = *top;
    element item;
    
    if (IS_EMPTY(temp)) {
        printf(stderr, "The stack is empty\n");
        exit(1);
    }
    item = temp->item;
    *top = temp->link;
    free(temp);
    return item;
}

void main() {
    
}