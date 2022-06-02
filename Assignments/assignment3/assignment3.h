struct Graph;
typedef struct Vertex;
typedef struct Edge;

void createAdjacencyListfromMatrix(struct Graph graph, const int adjacencyMatrix[16][16]);
Vertex* createVertex(const int index, const int cost);
void addVertexToList(Vertex* adjacencyList[16], const int index, Vertex* newVertex);
Vertex* getLastLinkedVertex(Vertex* linkedVertex);
void relaxDistances(Vertex vertex, struct Graph graph);
Edge takeMinimumCostEdge(const Edge edges[]);