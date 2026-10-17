#include <stdio.h>
#include <stdlib.h>

#define MAX 5
int front = -1, rear = -1, queue[MAX];

int isEmpty(void) {
    return (front == -1);
}

int isFull(void) {
    return (rear == MAX - 1);
}

void enqueue(int item) {
    if(isFull()) {
        printf("Queue is full.\n");
        return;
    }
    if(isEmpty()){
        front = 0;
    }
    queue[++rear] = item;
}

int dequeue(void) {
    if(isEmpty()) {
        printf("Queue is empty.\n");
        exit(1);
    }
    int item = queue[front];
    if(front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
    return item;
}

int peek() {
    if(isEmpty()) {
        printf("Queue is empty.\n");
        exit(1);
    }
    return queue[front];
}

void display(void) {
    if(isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue:\n");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main(void) {
    int choice, value;
    do {
        printf("Array-based linear queue\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n0. Exit\nEnter your choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        switch(choice) {
            case 1: {
                printf("Enter value: ");
                if(scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }
                enqueue(value);
                break;
            }
            case 2: {
                if(!isEmpty()) {
                    printf("Deleted: %d\n", dequeue());
                } else {
                    printf("Queue underflow.\n");
                }
                break;
            }
            case 3: {
                if(!isEmpty()) {
                    printf("Front element: %d\n", peek());
                } else {
                    printf("Queue underflow.\n");
                }
                break;
            }
            case 4: {
                display();
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                printf("Invalid choice.\n");
            }
        }
    } while (choice != 0);
    return 0;
}