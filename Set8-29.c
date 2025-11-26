#include <stdio.h>

#define MAX 20

int G[MAX][MAX];
int path[MAX];
int n;

// Check if we can add vertex v at position pos
int isSafe(int v, int pos) {
    // Must be adjacent to previous vertex
    if (!G[path[pos - 1]][v])
        return 0;

    // Vertex must not be repeated
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

// Try to construct Hamiltonian cycle
int hamCycleUtil(int pos) {
    if (pos == n) {
        // Last vertex must connect to start
        return G[path[pos - 1]][path[0]];
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycleUtil(pos + 1))
                return 1;
        }
    }
    return 0; // No option works
}

// Driver
int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }

    // Start cycle with vertex 0
    path[0] = 0;

    if (hamCycleUtil(1)) {
        printf("Hamiltonian Cycle Exists: ");
        for (int i = 0; i < n; i++)
            printf("%d -> ", path[i]);
        printf("%d\n", path[0]); // complete the cycle
    } else {
        printf("No Hamiltonian Cycle Exists.\n");
    }

    return 0;
}