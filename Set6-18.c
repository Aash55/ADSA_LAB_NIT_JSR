#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
int knapsack(int W, int weights[], int values[], int n) {
    // dp[i][w] is the maximum value that can be attained 
    // with a knapsack capacity of w using first i items.
    int dp[n + 1][W + 1];

    // Build the dp table in a bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Base case: 
            // If no items (i=0) or no capacity (w=0), value is 0.
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } 
            // If the weight of the i-th item is less than or equal to current capacity w
            else if (weights[i - 1] <= w) {
                // max of (excluding the item) and (including the item)
                dp[i][w] = max(
                    dp[i - 1][w], // Exclude item i
                    values[i - 1] + dp[i - 1][w - weights[i - 1]] // Include item i
                );
            } 
            // If the weight of the i-th item is greater than the current capacity w
            else {
                // Must exclude the item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The result is stored at dp[n][W]
    return dp[n][W];
}

int main() {
    // Example Data
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int W = 50; // Knapsack capacity
    int n = sizeof(values) / sizeof(values[0]); // Number of items

    printf("Weights: {");
    for(int i = 0; i < n; i++) printf("%d%s", weights[i], i < n-1 ? ", " : "}\n");
    
    printf("Values: {");
    for(int i = 0; i < n; i++) printf("%d%s", values[i], i < n-1 ? ", " : "}\n");
    
    printf("Knapsack Capacity (W): %d\n", W);

    // Solve and print the result
    int max_value = knapsack(W, weights, values, n);
    printf("Maximum value in Knapsack: %d\n", max_value);

    return 0;
}