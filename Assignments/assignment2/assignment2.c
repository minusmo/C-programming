#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int boolean;
struct node
{
    int data; //node will store an integer
    struct node* right_child; // right child
    struct node* left_child; // left child
};

boolean isEmpty();
void makeEmpty();
void inOrder(struct node* root);
void preOrder(struct node* root);
void postOrder(struct node* root);
boolean contains(int data);
void put(int data);
void delete(int data);

struct node* root = NULL;

int main() {
    return 0;
}

boolean isEmpty() {
    if (root == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void makeEmpty() {
    if (isEmpty()) {
        return;
    }
    else {
        postOrder(root);
    }
}

void inOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    else {
        inOrder(root->left_child);
        pushQueue(root->data);
        inOrder(root->right_child);
    }
}

void preOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    else {
        pushQueue(root->data);
        preOrder(root->left_child);
        preOrder(root->right_child);
    }
}

void postOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    else {
        postOrder(root->left_child);
        postOrder(root->right_child);
        pushQueue(root->data);
    }
}

boolean contains(int data) {
    struct node* temp;
    if (isEmpty()) {
        return FALSE;
    }
    temp = root;
    while (temp)
    {
        if (data == temp->data) {
            return TRUE;
        }
        else {
            if (data < temp->data) {
                temp = temp->left_child;
            }
            else {
                temp = temp->right_child;
            }
        }
    }
    return FALSE;
}

void put(int data) {
    struct node* temp;
    if (isEmpty()) {
        return;
    }
    temp = root;
    while (temp)
    {
        if (data == temp->data) {
            return;
        }
        else {
            if (data < temp->data && data > temp->left_child) {
                struct node* newNode = (struct node*)malloc(sizeof(struct node));
                newNode->data = data;
                newNode->left_child = temp->left_child;
                temp->left_child = newNode;
            }
            else {
                temp = temp->right_child;
            }
        }
    }
    return;
}