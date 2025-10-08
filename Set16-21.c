#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Board size (3x3 for 8-puzzle)
#define N 3
#define BOARD_SIZE (N * N)
#define MAX_QUEUE_SIZE 10000 // Small size for demonstration

// Structure to represent a state of the puzzle
typedef struct Node {
    int board[BOARD_SIZE];
    int g; // Cost from start (depth)
    int h; // Heuristic cost (Manhattan distance)
    int f; // Total cost (f = g + h)
    struct Node* parent;
} Node;

// Simple structure to act as a Priority Queue (min-heap logic)
typedef struct PriorityQueue {
    Node* nodes[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue;

// Function Prototypes
int calculate_manhattan(int board[]);
int is_goal(int board[]);
Node* create_node(int board[], int g, int h, Node* parent);
void insert_pq(PriorityQueue* pq, Node* node);
Node* extract_min_pq(PriorityQueue* pq);
void print_board(int board[]);
void print_path(Node* goal_node);
void solve_puzzle(int initial_board[]);

// Directions for the blank space (row, col)
int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
int dc[] = {0, 0, -1, 1};

//---------------------------------------------------------
// Heuristic Function: Manhattan Distance
//---------------------------------------------------------
int calculate_manhattan(int board[]) {
    int h = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == 0) continue; // Skip the blank space
        
        int value = board[i] - 1; // Expected position (0-indexed)
        
        // Current (r, c)
        int cur_r = i / N;
        int cur_c = i % N;
        
        // Target (r, c)
        int target_r = value / N;
        int target_c = value % N;
        
        h += abs(cur_r - target_r) + abs(cur_c - target_c);
    }
    return h;
}

//---------------------------------------------------------
// Goal Check
//---------------------------------------------------------
int is_goal(int board[]) {
    // Goal state is 1, 2, 3, ..., 8, 0
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        if (board[i] != i + 1) {
            return 0;
        }
    }
    // Check last tile is 0
    if (board[BOARD_SIZE - 1] != 0) {
        return 0;
    }
    return 1;
}

//---------------------------------------------------------
// Node Management
//---------------------------------------------------------
Node* create_node(int board[], int g, int h, Node* parent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    memcpy(new_node->board, board, sizeof(int) * BOARD_SIZE);
    new_node->g = g;
    new_node->h = h;
    new_node->f = g + h;
    new_node->parent = parent;
    return new_node;
}

//---------------------------------------------------------
// Priority Queue Operations (Simplified)
//---------------------------------------------------------
void insert_pq(PriorityQueue* pq, Node* node) {
    if (pq->size >= MAX_QUEUE_SIZE) {
        // In a real implementation, you'd handle this better (e.g., resizing)
        return; 
    }
    pq->nodes[pq->size++] = node;
    // For simplicity, we don't fully heapify on insert.
    // Instead, we search for the minimum on extraction.
}

Node* extract_min_pq(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL;
    }

    int min_f = pq->nodes[0]->f;
    int min_index = 0;

    // Find the node with the minimum f-value
    for (int i = 1; i < pq->size; i++) {
        if (pq->nodes[i]->f < min_f) {
            min_f = pq->nodes[i]->f;
            min_index = i;
        }
    }

    // Extract the node
    Node* min_node = pq->nodes[min_index];

    // Replace extracted node with the last node
    pq->nodes[min_index] = pq->nodes[pq->size - 1];
    pq->size--;

    return min_node;
}

//---------------------------------------------------------
// Output Functions
//---------------------------------------------------------
void print_board(int board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i % N == 0) printf("\n");
        if (board[i] == 0) {
            printf(" . "); // Blank space
        } else {
            printf("%2d ", board[i]);
        }
    }
    printf("\n");
}

void print_path(Node* goal_node) {
    if (goal_node == NULL) return;
    print_path(goal_node->parent);
    
    printf("--- Step (g=%d, f=%d) ---\n", goal_node->g, goal_node->f);
    print_board(goal_node->board);
}

//---------------------------------------------------------
// Branch and Bound (A*) Core Logic
//---------------------------------------------------------
void solve_puzzle(int initial_board[]) {
    PriorityQueue pq = { .size = 0 };
    
    Node* initial_node = create_node(initial_board, 0, calculate_manhattan(initial_board), NULL);
    insert_pq(&pq, initial_node);
    
    Node* current_node = NULL;
    int nodes_explored = 0;

    printf("Starting Board:\n");
    print_board(initial_board);

    while (pq.size > 0) {
        current_node = extract_min_pq(&pq);
        nodes_explored++;
        
        // Check for goal
        if (is_goal(current_node->board)) {
            printf("\n🎉 Solution Found! 🎉\n");
            printf("Total Steps: %d\n", current_node->g);
            printf("Nodes Explored: %d\n", nodes_explored);
            printf("Path to Goal:\n");
            print_path(current_node);
            return;
        }

        // Branching: Find the blank tile (0)
        int zero_idx;
        for (zero_idx = 0; zero_idx < BOARD_SIZE; zero_idx++) {
            if (current_node->board[zero_idx] == 0) break;
        }

        int zero_r = zero_idx / N;
        int zero_c = zero_idx % N;

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int new_r = zero_r + dr[i];
            int new_c = zero_c + dc[i];
            
            // Check bounds
            if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < N) {
                int new_idx = new_r * N + new_c;
                
                // Create new board state (the 'branch')
                int new_board[BOARD_SIZE];
                memcpy(new_board, current_node->board, sizeof(int) * BOARD_SIZE);
                
                // Swap the blank tile and the neighbor tile (the 'move')
                new_board[zero_idx] = new_board[new_idx];
                new_board[new_idx] = 0;
                
                // Create a new node (the 'bound' part is enforced by g+h)
                int new_g = current_node->g + 1;
                int new_h = calculate_manhattan(new_board);
                Node* next_node = create_node(new_board, new_g, new_h, current_node);
                
                // Add to the priority queue (frontier)
                insert_pq(&pq, next_node);
            }
        }
        // In a proper implementation, you'd also check for repeated states (visited set)
    }

    printf("\nSolution not found within limits (queue size).\n");
}

//---------------------------------------------------------
// Main Function
//---------------------------------------------------------
int main() {
    // Solvable 8-puzzle example (3x3)
    int initial_board[] = {1, 2, 3, 
                           4, 0, 6, 
                           7, 5, 8}; // Easy to solve in a few steps

    // The full 15-puzzle would use N=4 and a 16-element array, 
    // requiring a much more robust and efficient implementation.
    
    solve_puzzle(initial_board);
    
    // Note: Freeing memory for all allocated nodes is omitted 
    // for brevity but is essential in real-world C programs.

    return 0;
}