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

struct bstQueue {
    int size;
    int front;
    int rear;
    int* queue;
};

struct qNode {
    int data;
    struct qNode* next;
};

struct queue {
    int size;
    struct qNode* front;
    struct qNode* rear;
};

struct bst bst = { 0, NULL };
struct bstQueue bstQueue = { 0, -1, -1, NULL };
struct queue queue = { 0, NULL, NULL };

int main() {
    int values[7] = { 6, 7, 2, 1, 4, 3, 5};
    printf("%d\n", isEmpty());
    for (int i = 0; i < 7; i++) {
        put(values[i]);
    }
    printf("%d\n", contains(4));
    inOrder(*(bst.tree));
    printQueue(queue.front);
    preOrder(*(bst.tree));
    printQueue(queue.front);
    postOrder(*(bst.tree));
    printQueue(queue.front);
    delete(2);
    inOrder(*(bst.tree));
    printQueue(queue.front);
    makeEmpty();
    printf("%d\n", isEmpty());
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
        bst.nodes = 0;
        bst.tree = NULL;
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
    if (queue.size != 0) {
        clearQueue();
    }
    inOrder(root->left_child);
    pushQueue(root->data);
    inOrder(root->right_child);
}

void createBstQueue(int queueSize) {
    bstQueue.queue = (int*)malloc(sizeof(int) * queueSize);
}

void resetBstQueue() {
    bstQueue.front = -1;
    bstQueue.rear = -1;
    free(bstQueue.queue);
    bstQueue.queue = (int*)malloc(bst.nodes * sizeof(int));
}

void pushBstQueue(int data) {
    if (isFullBstQueue()) {
        printf("queue is full");
        return;
    }
    bstQueue.rear = (bstQueue.rear + 1) ;
    bstQueue.queue[bstQueue.rear] = data;
    bstQueue.size += 1;
}

boolean isFullBstQueue() {
    if (bstQueue.size == bstQueue.rear + 1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void pushQueue(int data) {
    struct qNode* newQNode = createQNode(data);
    newQNode->next = NULL;
    queue.rear = newQNode;
    queue.size += 1;
}

int popQueue() {
    int data = (queue.front)->data;
    struct qNode* front = queue.front;
    queue.front = (queue.front)->next;
    queue.size -= 1;
    free(front);
    return data;
}

void clearQueue() {
    struct qNode* temp;
    if (queue.size == 0) {
        return;
    }
    while (!(queue.front == NULL)) {
        temp = queue.front;
        queue.front = (queue.front)->next;
        free(temp);
    }
}

void printQueue(struct qNode* front) {
    struct qNode* temp;
    temp = front;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void preOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (queue.size != 0) {
        clearQueue();
    }
    pushQueue(root->data);
    preOrder(root->left_child);
    preOrder(root->right_child);
}

void postOrder(struct node* root) {
    if (isEmpty()) {
        return;
    }
    if (queue.size != 0) {
        clearQueue();
    }
    postOrder(root->left_child);
    postOrder(root->right_child);
    pushQueue(root->data);
}

boolean contains(int data) {
    struct node* root;
    struct node* containingNode;
    if (isEmpty()) {
        return FALSE;
    }
    root = *(bst.tree);
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

void put(int data) {
    struct node* root;
    struct node* leafNode;
    if (isEmpty()) {
        root = createNode(data);
        bst.tree = &root;
        return;
    }
    root = *(bst.tree);
    leafNode = searchLeafNode(root, data);
    addChild(leafNode, data);
    return;
}

struct node* searchLeafNode(struct node* root, int data) {
    if (isEmpty() || root == NULL) {
        return NULL;
    }
    if (root->left_child == NULL || root->right_child == NULL) {
        return root;
    }
    if (root->data > data) {
        return searchLeafNode(root->left_child, data);
    }
    if (root->data < data) {
        return searchLeafNode(root->right_child, data);
    }
    if (root->data == data) {
        return NULL;
    }
}

void addChild(struct node* parent, int data) {
    if (!parent == NULL && parent->data > data) {
        parent->left_child = createNode(data);
    }
    if (!parent == NULL && parent->data < data) {
        parent->right_child = createNode(data);
    }
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

    if (isEmpty()) {
        return;
    }
    root = *(bst.tree);
    if (root->data == data) {
        freeNode(root);
        bst.tree = NULL;
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
    if (!parent == NULL && data < parent->data) {
        child = parent->left_child;
        isLeftChild = TRUE;
    }
    if (!parent == NULL && data > parent->data) {
        child = parent->right_child;
        isLeftChild = FALSE;
    }
    deleteChild(parent, child, isLeftChild);
}

void deleteChild(struct node* parent, struct node* child, int isLeftChild) {
    if (isLeafNode(child)) {
        freeNode(child);
        if (isLeftChild) {
            parent->left_child = NULL;
        }
        else {
            parent->right_child = NULL;
        }
        return;
    }
    if (hasAChild(child)) {
        if (child->right_child == NULL && isLeftChild) {
            parent->left_child = child->left_child;
        }
        if (child->right_child == NULL && !isLeftChild) {
            parent->right_child = child->left_child;
        }
        if (child->left_child == NULL && isLeftChild) {
            parent->left_child = child->right_child;
        }
        if (child->right_child == NULL && !isLeftChild) {
            parent->right_child = child->left_child;
        }
        freeNode(child);
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
    while (!temp->right_child == NULL) {
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
    if (!root->left_child == NULL && !root->right_child == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}