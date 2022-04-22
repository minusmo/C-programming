#include <stdio.h>
#include <stdlib.h>
/*
Singly Linked List는 
노드들이 단방향으로 연결된 정렬된 Linked List로,
배열과는 달리,
연속된 메모리 공간을 사용하지 않고,
프로그램이 실행될 때마다 다른 메모리 공간을 노드들이 점유하게 된다.
*/

typedef list_node* list_pointer;
typedef struct
{
    int data;
    list_pointer link;
} list_node;
void insert(list_pointer* ptr, list_pointer node);
void delete(list_pointer* ptr, list_pointer trail, list_pointer node);

list_pointer ptr = NULL; //create new empty linked list

// #define IS_EMPTY(ptr) (!(ptr)) we can use IS_EMPTY macro to test for an empty list
// #define IS_FUll(ptr) (!(ptr)) returns NULL if there is no more memory
void main() {
    ptr = (list_pointer)malloc(sizeof(list_node));
    ptr->data = 1;
    ptr->link = NULL;
}

void insert(list_pointer* ptr, list_pointer node) {
    // insert a new node with data = 50 into the list ptr after node
    list_pointer temp;
    temp = (list_pointer)malloc(sizeof(list_node));
    if (IS_FULL(temp)) {
        printf(stderr, "The memory is full\n");
        exit(1);
    }
    temp->data = 50;
    if (*ptr) {
        temp->link = node->link;
        node->link = temp;
    }
    else {
        temp->link = NULL;
        *ptr = temp;
    }
}

void delete(list_pointer* ptr, list_pointer trail, list_pointer node) {
    // delete node from the list, trail is the preceding node. ptr is the head of the list
    if (trail) {
        trail->link = node->link;
    }
    else {
        *ptr = (*ptr)->link;
    }
    free(node);
}

void invert(list_node* head) {
    list_node* curr = head;
    list_node* prev = NULL;
    list_node* next = NULL;

    while (curr != NULL)
    {
        next = curr->link;
        curr->link = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

list_node* concatenate(list_node* list1, list_node* list2) {
    list_node* temp;
    if (IS_EMPTY(list1)) {
        return list2;
    }
    else {
        if (!IS_EMPTY(list2)) {
            temp = list1;
            while (temp->link != NULL) {
                temp = temp->link;
            }
            temp->link = list2;
        }
        return list1;
    }
}