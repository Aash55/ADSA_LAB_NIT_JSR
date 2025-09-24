#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Adjacency list representation
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* adj[MAX_VERTICES];
int visited[MAX_VERTICES];
int arrival_time[MAX_VERTICES];
int departure_time[MAX_VERTICES];
int time;

// Function to add an edge to the graph
void addEdge(int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = dest;
    newNode->next = adj[src];
    adj[src] = newNode;
}

// DFS function to traverse the graph and classify edges
void DFS(int u) {
    visited[u] = 1;
    arrival_time[u] = ++time;

    Node* temp = adj[u];
    while (temp) {
        int v = temp->data;

        if (!visited[v]) {
            printf("Edge (%d, %d) is a Tree Edge\n", u, v);
            DFS(v);
        } else {
            // Check for back, forward, and cross edges based on arrival/departure times
            if (arrival_time[v] < arrival_time[u] && departure_time[v] == 0) {
                printf("Edge (%d, %d) is a Back Edge\n", u, v);
            } else if (arrival_time[v] > arrival_time[u] && departure_time[v] != 0) {
                printf("Edge (%d, %d) is a Forward Edge\n", u, v);
            } else if (arrival_time[v] < arrival_time[u] && departure_time[v] != 0) {
                printf("Edge (%d, %d) is a Cross Edge\n", u, v);
            }
        }
        temp = temp->next;
    }
    departure_time[u] = ++time;
}

// Driver program to test the DFS function
int main() {
    int V = 6; // Number of vertices
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
        visited[i] = 0;
        arrival_time[i] = 0;
        departure_time[i] = 0;
    }
    time = 0;

    // Add edges to create a sample graph
    // Note: The graph is directed
    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 4);
    addEdge(3, 1); // Back edge
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(5, 2); // Cross edge

    // Start DFS from vertex 0
    printf("Starting DFS from vertex 0...\n");
    DFS(0);

    return 0;
}