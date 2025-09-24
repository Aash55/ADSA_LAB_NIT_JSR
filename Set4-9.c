#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Define a structure for a stack node
typedef struct StackNode {
    Node *treeNode;
    struct StackNode *next;
} StackNode;

// Function to create a new tree node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to push a tree node onto the stack
void push(StackNode** top, Node* treeNode) {
    StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
    newStackNode->treeNode = treeNode;
    newStackNode->next = *top;
    *top = newStackNode;
}

// Function to pop a tree node from the stack
Node* pop(StackNode** top) {
    if (*top == NULL) {
        return NULL;
    }
    StackNode* temp = *top;
    Node* poppedNode = temp->treeNode;
    *top = temp->next;
    free(temp);
    return poppedNode;
}

// Function to check if the stack is empty
int isStackEmpty(StackNode* top) {
    return (top == NULL);
}

// Function to perform iterative preorder traversal
void preorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    StackNode* stack = NULL;
    push(&stack, root);

    while (!isStackEmpty(stack)) {
        Node* current = pop(&stack);
        printf("%d ", current->data);

        // Push right child first, then left child
        if (current->right) {
            push(&stack, current->right);
        }
        if (current->left) {
            push(&stack, current->left);
        }
    }
}

// Main function to demonstrate the traversal
int main() {
    // Create the binary tree
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Preorder traversal of the binary tree is: \n");
    preorderTraversal(root); // Outputs: 1 2 4 5 3
    printf("\n");

    return 0;
}