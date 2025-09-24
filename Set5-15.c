#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Adjacency list representation
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

Node* adj[MAX_VERTICES];
int V;

// Function to add an edge to an undirected graph
void addEdge(int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = adj[src];
    adj[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = src;
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

// A BFS based function to find the length of the shortest cycle
// This is the most efficient way to find the smallest cycle (girth)
int findSmallestCycle() {
    int min_cycle = INT_MAX;
    int dist[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[j] = -1;
            parent[j] = -1;
        }

        int queue[V];
        int front = 0, rear = 0;

        dist[i] = 0;
        queue[rear++] = i;

        while (front < rear) {
            int u = queue[front++];

            Node* temp = adj[u];
            while (temp) {
                int v = temp->dest;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    queue[rear++] = v;
                } else if (parent[u] != v) {
                    // We found a cycle. Calculate its length.
                    int cycle_len = dist[u] + dist[v] + 1;
                    if (cycle_len < min_cycle) {
                        min_cycle = cycle_len;
                    }
                }
                temp = temp->next;
            }
        }
    }
    return (min_cycle == INT_MAX) ? 0 : min_cycle;
}

// A recursive function for finding the longest cycle using brute-force DFS.
// WARNING: This is computationally expensive and not suitable for large graphs.
void findLongestCycleUtil(int u, int start_node, int visited[], int current_path_len, int* max_cycle) {
    visited[u] = 1;

    Node* temp = adj[u];
    while (temp) {
        int v = temp->dest;
        if (v == start_node && current_path_len > 1) {
            // Found a cycle
            if (current_path_len < *max_cycle) {
                *max_cycle = current_path_len;
            }
        }
        if (!visited[v]) {
            findLongestCycleUtil(v, start_node, visited, current_path_len + 1, max_cycle);
        }
        temp = temp->next;
    }
    visited[u] = 0; // Backtrack
}

int findLargestCycle() {
    int max_cycle = 0;
    int visited[V];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            visited[j] = 0;
        }
        findLongestCycleUtil(i, i, visited, 0, &max_cycle);
    }
    return max_cycle;
}


int main() {
    V = 6;
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(2, 4);
    addEdge(3, 5);
    addEdge(4, 5);

    int smallest = findSmallestCycle();
    if (smallest) {
        printf("Length of the smallest cycle: %d\n", smallest);
    } else {
        printf("No cycles found.\n");
    }

    int largest = findLargestCycle();
    if (largest) {
        printf("Length of the largest cycle: %d\n", largest);
    } else {
        printf("No cycles found.\n");
    }

    return 0;
}