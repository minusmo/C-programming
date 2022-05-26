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

struct bstQueue bstQueue = { -1, -1, NULL };

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
    freeNode(root);
}

void freeNode(struct node* root) {
    free(root);
}

void inOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (bstQueue.queue == NULL) {
        createQueue(bst.nodes);
    }
    else {
        resetQueue();
    }
    inOrder(root->left_child);
    pushQueue(root->data);
    inOrder(root->right_child);
}

void createQueue(int queueSize) {
    bstQueue.queue = (int*)malloc(sizeof(int) * queueSize);
}

void resetQueue() {
    bstQueue.front = -1;
    bstQueue.rear = -1;
    free(bstQueue.queue);
    bstQueue.queue = (int*)malloc(bst.nodes * sizeof(int));
}

void pushQueue(int data) {
    bstQueue.rear += 1;
    bstQueue.queue[bstQueue.rear] = data;
}

void preOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (bstQueue.queue == NULL) {
        createQueue(bst.nodes);
    }
    else {
        resetQueue();
    }
    pushQueue(root->data);
    preOrder(root->left_child);
    preOrder(root->right_child);
}

void postOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (bstQueue.queue == NULL) {
        createQueue(bst.nodes);
    }
    else {
        resetQueue();
    }
    postOrder(root->left_child);
    postOrder(root->right_child);
    pushQueue(root->data);
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
        if (data < root->data) {
            if (root->left_child == NULL) {
                struct node* newNode = createNode(data);
                root->left_child = newNode;
                return;
            }
            else {
                root = root->left_child;
            }
        }
        else {
            if (root->right_child == NULL) {
                struct node* newNode = createNode(data);
                root->right_child = newNode;
                return;
            }
            else {
                root = root->right_child;
            }
        }
    }
    return;
}

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    return newNode;
}

void delete(int data) {
    struct node* parent = NULL;
    struct node* root;
    boolean isLeftChild = FALSE;

    if (isEmpty()) {
        return;
    }
    root = *(bst.tree);
    while (!root == NULL)
    {
        if (data == root->data) {
            deleteNode(parent, root, isLeftChild);
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

void deleteNode(struct node* parent, struct node* root, boolean isLeftChild) {
    if (root = *(bst.tree)) {
        freeNode(root);
        *(bst.tree) = NULL;
        return;
    }
    if (isLeafNode(root)) {
        freeNode(root);
        if (isLeftChild) {
            parent->left_child = NULL;
        }
        else {
            parent->right_child = NULL;
        }
        return;
    }
    if (hasOneChild(root)) {
        if (root->right_child == NULL && isLeftChild) {
            parent->left_child = root->left_child;
            freeNode(root);
            return;
        }
        if (root->right_child == NULL && !isLeftChild) {
            parent->right_child = root->left_child;
            freeNode(root);
            return;
        }
        if (root->left_child == NULL && isLeftChild) {
            parent->left_child = root->right_child;
            freeNode(root);
            return;
        }
        if (root->right_child == NULL && !isLeftChild) {
            parent->right_child = root->left_child;
            freeNode(root);
            return;
        }
        
    }
    if (hasTwoChildren(root)) {
        struct node* maxNode = findMaxNode(root->left_child);
        root->data = maxNode->data;

        return;
    }
}

struct node* findMaxNode(struct node* root) {
    
}

boolean isLeafNode(struct node* root) {
    if (root->left_child == NULL && root->right_child == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

boolean hasOneChild(struct node* root) {
    if (isLeafNode(root)) {
        return FALSE;
    }
    if (hasTwoChildren(root)) {
        return FALSE;
    }
    return TRUE;
}

boolean hasTwoChildren(struct node* root) {
    if (!root->left_child == NULL && !root->right_child == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}