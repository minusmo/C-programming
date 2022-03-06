#include <stdio.h>
#include <stlib.h>
// sortedlist: 항상 정렬되어 있는 리스트를 이중연결리스트로 구현

typedef int element;
typedef struct listnode{
    element data;
    listnode *lnode;
    listnode *rnode;
} listnode;
typedef struct {
    int length;
    listnode *head;
} Linkedlist;

void init(Linkedlist *linkedlist)
{
    linkedlist->length = 0;
}