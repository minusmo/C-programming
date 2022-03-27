#include <stdio.h>
/*
스택은 추상 데이터 타입으로, LIFO의 구조를 가진다.
MAX_STACK_SIZE 를 지정한다.
자료형은 element로, key field만 가지는 구조체 타입이다.
이는 당장은 불필요하지만, 추후에 다른 자료형을 추가/변형이 필요할 시에 유용하다.

스택은 다음과 같은 기본적인 함수를 구현한다.
Stack CreateStack(max_stack_size),
void Add(stack, item);
Element Delete(stack);
Boolean IsEmpty(Stack);
Boolean IsFull(Stack, max_stack_size);
*/
#define MAX_STACK_SIZE 10

typedef struct {
    int key;
} Element;

int top = -1;

typedef Element* Stack;
typedef int boolean;
Stack CreateStack(int max_stack_size);
boolean IsFull(Stack stack, int max_stack_size);
void Add(Stack stack, int* top, Element item);
boolean IsEmpty(Stack stack);
Element Delete(Stack stack, int* top);

void main() {
    Element* stack = CreateStack(MAX_STACK_SIZE);
    free(stack);
    return;
}

Stack CreateStack(int max_stack_size) {
    Element* stack;
    stack = (Element*)malloc(max_stack_size * sizeof(Element));
    return stack;
}

boolean IsFull(Stack stack, int max_stack_size) {
    if (top >= max_stack_size - 1) {
        return 0;
    }
    else {
        return 1;
    }
}

boolean IsEmpty(Stack stack) {
    if (top < 0) {
        return 0;
    }
    else {
        return 1;
    }
}

void Add(Stack stack, int* top, Element item) {
    if (*top >= MAX_STACK_SIZE) {
        stack_full();
        return;
    }
    else {
        stack[++*top] = item;
    }
}

Element Delete(Stack stack, int* top) {
    if (*top == -1) {
        return stack_empty();
    }
    return stack[(*top)--];
}