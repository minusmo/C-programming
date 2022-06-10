#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "assignment3.h"

struct Vertex {
    int index;
    int cost;
    struct Vertex* next;
};

struct VertexNode {
    struct VertexNode* parent;
    int index;
};

struct Edge {
    int source;
    int destination;
    int cost;
};

struct HeapItem {
    int label1;
    int label2;
    int value;
};

struct MinHeap {
    int heapSize;
    struct HeapItem* heap[MAX_EDGES];
};

struct Graph {
    int vertices;
    struct Vertex* adjacencyList[V];
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
        {0,0,0,6,0,0,8,0,0,0,0,6,0,0,0,0},
        {0,0,0,0,3,0,0,0,0,2,0,0,2,0,0,0},
        {0,0,0,0,0,4,0,0,2,0,4,0,0,6,0,0},
        {0,0,0,0,0,0,2,0,0,4,0,6,0,0,4,0},
        {0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,4},
        {0,0,0,0,0,0,0,0,2,0,0,0,0,3,0,0},
        {0,0,0,0,0,0,0,0,0,6,0,0,3,0,5,0},
        {0,0,0,0,0,0,0,0,0,0,4,0,0,5,0,7},
        {0,0,0,0,0,0,0,0,0,0,0,4,0,0,7,0},
    };
    createAdjacencyListfromMatrix(&undirectedGraph, adjacencyMatrix);
    test(adjacencyMatrix);
    clearAdjacencyList();
    return 0;
}

void test(int adjacencyMatrix[V][V]) {
    testAdjacencyList();
    testKruskalMethod(adjacencyMatrix);
    testDijkstraMethod(0);
}

void testAdjacencyList() {
    for (int i = 0; i < V; i++) {
        printf("Vertex %d is adjacent to following vertices", i+1);
        printLinkedList(undirectedGraph.adjacencyList[i]);
    }
}

void printLinkedList(struct Vertex* vertex) {
    struct Vertex* temp = vertex;
    while (temp != NULL)
    {
        printf(" %d(cost: %d)", temp->index + 1, temp->cost);
        temp = temp->next;
    }
    printf("\n");
}

void testKruskalMethod(int adjacencyMatrix[V][V]) {
    findMSTUsingKruskalMethod(undirectedGraph, &priorityQueue, adjacencyMatrix);
}

void testDijkstraMethod(int source) {
    findSSSPUsingDijkstraMethod(undirectedGraph, &priorityQueue, source);
}

void clearAdjacencyList() {
    for (int i = 0; i < V; i++) {
        clearLinkedList(undirectedGraph.adjacencyList[i]);
    }
}

void createAdjacencyListfromMatrix(struct Graph* undirectedGraph, int adjacencyMatrix[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                undirectedGraph->vertices += 1;
                struct Vertex* newVertex = createVertex(j, adjacencyMatrix[i][j]);
                addVertexToList(undirectedGraph->adjacencyList, i, newVertex);
            }
        }
    }
}

struct Vertex* createVertex(const int index, const int cost) {
    struct Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    newVertex->index = index;
    newVertex->cost = cost;
    newVertex->next = NULL;
    return newVertex;
}

void addVertexToList(struct Vertex* adjacencyList[V], const int index, struct Vertex* newVertex) {
    if (adjacencyList[index] == NULL) {
        adjacencyList[index] = newVertex;
    }
    else {
        struct Vertex* lastLinkedVertex = getLastLinkedVertex(adjacencyList[index]);
        lastLinkedVertex->next = newVertex;
    }
}

struct Vertex* getLastLinkedVertex(struct Vertex* linkedVertex) {
    struct Vertex* temp = linkedVertex;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}

void clearLinkedList(struct Vertex* linkedVertex) {
    struct Vertex* temp = linkedVertex;
    if (temp != NULL) {
        clearLinkedList(temp->next);
        free(temp);
    }
}

void findMSTUsingKruskalMethod(struct Graph graph, struct MinHeap* minheap, int adjacencyMatrix[V][V]) {
    int mstEdgeSet[V][V];
    int mstEdges = 0;
    struct VertexNode* disjointSet[V];
    createMSTSet(mstEdgeSet);
    initializeMinHeap(minheap);
    createDisjointSets(disjointSet);
    sortEdgeSetAscending(adjacencyMatrix);
    while (!isMST(mstEdges)) {
        struct Edge* minEdge = takeMinimumCostEdge();
        if (isCycle(disjointSet, minEdge)) {
            continue;
        }
        else {
            mergeTwoTrees(disjointSet, minEdge);
            addToMSTSet(&mstEdges, mstEdgeSet, minEdge);
        }
    }
    printMST(mstEdgeSet);
}

void createMSTSet(int mstEdgeSet[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            mstEdgeSet[i][j] = 0;
        }
    }
}

void createDisjointSets(struct VertexNode* disjointSets[V]) {
    for (int i = 0; i < V; i++) {
        struct VertexNode* disjointSet = (struct VertexNode*)malloc(sizeof(struct VertexNode));
        disjointSet->index = i;
        disjointSet->parent = NULL;
        disjointSets[i] = disjointSet;
    }
}

void sortEdgeSetAscending(int adjacencyMatrix[V][V]) {
    int temp[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjacencyMatrix[i][j] != 0 && (temp[i][j] != -1 || temp[j][i] != -1)) {
                struct HeapItem* heapitem = (struct HeapItem*)malloc(sizeof(struct HeapItem));
                heapitem->label1 = i;
                heapitem->label2 = j;
                heapitem->value = adjacencyMatrix[i][j];
                insertItemToMinHeap(&priorityQueue, heapitem);
                temp[i][j] = -1;
                temp[j][i] = -1;
            }
        }
    }
}

void insertItemToMinHeap(struct MinHeap* minheap, struct HeapItem* newHeapItem) {
    int isHeapified;
    int index = minheap->heapSize + 1;
    minheap->heapSize += 1;
    minheap->heap[index] = newHeapItem;
    for (; index > 1; index = index/2) {
        isHeapified = minHeapify(index, minheap->heap);
        if (!isHeapified) {
            break;
        }
    }
}

int minHeapify(int index, struct HeapItem* heap[MAX_EDGES]) {
    int rootIndex = index / 2;
    if (rootIndex < 1) {
        return 0;
    }
    if (heap[rootIndex]->value > heap[index]->value) {
        struct HeapItem* temp = heap[rootIndex];
        heap[rootIndex] = heap[index];
        heap[index] = temp;
        return 1;
    }
    else {
        return 0;
    }
}

int isMST(int mstEdges) {
    if (mstEdges == V-1) {
        return 1;
    }
    else {
        return 0;
    }
}

struct Edge* takeMinimumCostEdge() {
    struct HeapItem* minHeapItem = popHeapItem(&priorityQueue);
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->source = minHeapItem->label1;
    newEdge->destination = minHeapItem->label2;
    newEdge->cost = minHeapItem->value;
    free(minHeapItem);
    return newEdge;
}

struct HeapItem* popHeapItem(struct MinHeap* minheap) {
    int rootIndex, rightChildIndex, leftChildIndex, lastItemIndex;
    struct HeapItem *minItem, *lastItem;
    if (minheap->heapSize == 0) {
        return NULL;
    }
    rootIndex = 1;
    minItem = minheap->heap[rootIndex];
    lastItemIndex = minheap->heapSize;
    if (minheap->heapSize == 1) {
        minheap->heapSize -= 1;
        minheap->heap[rootIndex] = NULL;
        return minItem;
    }
    lastItem = minheap->heap[lastItemIndex];
    minheap->heap[rootIndex] = lastItem;
    minheap->heap[lastItemIndex] = NULL;
    minheap->heapSize -= 1;

    for (; rootIndex < minheap->heapSize; ) {
        leftChildIndex = rootIndex * 2;
        rightChildIndex = rootIndex * 2 + 1;
        if (minheap->heap[rightChildIndex] != NULL) {
            int minItemIndex;
            if (minheap->heap[leftChildIndex]->value < minheap->heap[rightChildIndex]->value) {
                minItemIndex = leftChildIndex;
            }
            else {
                minItemIndex = rightChildIndex;
            }
            if (minheap->heap[rootIndex]->value > minheap->heap[minItemIndex]->value) {
                struct HeapItem* temp = minheap->heap[rootIndex];
                minheap->heap[rootIndex] = minheap->heap[minItemIndex];
                minheap->heap[minItemIndex] = temp;
                rootIndex = minItemIndex;
            }
            else {
                break;
            }
        }
        else if (minheap->heap[leftChildIndex] != NULL) {
            if (minheap->heap[rootIndex]->value > minheap->heap[leftChildIndex]->value) {
                struct HeapItem* temp = minheap->heap[rootIndex];
                minheap->heap[rootIndex] = minheap->heap[leftChildIndex];
                minheap->heap[leftChildIndex] = temp;
                rootIndex = leftChildIndex;
            }
            else {
                break;
            }
        }
        else {
            break;
        }   
    }
    return minItem;
}

int isCycle(struct VertexNode* disjointSet[V], struct Edge* minEdge) {
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

int findRoot(struct VertexNode* disjointSet[V], int node) {
    struct VertexNode* temp = disjointSet[node];
    while (temp->parent != NULL) {
        temp = temp->parent;
    }
    return temp->index;
}

void mergeTwoTrees(struct VertexNode* disjointSet[V], struct Edge* minEdge) {
    int source, destination;
    source = minEdge->source;
    destination = minEdge->destination;
    if (source < destination) {
        disjointSet[destination]->parent = disjointSet[source];
    }
    else {
        disjointSet[source]->parent = disjointSet[destination];
    }
}

void addToMSTSet(int* mstEdges, int mstEdgeSet[V][V], struct Edge* minEdge) {
    int source, destination;
    source = minEdge->source;
    destination = minEdge->destination;
    
    mstEdgeSet[source][destination] = minEdge->cost;
    mstEdgeSet[destination][source] = minEdge->cost;
    (*mstEdges)++;
}

void printMST(int mstEdgeSet[V][V]) {
    printf("Minimum Spanning Tree using Kruskal's method consists of following edges.\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (mstEdgeSet[i][j] != 0) {
                printf("Edge from vertex %d to %d costs %d\n", i + 1, j + 1, mstEdgeSet[i][j]);
            }
        }
    }
}

void findSSSPUsingDijkstraMethod(struct Graph graph, struct MinHeap* minheap, int source) {
    int distanceFromSource[V];
    struct HeapItem* sourceItem;
    initializeMinHeap(minheap);
    initializeDistances(distanceFromSource, source);
    sourceItem = (struct HeapItem*)malloc(sizeof(struct HeapItem));
    sourceItem->label1 = 0;
    sourceItem->value = 0;
    insertItemToMinHeap(minheap, sourceItem);
    while (minheap->heapSize != 0)
    {
        struct HeapItem* closestVertex = popHeapItem(&priorityQueue);
        relaxDistances(closestVertex, graph, distanceFromSource, minheap);
    }
    printSSSP(distanceFromSource, source);
}

void initializeMinHeap(struct MinHeap* minheap) {
    while (minheap->heapSize != 0)
    {
        popHeapItem(minheap);
    }
}

void initializeDistances(int distanceFromSource[V], int source) {
    for (int i = 0; i < V; i++) {
        distanceFromSource[i] = INT_MAX;
    }
    distanceFromSource[source] = 0;
}

void relaxDistances(struct HeapItem* vertex, struct Graph graph, int distanceFromSource[V], struct MinHeap* minheap) {
    struct Vertex* adjacentVertex = graph.adjacencyList[vertex->label1];
    while (adjacentVertex != NULL)
    {   
        int currentVertex = adjacentVertex->index;
        int newDistance = vertex->value + adjacentVertex->cost;
        int currentDistance = distanceFromSource[currentVertex];
        if (newDistance < currentDistance) {
            distanceFromSource[currentVertex] = newDistance;
            struct HeapItem* newHeapItem = (struct HeapItem*)malloc(sizeof(struct HeapItem));
            newHeapItem->label1 = currentVertex;
            newHeapItem->value = newDistance;
            insertItemToMinHeap(minheap, newHeapItem);
        }
        adjacentVertex = adjacentVertex->next;
    }
}

void printSSSP(int distanceFromSource[V], int source) {
    printf("Following shortest paths are computed by Dijkstra's method\n");
    for (int i = 0; i < V; i++) {
        printf("Shortest path distance from vertex %d to %d is %d\n", source + 1, i + 1, distanceFromSource[i]);
    }
}