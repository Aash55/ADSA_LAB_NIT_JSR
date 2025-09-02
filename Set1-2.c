#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stacks for operands and operators
int operandStack[MAX_SIZE];
char operatorStack[MAX_SIZE];
int topOperand = -1;
int topOperator = -1;

// Stack operations
void pushOperand(int value) {
    operandStack[++topOperand] = value;
}

int popOperand() {
    if (topOperand < 0) return 0;
    return operandStack[topOperand--];
}

void pushOperator(char op) {
    operatorStack[++topOperator] = op;
}

char popOperator() {
    if (topOperator < 0) return '\0';
    return operatorStack[topOperator--];
}

char peekOperator() {
    if (topOperator < 0) return '\0';
    return operatorStack[topOperator];
}

// Function to get precedence of operators
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to perform a single operation
void applyOperation() {
    char op = popOperator();
    int right = popOperand();
    int left = popOperand();
    int result;

    switch (op) {
        case '+':
            result = left + right;
            break;
        case '-':
            result = left - right;
            break;
        case '*':
            result = left * right;
            break;
        case '/':
            // Basic error handling for division by zero
            if (right == 0) {
                printf("Error: Division by zero\n");
                exit(1);
            }
            result = left / right;
            break;
    }
    pushOperand(result);
}

// Function to evaluate the expression
int evaluateExpression(char* expression) {
    int i;
    for (i = 0; expression[i] != '\0'; i++) {
        char current_char = expression[i];

        if (isspace(current_char)) {
            continue;
        } else if (isdigit(current_char)) {
            int value = 0;
            while (isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Decrement to handle the outer loop's increment
            pushOperand(value);
        } else if (current_char == '(') {
            pushOperator(current_char);
        } else if (current_char == ')') {
            while (topOperator >= 0 && peekOperator() != '(') {
                applyOperation();
            }
            if (topOperator >= 0 && peekOperator() == '(') {
                popOperator(); // Pop the '('
            }
        } else { // Operator
            while (topOperator >= 0 && precedence(peekOperator()) >= precedence(current_char)) {
                applyOperation();
            }
            pushOperator(current_char);
        }
    }

    // Apply remaining operations
    while (topOperator >= 0) {
        applyOperation();
    }

    return popOperand();
}

int main(int argc, char *argv[]) {
    // Check if an expression is provided as a command-line argument
    if (argc < 2) {
        printf("Usage: %s \"<expression>\"\n", argv[0]);
        printf("Example: %s \"(23 - 8) * 3 + 28 / 4\"\n", argv[0]);
        return 1;
    }

    int result = evaluateExpression(argv[1]);
    printf("Result: %d\n", result);

    return 0;
}