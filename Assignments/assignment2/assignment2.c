#include <stdio.h>
#include <stdlib.h>
#include "assignment2.h"
#define TRUE 1
#define FALSE 0

struct node
{
    int data; //node will store an integer
    struct node* right_child; // right child
    struct node* left_child; // left child
};

struct bst {
    int nodes;
    struct node** tree;
};

struct bst bst = { 0, NULL };

struct bstQueue {
    int front;
    int rear;
    int* queue;
};

int main() {
    return 0;
}

boolean isEmpty() {
    if (bst.tree == NULL) {
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
        postOrderDelete(*(bst.tree));
    }
}

void postOrderDelete(struct node* root) {
    if (root == NULL) {
        return;
    }
    postOrderDelete(root->left_child);
    postOrderDelete(root->right_child);
    deleteNode(root);
}

void deleteNode(struct node* root) {
    free(root);
}

void inOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (bstQueue == NULL) {
        createQueue(bst.nodes);
    }
    inOrder(root->left_child);
    pushQueue(root->data);
    inOrder(root->right_child);
}

void createQueue(int queueSize) {
    bstQueue = (int*)malloc(sizeof(int) * queueSize);
}

void pushQueue(int data) {

}

void preOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (bstQueue == NULL) {
        createQueue(bst.nodes);
    }
    pushQueue(root->data);
    preOrder(root->left_child);
    preOrder(root->right_child);
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
    struct node* root;
    if (isEmpty()) {
        return FALSE;
    }
    root = *(bst.tree);
    while (root)
    {
        if (data == root->data) {
            return TRUE;
        }
        else {
            if (data < root->data) {
                root = root->left_child;
            }
            else {
                root = root->right_child;
            }
        }
    }
    return FALSE;
}

void put(int data) {
    struct node* root;
    if (isEmpty()) {
        return;
    }
    root = *(bst.tree);
    while (!root == NULL)
    {
        if (data == root->data) {
            return;
        }
        else {
            if (data < root->data) {
                if (root->left_child == NULL) {
                    struct node* newNode = (struct node*)malloc(sizeof(struct node));
                    newNode->data = data;
                    newNode->left_child = NULL;
                    newNode->right_child = NULL;
                    root->left_child = newNode;
                    return;
                }
                else {
                    root = root->left_child;
                }
            }
            else {
                if (root->right_child == NULL) {
                    struct node* newNode = (struct node*)malloc(sizeof(struct node));
                    newNode->data = data;
                    newNode->left_child = NULL;
                    newNode->right_child = NULL;
                    root->right_child = newNode;
                    return;
                }
                else {
                    root = root->right_child;
                }
            }
        }
    }
    return;
}

void delete(int data) {
    struct node* root;
    if (isEmpty()) {
        return;
    }
    root = *(bst.tree);
    while (!root == NULL)
    {
        if (data == root->data) {
            if (root->left_child == NULL && root->right_child == NULL) {
                
            }
            return;
        }
        else {
            if (data < root->data) {
                root = root->left_child;
            }
            else {
                root = root->right_child;
            }
        }
    }
    return;
}