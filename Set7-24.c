#include <stdio.h>
#include <stdbool.h>

// --- Configuration ---
#define V 4 // Number of vertices in the graph (e.g., 4)
#define M 3 // Maximum number of colors allowed (e.g., 3: Red, Green, Blue)

// Define the graph using an adjacency matrix
// Adj[i][j] = 1 if there is an edge between vertex i and j, 0 otherwise.
int graph[V][V] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}
};
// Graph structure: 0-1, 0-2, 0-3, 1-2, 2-3

// Array to store the resulting color of each vertex (1 to M)
int color[V];

// --- Utility Function: Check if a color is safe for a vertex ---
// Checks if color 'c' can be assigned to vertex 'v'
bool isSafe(int v, int c) {
    // Iterate over all other vertices 'i'
    for (int i = 0; i < V; i++) {
        // Check 1: Is there an edge between 'v' and 'i'? (graph[v][i] == 1)
        // Check 2: Is vertex 'i' already colored with 'c'? (color[i] == c)
        if (graph[v][i] && color[i] == c) {
            return false; // Not safe, adjacent vertex has the same color
        }
    }
    return true; // Safe to assign color 'c'
}

// --- Backtracking Function: The core of the solution ---
// 'v' is the current vertex being colored (starting from 0)
bool graphColoringUtil(int v) {
    // Base Case: If all vertices are colored, we found a solution.
    if (v == V) {
        return true;
    }

    // Try assigning all possible colors (from 1 to M) to vertex 'v'
    for (int c = 1; c <= M; c++) {
        // Check if the color 'c' is safe to assign to vertex 'v'
        if (isSafe(v, c)) {
            // 1. **Choose**: Assign the color
            color[v] = c;

            // 2. **Explore**: Recur for the next vertex (v + 1)
            if (graphColoringUtil(v + 1)) {
                return true; // If the recursive call succeeds, propagate success
            }

            // 3. **Unchoose (Backtrack)**: If assigning 'c' didn't lead to a solution, 
            // reset the color (or let the next iteration override it).
            // Backtracking happens implicitly by the loop moving to the next color 'c'.
            // Setting color[v] = 0 is a common explicit backtrack step, but often unnecessary
            // as the function explores all possibilities.
            color[v] = 0; 
        }
    }

    // If no color from 1 to M can be assigned to vertex 'v', return false
    // to trigger backtracking in the previous recursive call.
    return false;
}

// --- Main Function: Start the coloring process ---
void graphColoring() {
    // Initialize all colors to 0 (uncolored)
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    printf("--- Graph Coloring Problem (Backtracking) ---\n");
    printf("Vertices (V): %d, Max Colors (M): %d\n\n", V, M);

    if (graphColoringUtil(0) == true) {
        printf("Solution Found:\n");
        printf("Vertex Coloring (1=Red, 2=Green, 3=Blue):\n");
        for (int i = 0; i < V; i++) {
            printf("Vertex %d ---> Color %d\n", i, color[i]);
        }
    } else {
        printf("Solution Does NOT Exist for M=%d colors.\n", M);
    }
}

int main() {
    graphColoring();
    return 0;
}