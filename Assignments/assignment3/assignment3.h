struct Graph;
struct MinHeap;
typedef struct Vertex;
typedef struct Edge;
typedef struct HeapItem;

void createAdjacencyListfromMatrix(struct Graph undirectedGraph, int adjacencyMatrix[][16]);
Vertex* createVertex(const int index, const int cost);
void addVertexToList(Vertex* adjacencyList[16], const int index, Vertex* newVertex);
Vertex* getLastLinkedVertex(Vertex* linkedVertex);
void clearLinkedList(Vertex* linkedVertex);
void insertItemToMinHeap(struct MinHeap minheap, HeapItem item);
int minHeapify(int index, HeapItem* heap[121]);
HeapItem* popHeapItem(struct MinHeap minheap);
void findMSTUsingKruskalMethod(struct Graph graph, struct MinHeap minheap, int adjacencyMatrix[16][16]);
Edge* takeMinimumCostEdge();
void relaxDistances(Vertex vertex, struct Graph graph);