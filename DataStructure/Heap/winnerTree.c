#include <stdio.h>
#include <stdlib.h>
/*
winner tree는 입력 시퀀스에서 최종 승자(winner)를 골라내는 트리구조이다.
주로 정수 배열이 주어지며, 이 배열의 원소는 key이다.
이 key를 비교하여 승자가 위로 올라가는 구조이다.
이 때, 입력 배열은 externel node라 하며,
트리 구조는 internal node라 한다.
이 방법은 입력 시퀀스의 크기가 클 때,
가능한 적은 비교를 통해 최소 값을 찾아내는 데에 의의가 있다.

시간 복잡도는 O(n + logn)으로,
O(n) => winner tree를 만드는 시간
O(logn) => winner의 위치를 탐색하는 시간이다.
*/

typedef struct {
    int index;
    node *left, *right;
} node;

node* createNode(int index) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->left = newNode->right = NULL;
    newNode->index = index;
    return newNode;
}

void traversHeight(node* root, int arr[], int* result) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return;
    }
    if (*result > arr[root->left->index] && root->left->index != root->index) {
        *result = arr[root->left->index];
        traversHeight(root->right, arr, result);
    }
    else {
        if (*result > arr[root->right->index] && root->right->index != root->index) {
            *result = arr[root->right->index];
            traversHeight(root->left, arr, result);
        }
    }
}