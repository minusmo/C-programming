#include <stdio.h>
#include <stdlib.h>
#include "assignment3.h";

#define V 16
const int MaxEdges = (V * (V-1))/2 + 1;

typedef struct {
    int index;
    int cost;
    Vertex* next;
} Vertex;

typedef struct {
    VertexNode* parent;
    int index;
} VertexNode;

typedef struct {
    int source;
    int destination;
    int cost;
} Edge;

typedef struct {
    int label1;
    int label2;
    int value;
} HeapItem;

struct MinHeap {
    int heapSize;
    HeapItem* heap[MaxEdges];
};

struct Graph {
    int vertices;
    Vertex* adjacencyList[V];
}; 

struct MinHeap priorityQueue = { 0, { NULL } };
struct Graph undirectedGraph = { 0, { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };

int main() {
    int adjacencyMatrix[V][V] = {
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
    createAdjacencyListfromMatrix(undirectedGraph, adjacencyMatrix);
    return 0;
}

void createAdjacencyListfromMatrix(struct Graph undirectedGraph, int adjacencyMatrix[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                undirectedGraph.vertices += 1;
                Vertex* newVertex = createVertex(j, adjacencyMatrix[i][j]);
                addVertexToList(undirectedGraph.adjacencyList, i, newVertex);
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

void addVertexToList(Vertex* adjacencyList[V], const int index, Vertex* newVertex) {
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

void insertItemToMinHeap(struct MinHeap minheap, HeapItem* value) {
    int isHeapified;
    int index = minheap.heapSize + 1;
    priorityQueue.heapSize += 1;
    minheap.heap[index] = value;
    for (; index > 0; index/2) {
        isHeapified = minHeapify(index, priorityQueue.heap);
        if (!isHeapified) {
            break;
        }
    }
}

int minHeapify(int index, HeapItem* heap[MaxEdges]) {
    int rootIndex = index / 2;
    if (rootIndex < 1) {
        return 0;
    }
    if (heap[rootIndex]->value > heap[index]->value) {
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
        if (minheap.heap[rightChildIndex] == NULL && minheap.heap[rootIndex]->value > minheap.heap[leftChildIndex]->value) {
            HeapItem* temp = minheap.heap[rootIndex];
            minheap.heap[rootIndex] = minheap.heap[leftChildIndex];
            minheap.heap[leftChildIndex] = temp;
            break;
        }
        else {
            int minItemIndex;
            if (minheap.heap[leftChildIndex]->value < minheap.heap[rightChildIndex]->value) {
                minItemIndex = leftChildIndex;
            }
            else {
                minItemIndex = rightChildIndex;
            }
            if (minheap.heap[rootIndex]->value > minheap.heap[minItemIndex]->value) {
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

void findMSTUsingKruskalMethod(struct Graph graph, struct MinHeap minheap, int adjacencyMatrix[V][V]) {
    int mstEdgeSet[V];
    int mstNodes = 0;
    VertexNode* disjointSet[V];
    createMSTSet(mstEdgeSet);
    createDisjointSets(disjointSet);
    sortEdgeSetAscending(adjacencyMatrix);
    while (isNotMST(mstNodes)) {
        Edge* minEdge = takeMinimumCostEdge();
        if (isCycle(disjointSet, minEdge)) {
            continue;
        }
        else {
            mergeTwoTrees(disjointSet, minEdge);
            addToMSTSet(&mstNodes, mstEdgeSet, minEdge);
        }
        if (isMST(mstNodes)) {
            break;
        }
    }
}

void createMSTSet(int mstEdgeSet[V]) {
    for (int i = 0; i < V+1; i++) {
        mstEdgeSet[i] = 0;
    }
}

void createDisjointSets(VertexNode* disjointSets[V]) {
    for (int i = 0; i < V+1; i++) {
        VertexNode* disjointSet = (VertexNode*)malloc(sizeof(VertexNode));
        disjointSet->index = i;
        disjointSet->parent = NULL;
        disjointSets[i] = disjointSet;
    }
}

void sortEdgeSetAscending(int adjacencyMatrix[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                HeapItem* heapitem = (HeapItem*)malloc(sizeof(HeapItem));
                heapitem->label1 = i;
                heapitem->label2 = j;
                heapitem->value = adjacencyMatrix[i][j];
                insertItemToMinHeap(priorityQueue, heapitem);
            }
        }
    }
}

int isNotMST(int mstNodes) {
    if (mstNodes == 16) {
        return 0;
    }
    else {
        return 1;
    }
}

Edge* takeMinimumCostEdge() {
    HeapItem* minHeapItem = popHeapItem(priorityQueue);
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->source = minHeapItem->label1;
    newEdge->destination = minHeapItem->label2;
    newEdge->cost = minHeapItem->value;
    free(minHeapItem);
    return newEdge;
}

int isCycle(VertexNode* disjointSet[V], Edge* minEdge) {
    int source, destination, cost, root1, root2;
    source = minEdge->source;
    destination = minEdge->destination;
    cost = minEdge->cost;
    root1 = findRoot(disjointSet, source);
    root2 = findRoot(disjointSet, destination);
    if (root1 == root2) {
        return 1;
    }
    else {
        return 0;
    }
}

int findRoot(VertexNode* disjointSet[V], int node) {
    VertexNode* temp = disjointSet[node];
    while (temp->parent != NULL) {
        temp = temp->parent;
    }
    return temp->index;
}

void mergeTwoTrees(VertexNode* disjointSet[V], Edge* minEdge) {
    int source, destination;
    source = minEdge->source;
    destination = minEdge->destination;
    if (source < destination) {
        disjointSet[destination]->parent = source;
    }
    else {
        disjointSet[source]->parent = destination;
    }
}

void addToMSTSet(int* mstNodes, int mstEdgeSet[V], Edge* minEdge) {
    int source, destination;
    source = minEdge->source;
    destination = minEdge->destination;
    mstEdgeSet[source] = destination;
    mstEdgeSet[destination] = source;
    (*mstNodes)++;
}

int isMST(int mstNodes) {
    if (mstNodes == V) {
        return 1;
    }
    else {
        return 0;
    }
}

void findSSSPUsingDijkstraMethod(struct Graph graph, struct MinHeap minheap, int source) {
    int distanceFromSource[V];
    int isRelaxed;
    HeapItem* sourceItem;
    initializeDistances(distanceFromSource);
    sourceItem = (HeapItem*)malloc(sizeof(HeapItem));
    sourceItem->label1 = 0;
    sourceItem->value = 0;
    insertItemToMinHeap(minheap, sourceItem);
    while (minheap.heapSize != 0)
    {
        HeapItem* closestVertex = popHeapItem(priorityQueue);
        relaxDistances(closestVertex->label1, graph, distanceFromSource, minheap);
    }
    for (int i = 0; i < V; i++) {
        printf("%d ", distanceFromSource[i]);
    }
}