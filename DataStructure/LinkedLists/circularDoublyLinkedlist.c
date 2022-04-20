#include <stdio.h>


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