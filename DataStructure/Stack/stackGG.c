#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} Element;

typedef struct {
    int top;
    int capacity;
    Element* array;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Element*)malloc(capacity * sizeof(Element));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    if (isFull(stack)) {
        // return nothing and raise error or return error key
        return;
    }
    Element* newItem = (Element*)malloc(sizeof(Element));
    newItem->key = item;
    stack->array[++stack->top] = *newItem;
    printf("%d pushed to stack\n", item);
    return;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        return INT32_MIN;
    }
    return stack->array[stack->top--].key;
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        return INT32_MIN;
    }
    return stack->array[stack->top].key;
}

#define MAX_STACK_SIZE 100

void main() {
    Stack* stack = createStack(MAX_STACK_SIZE);
    push(stack, 10);
    printf("%d popped from stack\n", pop(stack));
    return;
}