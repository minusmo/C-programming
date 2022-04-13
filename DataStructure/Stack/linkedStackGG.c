#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int data;
    StackNode* next;
} StackNode;

StackNode* newNode(int data) {
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(StackNode* top) {
    return !top;
}

void push(StackNode** top, int data) {
    StackNode* topNode = newNode(data);
    topNode->next = *top;
    *top = topNode;
    printf("%d pushed to stack\n", data);
    return;
}

int pop(StackNode** top) {
    if (isEmpty(*top)) {
        return INT_MIN;
    }
    StackNode* temp = *top;
    *top = (*top)->next;
    int poppedData = temp->data;
    free(temp);
    return poppedData;
}

int peek(StackNode* top) {
    if (isEmpty(top)) {
        return INT_MIN;
    }
    return top->data;
}

void main() {
    StackNode* top = NULL;
    push(&top, 10);
    push(&top, 20);

    printf("%d is popped from stack\n", pop(&top));
    printf("%d is top data\n", peek(top));
}