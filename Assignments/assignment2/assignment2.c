#include <stdio.h>
#include <stdlib.h>
#include "assignment2.h"
#define TRUE 1
#define FALSE 0

struct Bst {
    int nodes;
    struct node* root;
};

struct node
{
    int data; //node will store an integer
    struct node* right_child; // right child
    struct node* left_child; // left child
};

struct Queue {
    int size;
    struct qNode* front;
    struct qNode* rear;
};

struct qNode {
    int data;
    struct qNode* next;
};

struct Bst bst = { 0, NULL };
struct Queue queue = { 0, NULL, NULL };

int main() {
    test();
    return 0;
}

void test() {
    int values[7] = { 6, 7, 2, 1, 4, 3, 5 };

    testEmpty();
    for (int i = 0; i < 7; i++) {
        put(values[i]);
    }

    testContains();

    testInOrder();
    testPreOrder();
    testPostOrder();
    
    delete(2);

    testInOrder();

    makeEmpty();
    testEmpty();
}

void testEmpty() {
    printf("BST is empty: %d\n", isEmpty());
}

void put(int data) {
    struct node* root;
    struct node* leafNode;
    if (isEmpty()) {
        root = createNode(data);
        bst.root = root;
        bst.nodes += 1;
        return;
    }
    root = bst.root;
    leafNode = searchLeafNode(root, data);
    addChild(leafNode, data);
    return;
}

boolean isEmpty() {
    if (bst.root == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    return newNode;
}

struct node* searchLeafNode(struct node* root, int data) {
    if (isEmpty() || root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        return NULL;
    }
    if (root->left_child == NULL || root->right_child == NULL) {
        return root;
    }
    if (root->data > data) {
        return searchLeafNode(root->left_child, data);
    }
    else {
        return searchLeafNode(root->right_child, data);
    }
}

void addChild(struct node* parent, int data) {
    struct node* newNode;
    if (parent == NULL) {
        return;
    }
    newNode = createNode(data);
    if (parent->data > data) {
        parent->left_child = newNode;
    }
    else {
        parent->right_child = newNode;
    }
    bst.nodes += 1;
}

void testContains() {
    printf("BST contains 4: %d\n", contains(4));
}

boolean contains(int data) {
    struct node* root;
    struct node* containingNode;
    if (isEmpty()) {
        return FALSE;
    }
    root = bst.root;
    containingNode = search(root, data);
    if (containingNode == NULL) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

struct node* search(struct node* root, int data) {
    if (isEmpty() || root == NULL) {
        return NULL;
    }
    if (data == root->data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left_child, data);
    }
    else {
        return search(root->right_child, data);
    }
}

void testInOrder() {
    inOrder(bst.root);
    printQueue(&queue);
}

void inOrder(struct node* root) {
    if (isEmpty() || root == NULL) {
        return;
    }
    inOrder(root->left_child);
    pushQueue(&queue, root->data);
    inOrder(root->right_child);
}

void pushQueue(struct Queue* queue,  int data) {
    struct qNode* newQNode = createQNode(data);
    if (queue->rear == NULL) {
        queue->front = newQNode;
    }
    else {
        queue->rear->next = newQNode;
    }
    queue->rear = newQNode;
    queue->size += 1;
}

struct qNode* createQNode(int data) {
    struct qNode* newQNode = (struct qNode*)malloc(sizeof(struct qNode));
    newQNode->data = data;
    newQNode->next = NULL;
    return newQNode;
}

void printQueue(struct Queue* queue) {
    struct qNode* front;
    if (queue->front == NULL) {
        return;
    }
    else {
       while (queue->front != NULL) {
           int data = popQueue(queue);
           printf("%d", data);
       }
    }
    printf("\n");
}

int popQueue(struct Queue* queue) {
    struct qNode* frontQNode;
    int data;
    if (queue->front == NULL) {
        return 0;
    }
    frontQNode = queue->front;
    data = frontQNode->data;
    queue->front = frontQNode->next;
    queue->size -= 1;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(frontQNode);
    return data;
}

void testPreOrder() {
    preOrder(bst.root);
    printQueue(&queue);
}

void preOrder(struct node* root) {
    if (isEmpty() || root == NULL) {
        return;
    }
    pushQueue(&queue, root->data);
    preOrder(root->left_child);
    preOrder(root->right_child);
}

void testPostOrder() {
    postOrder(bst.root);
    printQueue(&queue);
}

void postOrder(struct node* root) {
    if (isEmpty() || root == NULL) {
        return;
    }
    postOrder(root->left_child);
    postOrder(root->right_child);
    pushQueue(&queue, root->data);
}

void delete(int data) {
    struct node* parent = NULL;
    struct node* root;

    if (isEmpty()) {
        return;
    }
    root = bst.root;
    if (root->data == data) {
        free(root);
        bst.root = NULL;
        bst.nodes -= 1;
        return;
    }
    parent = searchParent(root, data);
    deleteNode(parent, data);
    return;
}

struct node* searchParent(struct node* root, int data) {
    if (isEmpty() || root == NULL) {
        return NULL;
    }
    if (data < root->data) {
        if (root->left_child == NULL) {
            return NULL;
        }
        if ((root->left_child)->data == data) {
            return root;
        }
        return searchParent(root->left_child, data);
    }
    else {
        if (root->right_child == NULL) {
            return NULL;
        }
        if ((root->right_child)->data == data) {
            return root;
        }
        return searchParent(root->right_child, data);
    }
}

void deleteNode(struct node* parent, int data) {
    struct node* child;
    boolean isLeftChild;
    if (parent == NULL) {
        return;
    }
    if (data < parent->data) {
        child = parent->left_child;
        isLeftChild = TRUE;
    }
    else {
        child = parent->right_child;
        isLeftChild = FALSE;
    }
    deleteChild(parent, child, isLeftChild);
}

void deleteChild(struct node* parent, struct node* child, boolean isLeftChild) {
    if (isLeafNode(child)) {
        if (isLeftChild) {
            parent->left_child = NULL;
        }
        else {
            parent->right_child = NULL;
        }
        bst.nodes -= 1;
        free(child);
        return;
    }
    if (hasAChild(child)) {
        if (child->right_child == NULL && isLeftChild) {
            parent->left_child = child->left_child;
        }
        if (child->right_child == NULL && isLeftChild == FALSE) {
            parent->right_child = child->left_child;
        }
        if (child->left_child == NULL && isLeftChild) {
            parent->left_child = child->right_child;
        }
        if (child->left_child == NULL && isLeftChild == FALSE) {
            parent->right_child = child->right_child;
        }
        bst.nodes -= 1;
        free(child);
        return;
    }
    if (hasTwoChildren(child)) {
        int maxData;
        struct node* maxNodeParent = findMaxNodeParent(child->left_child);
        if (maxNodeParent->right_child == NULL) {
            maxData = maxNodeParent->data;
            deleteNode(child, maxData);
        }
        else {
            maxData = (maxNodeParent->right_child)->data;
            deleteNode(maxNodeParent, maxData);
        }
        child->data = maxData;
        return;
    }
}

struct node* findMaxNodeParent(struct node* root) {
    struct node* parent;
    struct node* temp = root;
    while (temp->right_child != NULL) {
        temp = temp->right_child;
    }
    return temp;
}

boolean isLeafNode(struct node* root) {
    if (root->left_child == NULL && root->right_child == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

boolean hasAChild(struct node* root) {
    if (isLeafNode(root) || hasTwoChildren(root)) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

boolean hasTwoChildren(struct node* root) {
    if (root->left_child != NULL && root->right_child != NULL) {
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
        postOrderDelete(bst.root);
        bst.nodes = 0;
        bst.root = NULL;
    }
}

void postOrderDelete(struct node* root) {
    if (root == NULL) {
        return;
    }
    postOrderDelete(root->left_child);
    postOrderDelete(root->right_child);
    free(root);
}