#include <stdio.h>

#define SIZE 5

struct Item {
    int data;
    int priority;
};

struct Item pq[SIZE];
int count = 0;

int isEmpty(void) {
    return count == 0;
}

int isFull(void) {
    return count == SIZE;
}

int enqueue(int data, int priority) {
    if (isFull()) {
        printf("Priority queue is full!\n");
        return 0;
    }
    pq[count].data = data;
    pq[count].priority = priority;
    count++;
    printf("Inserted successfully.\n");
    return 1;
}

int dequeue(int *value) {
    if (isEmpty()) {
        printf("Priority queue is empty!\n");
        return 0;
    }
    int best = 0;
    for (int i = 1; i < count; i++) {
        if (pq[i].priority < pq[best].priority) {
            best = i;
        }
    }
    *value = pq[best].data;
    for (int i = best; i < count - 1; i++) {
        pq[i] = pq[i + 1];
    }
    count--;
    return 1;
}

int peek(int *value) {
    if (isEmpty()) {
        return 0;
    }
    int best = 0;
    for (int i = 1; i < count; i++) {
        if (pq[i].priority < pq[best].priority) {
            best = i;
        }
    }
    *value = pq[best].data;
    return 1;
}

void display(void) {
    if (isEmpty()) {
        printf("Priority queue is empty.\n");
        return;
    }
    printf("Data\tPriority\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\n", pq[i].data, pq[i].priority);
    }
}

int main(void) {
    int choice, data, priority, value;
    while (1) {
        printf("\nArray Priority Queue\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            return 1;
        }
        switch (choice) {
            case 1:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    return 1;
                }
                printf("Enter priority (smaller = higher): ");
                if (scanf("%d", &priority) != 1) {
                    return 1;
                }
                enqueue(data, priority);
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
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
