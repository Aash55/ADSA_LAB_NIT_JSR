#include <stdio.h>
#include <math.h>
#include <stdlib.h> // For abs() in some compilers, though math.h is standard for abs() of floats.

// Global array to store the column position of the queen in each row.
// board[i] = j means queen in row 'i' is in column 'j'.
// Max size is set to 20 for convenience, but N is user-defined.
int board[20];
int count; // To keep track of the number of solutions found

// Function to print the solution board
void print_solution(int n) {
    int i, j;
    printf("\n\nSolution %d:\n", ++count);

    // Print column headers
    for (i = 1; i <= n; ++i) {
        printf("\t%d", i);
    }
    
    // Print the board
    for (i = 1; i <= n; ++i) {
        printf("\n%d", i); // Print row number
        for (j = 1; j <= n; ++j) {
            // Check if a queen is placed in this cell
            if (board[i] == j) {
                printf("\tQ");
            } else {
                printf("\t-");
            }
        }
    }
    printf("\n");
}

// Function to check if a queen can be safely placed at board[row] = column
// We only check against queens in previous rows (1 to row-1)
int is_safe(int row, int column) {
    int i;
    for (i = 1; i <= row - 1; ++i) {
        // Check column conflict: queen in a previous row 'i' is in the same column 'column'
        if (board[i] == column) {
            return 0;
        }
        // Check diagonal conflict: |board[i] - column| == |i - row|
        // The difference in row indices equals the difference in column indices
        else if (abs(board[i] - column) == abs(i - row)) {
            return 0;
        }
    }
    // No conflicts found
    return 1;
}

// Backtracking function to place queens
// Starts trying to place a queen in the current 'row'
void solve_nqueens(int row, int n) {
    int column;
    
    // Iterate through all columns in the current row
    for (column = 1; column <= n; ++column) {
        // Check if placing a queen in this position is safe
        if (is_safe(row, column)) {
            // Place the queen (tentative solution)
            board[row] = column;

            // Base case: If all queens are placed (last row reached)
            if (row == n) {
                print_solution(n);
            } 
            // Recursive step: Try to place the next queen in the next row
            else {
                solve_nqueens(row + 1, n);
            }
            // No need to explicitly 'backtrack' (board[row]=0). 
            // When returning from the recursive call, the loop continues to the next 
            // 'column', effectively removing the queen from the current 'column' 
            // for the current 'row' in the next iteration. The old value of board[row] 
            // is overwritten or forgotten in the recursive call's stack frame.
        }
    }
}

int main() {
    int n;
    printf("- N-Queens Problem Using Backtracking -\n");
    printf("\nEnter the number of Queens (N): ");
    scanf("%d", &n);

    if (n < 4 && n != 1) {
        printf("\nNo solution exists for N=%d.", n);
        return 0;
    }

    solve_nqueens(1, n); // Start from row 1 (1-based indexing for simplicity)
    
    if (count == 0) {
        printf("\nNo solution exists for N=%d.", n);
    } else {
        printf("\n\nTotal solutions found: %d\n", count);
    }

    return 0;
}