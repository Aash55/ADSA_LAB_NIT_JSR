#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define MAX_VERTICES 100

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a graph
typedef struct {
    int V, E;
    Edge edges[MAX_EDGES];
} Graph;

// Structure to represent a subset for union-find
typedef struct {
    int parent;
    int rank;
} Subset;

// A utility function to create a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    return graph;
}

// A utility function to find the set of an element i (uses path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y (uses union by rank)
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges based on their weights for qsort()
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V]; // TBD: Correct size based on max edges in MST
    int e = 0; // Index variable for result[]
    int i = 0; // Index variable for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    // Allocate memory for creating V subsets
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it in result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the contents of result[] to display the MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

// Driver program to test above functions
int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    Graph* graph = createGraph(V, E);

    // Add edges
    graph->edges[0] = (Edge){0, 1, 10};
    graph->edges[1] = (Edge){0, 2, 6};
    graph->edges[2] = (Edge){0, 3, 5};
    graph->edges[3] = (Edge){1, 3, 15};
    graph->edges[4] = (Edge){2, 3, 4};

    KruskalMST(graph);

    free(graph);
    return 0;
}