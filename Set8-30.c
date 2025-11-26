#include <stdio.h>

#define MAX 100

int G[MAX][MAX];
int color[MAX];   // -1 = uncolored, 0/1 = two colors
int n;

// BFS check from a starting node
int isBipartite(int start) {
    int queue[MAX], front = 0, rear = 0;

    color[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < n; v++) {
            if (G[u][v]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                }
                else if (color[v] == color[u]) {
                    return 0;  // conflict
                }
            }
        }
    }
    return 1;
}

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

    // Initialize all nodes as uncolored
    for (int i = 0; i < n; i++)
        color[i] = -1;

    // Check all components
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!isBipartite(i)) {
                printf("Graph is NOT Bipartite.\n");
                return 0;
            }
        }
    }

    printf("Graph IS Bipartite.\n");
    return 0;
}