struct graph;
typedef struct vertex;
typedef struct edge;

void relaxDistances(const vertex vertex, const struct graph graph);
edge takeMinimumCostEdge(const edge edges[]);