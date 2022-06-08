#define V 16
struct Graph;
struct MinHeap;
typedef struct Vertex;
typedef struct VertexNode;
typedef struct Edge;
typedef struct HeapItem;

void createAdjacencyListfromMatrix(struct Graph undirectedGraph, int adjacencyMatrix[V][V]);
Vertex* createVertex(const int index, const int cost);
void addVertexToList(Vertex* adjacencyList[V], const int index, Vertex* newVertex);
Vertex* getLastLinkedVertex(Vertex* linkedVertex);
void clearLinkedList(Vertex* linkedVertex);
void insertItemToMinHeap(struct MinHeap minheap, HeapItem item);
int minHeapify(int index, HeapItem* heap[121]);
HeapItem* popHeapItem(struct MinHeap minheap);
void findMSTUsingKruskalMethod(struct Graph graph, struct MinHeap minheap, int adjacencyMatrix[V][V]);
void createMSTSet(int mstEdgeSet[V]);
void createDisjointSets(VertexNode* disjointSets[V]);
void sortEdgeSetAscending(int adjacencyMatrix[V][V]);
int isNotMST(int mstNodes);
Edge* takeMinimumCostEdge();
int isCycle(VertexNode* disjointSet[V], Edge* minEdge);
int findRoot(VertexNode* disjointSet[V], int node);
void mergeTwoTrees(VertexNode* disjointSet[V], Edge* minEdge);
void addToMSTSet(int* mstNodes, int mstEdgeSet[V], Edge* minEdge);
int isMST(int mstNodes);
void relaxDistances(int vertex, struct Graph graph, int distanceFromSource[V], struct MinHeap minheap);