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

#define MAX_SIZE 10;

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

// 이 함수는 두번째로 작은 원소를 구하기 위한 함수이다.
// 첫번째로 작은 원소는 트리의 루트 노드의 원소이다.
/*
solution steps of traverseHeight
1. 루트 노드의 왼쪽 자식 노드의 키 값이 결과값보다 작고, 루트 노드의 키값과 다르면 결과값을 업데이트하고 오른쪽 서브트리를 탐색한다.
2. 루트 노드의 오른쪽 자식 노드의 키 값이 결과값보다 작고, 루트 노드의 키값과 다르면 결과값을 업데이트하고 왼쪽 서브트리를 탐색한다.
*/
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

void findSecondMin(int arr[], int n) {
    node* node_list = (node*)malloc(sizeof(node) * MAX_SIZE);
    int node_index = 0;
    node* root = NULL;

    for (int i = 0; i < n; i += 2) {
        node* t1 = createNode(i);
        node* t2 = NULL;

        if (i + 1 < n) {
            // 다음 원소를 위한 노드를 새로 만든다.
            t2 = createNode(i+1);
            // 둘 중 더 작은 원소를 루트 노드로 만든다.
            if (arr[i] < arr[i+1]) {
                root = createNode(i);
            }
            else {
                root = createNode(i+1);
            }
            // 두 노드를 새로운 루트노드의 자식 노드로 만든다.
            root->left = t1;
            root->right = t2;
            // 루트 노드를 추가한다.
            node_list[node_index] = root;
        }
        else {
            node_list[node_index] = t1;
        }
        node_index += 1;
    }

    int arr_size = node_index;
    // 완전 이진 트리를 위에서 부터 구성한다.
    node_index = 0;
    while (arr_size != 1)
    {
        //  마지막 쌍의 인덱스를 찾는다.
        int last = (arr_size & 1) ? (arr_size - 2) : (arr_size - 1);
        for (int i = 0; i < last; i += 2) {
            // root 노드 배열로 부터 두개의 노드를 추출한 후, 
            // 두 노드 중 winner의 root를 만든다.
            node* f1 = node_list[node_index];
            node_index += 1;
            node* f2 = node_list[node_index];
            node_index += 1;
            root = (arr[f1->index] < arr[f2->index]) ? createNode(f1->index) : createNode(f2->index);
            root->left = f1;
            root->right = f2;

            // root 노드를 node_list 맨 뒤에 추가한다.
        }
        if (arr_size & 1) {
            // node_list에 node_list 첫번째 값을 추가하고 제거한다.
        }
        // arr_size를 node_list의 크기로 한다.
    }
    
}