#include <stdio.h>

/*
*/
typedef struct {
    int data;
    node* next;
    node* prev;
} node;

void insert(node* nptr, node* newnode) {
    newnode->prev = nptr;
    newnode->next = nptr->next;
    nptr->next->prev = newnode;
    nptr->next = newnode;
}

void delete(node* nptr, node* deleted) {
    if (nptr == deleted) {
        printf("Deletion of head node not permitted.\n");
    }
    else {
        deleted->prev->next = deleted->next;
        deleted->next->prev = deleted->prev;
        free(deleted);
    }
}

void insertEnd(node** start, int value) {
    if (*start == NULL) {
        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = value;
        newNode->next = newNode;
        newNode->prev = newNode;
        *start = newNode;
        return;
    }

    //find last node
    node* last = (*start)->prev;
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = value;
    last->next = newNode;
    newNode->prev = last;
    newNode->next = *start;
    (*start)->prev = newNode;
}

void insertBegin(node** start, int value) {
    node* last = (*start)->prev;
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = value;

    newNode->next = *start;
    newNode->prev = last;
    last->next = newNode;
    (*start)->prev = newNode;

    *start = newNode;
}

void insertAfter(node** start, int valueToInsert, int valuePrecede) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = valueToInsert;

    node* temp = *start;
    while (temp->data != valuePrecede) {
        temp = temp->next;
    }
    node* next = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = next;
    next->prev = newNode;
}