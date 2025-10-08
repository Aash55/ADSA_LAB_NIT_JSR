#include <stdio.h>
#include <stdlib.h> // For NULL (though not strictly needed here)

// Define a large number to represent infinity (unreachable)
#define INF 99999

// Function to print the solution matrix
void printSolution(int **dist, int V) {
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("%7s", "INF");
            } else {
                printf("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }
}

// Implements the Floyd-Warshall algorithm
void floydWarshall(int **graph, int V) {
    // dist[][] will be the output matrix that will store the shortest distance
    // from i to j
    int **dist;

    // Allocate memory for the distance matrix
    dist = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        dist[i] = (int *)malloc(V * sizeof(int));
    }

    // Initialize the solution matrix same as the input graph matrix.
    // Or, we can say the initial shortest distances are based on direct edges.
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    /*
     * Main dynamic programming part:
     * Add all vertices one by one to the set of intermediate vertices.
     * k is the intermediate vertex being considered.
     */
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above source
            for (int j = 0; j < V; j++) {
                /*
                 * If vertex k is on the shortest path from i to j,
                 * then update the value of dist[i][j].
                 */
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist, V);

    // Free the dynamically allocated memory
    for (int i = 0; i < V; i++) {
        free(dist[i]);
    }
    free(dist);
}

// Driver code
int main() {
    // V is the number of vertices in the graph
    int V = 4;

    /*
     * Let's represent the graph as an adjacency matrix:
     *
     * (0) ---10---> (3)
     * |             ^
     * (3)           /
     * v           / (-5)
     * (1) <--(-4)-- (2)
     * |
     * (1)
     * v
     * (2)
     *
     * Matrix:
     * 0   1   2   3
     * 0: { 0, INF, INF, 10 }
     * 1: { 3,  0,   1, INF }
     * 2: {INF, -4,  0, INF }
     * 3: {INF, INF, -5, 0  }
     */

    // Allocate and initialize the graph matrix
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
    }

    // Hardcode the graph data (using INF for no direct edge)
    int graph_data[4][4] = {
        {0,   INF, INF, 10},
        {3,   0,   1,   INF},
        {INF, -4,  0,   INF},
        {INF, INF, -5,  0}
    };

    // Copy data to the dynamically allocated matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = graph_data[i][j];
        }
    }

    printf("Floyd-Warshall Algorithm for All-Pairs Shortest Path\n");
    floydWarshall(graph, V);

    // Free the graph memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}