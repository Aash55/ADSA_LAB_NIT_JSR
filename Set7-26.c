#include <stdio.h>

#define MAX 100

int adj[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;

void topoDFS(int u, int V) {
    visited[u] = 1;

    for (int v = 0; v < V; v++) {
        if (adj[u][v] && !visited[v]) {
            topoDFS(v, V);
        }
    }
    stack[++top] = u;
}

void topologicalSort(int V) {
    for (int i = 0; i < V; i++)
        if (!visited[i])
            topoDFS(i, V);

    printf("Topological Order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;   // directed edge
    }

    topologicalSort(V);
    return 0;
}