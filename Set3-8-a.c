#include <stdio.h>
#define MAX 100

typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

void init(Queue *q) { q->front = q->rear = -1; }

int isEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, int x) {
    if (q->rear == MAX-1) return;
    if (isEmpty(q)) q->front = q->rear = 0;
    else q->rear++;
    q->data[q->rear] = x;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int ret = q->data[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return ret;
}

// Stack using two queues
typedef struct {
    Queue q1, q2;
} Stack;

void sInit(Stack *s) { init(&s->q1); init(&s->q2); }

void push(Stack *s, int x) {
    enqueue(&s->q2, x);
    while (!isEmpty(&s->q1))
        enqueue(&s->q2, dequeue(&s->q1));
    // Swap q1 and q2 pointers
    Queue temp = s->q1; s->q1 = s->q2; s->q2 = temp;
}

int pop(Stack *s) {
    return dequeue(&s->q1);
}

int main() {
    Stack s; sInit(&s);
    push(&s, 10); push(&s, 20); push(&s, 30);
    printf("%d\n", pop(&s)); // 30
    printf("%d\n", pop(&s)); // 20
    return 0;
}