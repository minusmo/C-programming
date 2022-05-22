#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct
{
    int data; //node will store an integer
    struct node* right_child; // right child
    struct node* left_child; // left child
} node;

typedef node** BinarySearchTree;

BinarySearchTree Create();
int IsEmpty(BinarySearchTree root);
BinarySearchTree MakeBST(BinarySearchTree bst1, int item, BinarySearchTree bst2);
BinarySearchTree Lchild(BinarySearchTree bst);
BinarySearchTree Rchild(BinarySearchTree bst);
BinarySearchTree Data(BinarySearchTree bst);
void InorderTraversal(BinarySearchTree bst);
void PreorderTraversal(BinarySearchTree bst);
void PostorderTraversal(BinarySearchTree bst);
void LevelorderTraversal(BinarySearchTree bst);

int main() {
    return 0;
}

void InorderTraversal(BinarySearchTree bst) {
    if (*bst) {
        
    }
}