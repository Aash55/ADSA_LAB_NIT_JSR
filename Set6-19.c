#include <stdio.h>
#include <stdbool.h>

// Global variables for simplicity in a small example
int max_value = 0;
int max_weight;
int num_items;
int* weights;
int* values;

/*
*
 * @brief Backtracking function to solve the 0/1 Knapsack problem.
 * * @param index The current item index being considered (from 0 to num_items-1).
 * @param current_weight The total weight of items currently included in the knapsack.
 * @param current_value The total value of items currently included in the knapsack.
 */
void knapsack_backtracking(int index, int current_weight, int current_value) {
    // Base Case: All items have been considered
    if (index == num_items) {
        // Update the maximum value found so far
        if (current_value > max_value) {
            max_value = current_value;
        }
        return;
    }

    // Optimization/Pruning (Optional but good practice): 
    // If the current weight already exceeds the capacity, stop this path.
    // However, the main inclusion check below handles this naturally.
    // We keep this check simple to illustrate the core concept.

    // 1. **Inclusion Branch (Include the current item):**
    if (current_weight + weights[index] <= max_weight) {
        // If including the item is feasible
        knapsack_backtracking(
            index + 1,                              // Move to the next item
            current_weight + weights[index],        // Update weight
            current_value + values[index]           // Update value
        );
    }

    // 2. **Exclusion Branch (Exclude the current item):**
    // This branch is always feasible in terms of weight.
    knapsack_backtracking(
        index + 1,      // Move to the next item
        current_weight, // Weight remains unchanged
        current_value   // Value remains unchanged
    );
}

int main() {
    // --- Define Problem Instance ---
    int w[] = {10, 20, 30}; // Weights of items
    int v[] = {60, 100, 120}; // Values of items
    
    weights = w;
    values = v;
    max_weight = 50; // Knapsack capacity
    num_items = sizeof(w) / sizeof(w[0]);

    printf("--- 0/1 Knapsack Problem using Backtracking ---\n");
    printf("Knapsack Capacity: %d\n", max_weight);
    printf("Items (Weight, Value): ");
    for(int i = 0; i < num_items; i++) {
        printf("(%d, %d)%s", weights[i], values[i], (i == num_items - 1) ? "" : ", ");
    }
    printf("\n\n");

    // --- Start Backtracking ---
    // Start with the first item (index 0), current weight 0, and current value 0.
    knapsack_backtracking(0, 0, 0);

    // --- Output Result ---
    printf("Maximum Value achievable: %d\n", max_value);

    return 0;
}