#include <stdio.h>

// Function to implement the greedy coin changing algorithm
void findMinCoins(int amount) {
    // Array of standard coin denominations (sorted from largest to smallest)
    int coins[] = {100, 50, 25, 10, 5, 1}; // e.g., $1, 50c, 25c, 10c, 5c, 1c
    int num_denominations = sizeof(coins) / sizeof(coins[0]);
    int i;
    int count;

    printf("To make change for %d cents, the minimum coins needed are:\n", amount);

    // Iterate through the coin denominations
    for (i = 0; i < num_denominations; i++) {
        // While the current coin denomination is less than or equal to the remaining amount
        while (amount >= coins[i]) {
            count = 0; // Reset count for the current coin
            // Find how many of the current coin fit into the remaining amount
            count = amount / coins[i];

            // Print the result for this coin
            printf("- Use %d x %d cent coin(s)\n", count, coins[i]);

            // Update the remaining amount (modulo operation gives the remainder)
            amount = amount % coins[i];

            // Move to the next coin (smaller denomination)
            // The inner while loop logic ensures we take the maximum number of the current coin
            // before moving to the next one, but the outer for loop handles the iteration.
            // We break out of the inner while loop to let the for loop continue.
            break; 
        }
    }
    
    if (amount > 0) {
        printf("\nNote: Could not make exact change. Remaining amount: %d\n", amount);
    }
}

// Main function to test the implementation
int main() {
    int target_amount = 93; // Example: 93 cents
    
    // Test case 1
    printf("--- Test Case 1 ---\n");
    findMinCoins(target_amount);
    
    printf("\n--- Test Case 2 ---\n");
    findMinCoins(145); // Example: $1.45
    
    return 0;
}