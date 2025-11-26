#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
int G[MAX][MAX];
int visited[MAX];

int tspNearestNeighbor(int start, int n) {
    int cost = 0, u = start, count = 1;
    visited[u] = 1;

    while (count < n) {
        int next = -1, min = 999999;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && G[u][v] < min) {
                min = G[u][v];
                next = v;
            }
        }
        cost += min;
        u = next;
        visited[u] = 1;
        count++;
    }

    cost += G[u][start]; // return to start
    return cost;
}

int main() {
    int sizes[] = {10, 20, 40, 60, 100};
    int i;

    printf("Size\tTime(ms)\n");

    for (i = 0; i < 5; i++) {
        int n = sizes[i];

        // Generate random graph
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                G[u][v] = (u == v) ? 0 : (rand() % 90 + 10);

        for (int k = 0; k < n; k++)
            visited[k] = 0;

        clock_t start = clock();
        tspNearestNeighbor(0, n);
        clock_t end = clock();

        double time_ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
        printf("%d\t%.4f\n", n, time_ms);
    }
    return 0;
}