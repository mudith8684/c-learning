#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

int isEmpty(void) {
    return front == -1;
}

int isFull(void) {
    return (rear + 1) % SIZE == front;
}

void enqueue(int data) {
    if(isFull()) {
        printf("Queue is full.\n");
        return;
    }
    if(isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % SIZE;
    }
    queue[rear] = data;
}

void dequeue(void) {
    if(isEmpty()) {
        printf("Queue is empty.\n");
        exit(1);
    }
    printf("Dequeued element: %d\n", queue[front]);
    if(front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
}

void peek(void) {
    if(isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Front element: %d\n", queue[front]);
}

void display(void) {
    if(isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    int i = front;
    while(1) {
        printf("%d ", queue[i]);
        if(i == rear) {
            break;
        }
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main(void) {
    int choice, data;
    do{
        printf("Array Based Circular Queue\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n0. Exit\nEnter your choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        switch(choice) {
            case 1: {
                printf("Enter element to enqueue: ");
                if(scanf("%d", &data) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }
                enqueue(data);
                break;
            }
            case 2: {
                dequeue();
                break;
            }
            case 3: {
                peek();
                break;
            }
            case 4: {
                display();
                break;
            }
            case 0: {
                printf("Exiting...\n");
                return 0;
            }
            default: {
                printf("Invalid input.\n");
            }
        }
    } while(choice != 0);
    return 0;
}