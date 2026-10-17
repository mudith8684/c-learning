#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node* NODE;
NODE rear = NULL;

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(struct Node));
    if(newNode == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(void) {
    return rear == NULL;
}

void enqueue(int data) {
    NODE newNode = createNode(data);
    if(newNode == NULL) {
        printf("malloc failed.\n");
        return;
    }
    if(rear == NULL) {
        rear = newNode;
        rear->next = newNode;
    } else {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue(void) {
    if(rear == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Dequeued element: %d\n", rear->next->data);
    NODE front = rear->next;
    if(front == rear) {
        rear = NULL;
    } else {
        rear->next = front->next;
    }
    free(front);
}

void peek(void) {
    if(rear == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Front element: %d\n", rear->next->data);
}

void display(void) {
    if(rear == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    NODE temp = rear->next;
    do{
        printf("%d ", temp->data);
        temp = temp->next;
    } while(temp != rear->next);
    printf("\n");
}

void freeQueue(void) {
    if(rear == NULL) {
        return;
    }
    NODE front = rear->next;
    rear->next = NULL;
    while(front != NULL) {
        NODE temp = front;
        front = front->next;
        free(temp);
    }
    rear = NULL;
}

int main(void) {
    int choice, data;
    do{
        printf("Linked List Based Circular Queue\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n0. Exit\nEnter your choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        switch(choice) {
            case 1: {
                printf("Enter element to be enqueued: ");
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
                freeQueue();
                return 0;
            }
        }
    } while(choice != 0);
    return 0;
}