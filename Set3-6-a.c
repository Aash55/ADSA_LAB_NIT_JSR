#include <stdio.h>
#define SIZE 5

int queue[SIZE], front = -1, rear = -1;

void enqueue(int value) {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1))
        printf("Queue is full\n");
    else {
        if (front == -1)
            front = rear = 0;
        else if (rear == SIZE - 1)
            rear = 0;
        else
            rear++;
        queue[rear] = value;
        printf("Inserted %d\n", value);
    }
}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty\n");
        return;
    }
    printf("Deleted %d\n", queue[front]);
    if (front == rear)
        front = rear = -1;
    else if (front == SIZE - 1)
        front = 0;
    else
        front++;
}

void display() {
    if (front == -1) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display();
    dequeue();
    dequeue();
    display();
    enqueue(60);
    display();
    return 0;
}