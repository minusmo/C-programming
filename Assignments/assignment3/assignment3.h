#define V 16 // number of vertices
#define MAX_EDGES 121 // maximum edges of undirected graph((V * (V-1))/2) + 1(for convenience for using heap index)

struct Graph;
struct MinHeap;
struct Vertex;
struct VertexNode;
struct Edge;
struct HeapItem;

void test(int adjacencyMatrix[V][V]);
void testAdjacencyList();
void testKruskalMethod(int adjacencyMatrix[V][V]);
void testDijkstraMethod(int source);
void printLinkedList(struct Vertex* vertex);
void clearAdjacencyList();

void createAdjacencyListfromMatrix(struct Graph* undirectedGraph, int adjacencyMatrix[V][V]);
struct Vertex* createVertex(const int index, const int cost);
void addVertexToList(struct Vertex* adjacencyList[V], const int index, struct Vertex* newVertex);
struct Vertex* getLastLinkedVertex(struct Vertex* linkedVertex);
void clearLinkedList(struct Vertex* linkedVertex);

void insertItemToMinHeap(struct MinHeap* minheap, struct HeapItem* item);
int minHeapify(int index, struct HeapItem* heap[MAX_EDGES]);
struct HeapItem* popHeapItem(struct MinHeap* minheap);
void initializeMinHeap(struct MinHeap* minheap);

void findMSTUsingKruskalMethod(struct Graph graph, struct MinHeap* minheap, int adjacencyMatrix[V][V]);
void createMSTSet(int mstEdgeSet[V][V]);
void createDisjointSets(struct VertexNode* disjointSets[V]);
void sortEdgeSetAscending(int adjacencyMatrix[V][V]);
int isMST(int mstNodes);
struct Edge* takeMinimumCostEdge();
int isCycle(struct VertexNode* disjointSet[V], struct Edge* minEdge);
int findRoot(struct VertexNode* disjointSet[V], int node);
void mergeTwoTrees(struct VertexNode* disjointSet[V], struct Edge* minEdge);
void addToMSTSet(int* mstNodes, int mstEdgeSet[V][V], struct Edge* minEdge);
void printMST(int mstEdgeSet[V][V]);

void findSSSPUsingDijkstraMethod(struct Graph graph, struct MinHeap* minheap, int source);
void initializeDistances(int distanceFromSource[V], int source);
void relaxDistances(struct HeapItem* vertex, struct Graph graph, int distanceFromSource[V], struct MinHeap* minheap);
void printSSSP(int distanceFromSource[V], int source);