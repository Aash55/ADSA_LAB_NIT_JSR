#include <stdio.h>
#define SIZE 100

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

void push1(int x) {
     stack1[++top1] = x;
     }

int pop1() {
     return stack1[top1--];
     }

void push2(int x) {
     stack2[++top2] = x;
     }
     
int pop2() {
     return stack2[top2--];
     }

// Costly push (enqueue)
void enqueue(int x) {
    while (top1 != -1)
        push2(pop1());
    push1(x);
    while (top2 != -1)
        push1(pop2());
}

// Simple pop (dequeue)
int dequeue() {
    if (top1 == -1) return -1;
    return pop1();
}

int main() {
    enqueue(10); 
    enqueue(20); 
    enqueue(30);
    printf("%d ", dequeue()); // 10
    enqueue(40);
    printf("%d ", dequeue()); // 20
    printf("%d\n", dequeue()); // 30
    return 0;
}