#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

struct stack{
    int top;
   char array[MAX_SIZE];
};

void initializeStack(struct stack* stack){
    stack->top=-1;
}

int isEmpty(struct stack* stack){
    return stack->top ==-1;
}

void push(struct stack* stack,char item) {
    if (stack->top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

char pop(struct stack* stack) {
    if (isEmpty(stack)) {
        return '\0'; // Return null character for underflow
    }
    return stack->array[stack->top--];
}

char peek(struct stack* stack) {
    if (isEmpty(stack)) {
        return '\0';
    }
    return stack->array[stack->top];
}

// Function to get precedence of operators
int precedence(char op) {
    
    if(op=='+'||op=='-')
    return 1;
    if(op=='*'||op=='/')
    return 2;
    return 0;
}

void infixtopostfix(char* infix, char* postfix){
struct stack stack;

initializeStack(&stack);

int i = 0,j=0; 

while (infix[i] != '\0'){
    char symbol = infix[i];

if(isdigit (symbol) ||  isalpha(symbol)){

postfix[j++] = symbol;

 } else if(symbol == '('){

push(&stack, symbol);

  } else if( symbol == ')'){

while(!isEmpty(&stack) && peek(&stack) != '(') { 
    postfix[j++] = pop(&stack);

}

if ( !isEmpty (&stack ) && peek (&stack) == '('){
     pop(&stack);

}
} else {

while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(symbol)){

postfix[j++] = pop(&stack);

}
push(&stack, symbol);
}

i++;

}
while(!isEmpty(&stack)){
    postfix[j++] = pop(&stack);
}
postfix[j]='\0';
}

int main(){
    char infix[MAX_SIZE] = "(3+4)*5-6/2";
    char postfix[MAX_SIZE];

printf("\nInfix expression: %s \n",infix);

infixtopostfix(infix,postfix);

printf("postfix epression : %s \n",postfix);

return 0;
}