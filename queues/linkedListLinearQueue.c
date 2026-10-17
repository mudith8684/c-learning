#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node* NODE;
NODE front = NULL;
NODE rear = NULL;

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(struct Node));
    if(newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(void) {
    return front == NULL;
}

void enqueue(int data) {
    NODE newNode = createNode(data);
    if(newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    if(front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue(void) {
    if(front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    NODE temp = front;
    printf("Element dequeued: %d\n", temp->data);
    front = front->next;
    if(front == NULL) {
        rear = NULL;
    }
    free(temp);
}

void peek(void) {
    if(front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Front element: %d\n", front->data);
}

void display(void) {
    NODE temp = front;
    if(temp == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeQueue(void) {
    while(front != NULL) {
        NODE temp = front;
        front = front->next;
        free(temp);
    }
    rear = NULL;
}

int main(void) {
    int choice, data;
    do {
        printf("Linked List Based Linear Queue\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n0. Exit\nEnter your choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        switch(choice) {
            case 1: {
                printf("Enter data to enqueue: ");
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
                printf("Exiting...");
                freeQueue();
                return 0;
            }
            default: {
                printf("Invalid input.\n");
            }
        }
    } while(choice != 0);
    freeQueue();
    return 0;
}