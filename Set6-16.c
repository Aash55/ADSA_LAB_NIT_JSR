#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a weighted edge in graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a graph
struct Graph {
    int V, E;          // V-> Number of vertices, E-> Number of edges
    struct Edge* edge;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// A utility function used to print the solution
void printArr(int dist[], int V) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t INFINITY\n", i);
        else
            printf("%d \t\t %d\n", i, dist[i]);
    }
}

// The main function that finds shortest distances from src to all other
// vertices using Bellman-Ford algorithm. It also detects negative weight cycles.
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    
    // FIX: Use graph->E to get the number of edges, not graph->edge (the pointer)
    int E = graph->E; 
    
    int *dist = (int*)malloc(V * sizeof(int));

    // Step 1: Initialization
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relaxation (V - 1 iterations)
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            
            // Relaxation step:
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles (V-th iteration)
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("\nGraph contains negative weight cycle! Shortest paths are not well-defined.\n");
            free(dist);
            return;
        }
    }

    // Print the shortest distances
    printArr(dist, V);
    free(dist);
    return;
}

// Driver program to test the function
int main() {
    // Example Graph: 5 vertices (0-4) and 8 edges
    int V = 5;
    int E = 8;
    int source_vertex = 0; // Starting node

    struct Graph* graph = createGraph(V, E);

    // Edge data: {src, dest, weight}
    graph->edge[0] = (struct Edge){0, 1, -1};
    graph->edge[1] = (struct Edge){0, 2, 4};
    graph->edge[2] = (struct Edge){1, 2, 3};
    graph->edge[3] = (struct Edge){1, 3, 2};
    graph->edge[4] = (struct Edge){1, 4, 2};
    graph->edge[5] = (struct Edge){3, 2, 5};
    graph->edge[6] = (struct Edge){3, 1, 1};
    graph->edge[7] = (struct Edge){4, 3, -3}; // This is what creates the change in distances

    printf("Bellman-Ford Algorithm starting from Vertex %d:\n", source_vertex);
    BellmanFord(graph, source_vertex);
    
    // Free the dynamically allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}