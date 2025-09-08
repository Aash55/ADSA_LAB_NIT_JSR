#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

void enqueue(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (front == NULL) {
        front = rear = newNode;
        rear->next = front;
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
    printf("Inserted %d\n", value);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    if (front == rear) {
        printf("Deleted %d\n", front->data);
        free(front);
        front = rear = NULL;
    } else {
        struct Node *temp = front;
        printf("Deleted %d\n", temp->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void display() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    struct Node *temp = front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(11);
    enqueue(22);
    enqueue(33);
    display();
    dequeue();
    display();
    enqueue(44);
    enqueue(55);
    dequeue();
    display();
    return 0;
}
