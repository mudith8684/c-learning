#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node *next;
};

typedef struct Node *NODE;

NODE front = NULL;

NODE createNode(int data, int priority) {
    NODE newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(void) {
    return front == NULL;
}

int enqueue(int data, int priority) {
    NODE newNode = createNode(data, priority);
    if (newNode == NULL) {
        return 0;
    }
    if (front == NULL || priority < front->priority) {
        newNode->next = front;
        front = newNode;
    } else {
        NODE temp = front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    return 1;
}

int dequeue(int *value) {
    if (isEmpty()) {
        printf("Priority queue is empty.\n");
        return 0;
    }
    NODE temp = front;
    *value = temp->data;
    front = front->next;
    free(temp);
    return 1;
}

int peek(int *value) {
    if (isEmpty()) {
        return 0;
    }
    *value = front->data;
    return 1;
}

void display(void) {
    NODE temp = front;
    if (isEmpty()) {
        printf("Priority queue is empty.\n");
        return;
    }
    printf("Data\tPriority\n");
    while (temp != NULL) {
        printf("%d\t%d\n", temp->data, temp->priority);
        temp = temp->next;
    }
}

void freeQueue(void) {
    while (front != NULL) {
        NODE temp = front;
        front = front->next;
        free(temp);
    }
}

int main(void) {
    int choice, data, priority, value;
    while (1) {
        printf("\nLinked List Priority Queue\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            freeQueue();
            return 1;
        }
        switch (choice) {
            case 1:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    freeQueue();
                    return 1;
                }
                printf("Enter priority (smaller = higher): ");
                if (scanf("%d", &priority) != 1) {
                    freeQueue();
                    return 1;
                }
                if (enqueue(data, priority)) {
                    printf("Inserted successfully.\n");
                }
                break;
            case 2:
                if (dequeue(&value)) {
                    printf("Removed: %d\n", value);
                }
                break;
            case 3:
                if (peek(&value)) {
                    printf("Highest-priority element: %d\n", value);
                } else {
                    printf("Priority queue is empty.\n");
                }
                break;
            case 4:
                display();
                break;
            case 5:
                freeQueue();
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    freeQueue();
    return 0;
}