#include <stdio.h>
#include <stdlib.h>
#include "assignment3.h";

typedef struct {
    int index;
    int cost;
    Vertex* next;
} Vertex;

typedef struct {
    int source;
    int target;
    int cost;
} Edge;

typedef struct {
    int label;
    int item;
} HeapItem;

struct MinHeap {
    int heapSize;
    HeapItem* heap[121];
} minHeap = { 0, {NULL} };

struct Graph {
    int vertices;
    Vertex* adjacencyList[16];
} graphComponent = { 0, { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };

int main() {
    int adjacencyMatrix[16][16] = {
        {0,3,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
        {3,0,1,0,0,5,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,4,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,4,0,0,0,0,6,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,1,0,0,3,0,0,0,0,0,0,0},
        {0,5,0,0,1,0,5,0,0,4,0,0,0,0,0,0},
        {0,0,1,0,0,5,0,8,0,0,2,0,0,0,0,0},
        {0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,0},
        {0,0,0,0,3,0,0,0,0,2,0,0,2,0,0,0},
        {0,0,0,0,0,4,0,0,2,0,4,0,0,6,0,0},
        {0,0,0,0,0,0,2,0,0,4,0,6,0,0,0,0},
        {0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,4},
        {0,0,0,0,0,0,0,0,2,0,0,0,0,3,0,0},
        {0,0,0,0,0,0,0,0,0,6,0,0,3,0,5,0},
        {0,0,0,0,0,0,0,0,0,0,4,0,0,5,0,7},
        {0,0,0,0,0,0,0,0,0,0,0,4,0,0,7,0},
    };
    createAdjacencyListfromMatrix(graphComponent, adjacencyMatrix);
    return 0;
}

void createAdjacencyListfromMatrix(struct Graph graph, const int adjacencyMatrix[16][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                graph.vertices += 1;
                Vertex* newVertex = createVertex(j, adjacencyMatrix[i][j]);
                addVertexToList(graph.adjacencyList, i, newVertex);
            }
        }
    }
}

Vertex* createVertex(const int index, const int cost) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->index;
    newVertex->cost = cost;
    newVertex->next = NULL;
    return newVertex;
}

void addVertexToList(Vertex* adjacencyList[16], const int index, Vertex* newVertex) {
    if (adjacencyList[index] == NULL) {
        adjacencyList[index] = newVertex;
    }
    else {
        Vertex* lastLinkedVertex = getLastLinkedVertex(adjacencyList[index]);
        lastLinkedVertex->next = newVertex;
    }
}

Vertex* getLastLinkedVertex(Vertex* linkedVertex) {
    Vertex* temp = linkedVertex;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}

void clearLinkedList(Vertex* linkedVertex) {
    Vertex* temp = linkedVertex;
    if (temp != NULL) {
        clearLinkedList(temp->next);
        free(temp);
    }
}

void insertItemToMinHeap(struct MinHeap minheap, HeapItem* item) {
    int isHeapified;
    int index = minheap.heapSize + 1;
    minHeap.heapSize += 1;
    minheap.heap[index] = item;
    for (; index > 0; index/2) {
        isHeapified = minHeapify(index, minHeap.heap);
        if (!isHeapified) {
            break;
        }
    }
}

int minHeapify(int index, HeapItem* heap[121]) {
    int rootIndex = index / 2;
    if (rootIndex < 1) {
        return 0;
    }
    if (heap[rootIndex]->item > heap[index]->item) {
        HeapItem* temp = heap[rootIndex];
        heap[rootIndex] = heap[index];
        heap[index] = temp;
        return 1;
    }
    else {
        return 0;
    }
    
}

HeapItem* popHeapItem(struct MinHeap minheap) {
    int rootIndex, rightChildIndex, leftChildIndex;
    HeapItem *minItem, *lastItem;
    if (minheap.heapSize == 0) {
        return NULL;
    }
    rootIndex = 1;
    minItem = minheap.heap[rootIndex];
    if (minheap.heapSize == 1) {
        minheap.heapSize -= 1;
        minheap.heap[rootIndex] = NULL;
        return minItem;
    }
    minheap.heapSize -= 1;
    lastItem = minheap.heap[minheap.heapSize];
    minheap.heap[rootIndex] = lastItem;
    minheap.heap[minheap.heapSize] = NULL;

    for (; rootIndex < minheap.heapSize; ) {
        leftChildIndex = rootIndex * 2;
        rightChildIndex = rootIndex * 2 + 1;
        if (minheap.heap[rightChildIndex] == NULL && minheap.heap[rootIndex]->item > minheap.heap[leftChildIndex]->item) {
            HeapItem* temp = minheap.heap[rootIndex];
            minheap.heap[rootIndex] = minheap.heap[leftChildIndex];
            minheap.heap[leftChildIndex] = temp;
            break;
        }
        else {
            int minItemIndex;
            if (minheap.heap[leftChildIndex]->item < minheap.heap[rightChildIndex]->item) {
                minItemIndex = leftChildIndex;
            }
            else {
                minItemIndex = rightChildIndex;
            }
            if (minheap.heap[rootIndex]->item > minheap.heap[minItemIndex]->item) {
                HeapItem* temp = minheap.heap[rootIndex];
                minheap.heap[rootIndex] = minheap.heap[minItemIndex];
                minheap.heap[minItemIndex] = temp;
                rootIndex = minItemIndex;
            }
            else {
                break;
            }
        }

    }
    
    return minItem;
}