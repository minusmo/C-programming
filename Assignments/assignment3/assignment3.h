struct Graph;
struct MinHeap;
typedef struct Vertex;
typedef struct Edge;
typedef struct HeapItem;

void createAdjacencyListfromMatrix(struct Graph graph, const int adjacencyMatrix[16][16]);
Vertex* createVertex(const int index, const int cost);
void addVertexToList(Vertex* adjacencyList[16], const int index, Vertex* newVertex);
Vertex* getLastLinkedVertex(Vertex* linkedVertex);
void clearLinkedList(Vertex* linkedVertex);
void insertItemToMinHeap(struct MinHeap minheap, HeapItem item);
void relaxDistances(Vertex vertex, struct Graph graph);
Edge takeMinimumCostEdge(Edge edges[]);