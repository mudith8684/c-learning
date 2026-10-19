#include <stdio.h>

#define SIZE 5

int deque[SIZE], front = -1, rear = -1;

int isEmpty() {
    return front == -1;
}

int isFull() {
    return (rear + 1) % SIZE == front;
}

int insertFront(int value) {
    if(isFull()) {
        printf("Deque is full.\n");
        return 0;
    }
    if(isEmpty()) {
        front = rear = 0;
    } else {
        front = (front - 1 + SIZE) % SIZE;
    }
    deque[front] = value;
    return 1;
}

int insertRear(int value) {
    if(isFull()) {
        printf("Deque is full.\n");
        return 0;
    }
    if(isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % SIZE;
    }
    deque[rear] = value;
    return 1;
}

int deleteFront(int *value) {
    if(isEmpty()) {
        printf("Deque is empty.\n");
        return 0;
    }
    *value = deque[front];
    if(front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
    return 1;
}

int deleteRear(int *value) {
    if(isEmpty()) {
        printf("Deque is empty.\n");
        return 0;
    }
    *value = deque[rear];
    if(front == rear) {
        front = rear = -1;
    } else {
        rear = (rear - 1 + SIZE) % SIZE;
    }
    return 1;
}

int getFront(int *value) {
    if(isEmpty()) {
        printf("Deque is empty.\n");
        return 0;
    }
    *value = deque[front];
    return 1;
}

int getRear(int *value) {
    if(isEmpty()) {
        printf("Deque is empty.\n");
        return 0;
    }
    *value = deque[rear];
    return 1;
}

void display() {
    if(isEmpty()) {
        printf("Deque is empty.\n");
        return;
    }
    int i = front;
    printf("Deque: ");
    while(1) {
        printf("%d ", deque[i]);
        if(i == rear) {
            break;
        }
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    int choice, value;
    while(1) {
        printf("Array-based double-ended queue\n1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n5. Get Front\n6. Get Rear\n7. Display\n8. Exit\nEnter choice: ");
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        switch(choice) {
            case 1:
            case 2: 
                printf("Enter value: ");
                if(scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }
                if(choice == 1) {
                    if(insertFront(value)) {
                        printf("Inserted at front.\n");
                    }
                } else {
                    if(insertRear(value)) {
                        printf("Inserted at rear.\n");
                    }
                }
                break;
            case 3:
            case 4:
                if(choice == 3) {
                    if(deleteFront(&value)) {
                        printf("Deleted from front: %d\n", value);
                    }
                } else {
                    if(deleteRear(&value)) {
                        printf("Deleted from rear: %d\n", value);
                    }
                }
                break;
            case 5:
                if(getFront(&value)) {
                    printf("Front: %d\n", value);
                } else {
                    printf("Deque is empty.\n");
                }
                break;
            case 6:
                if(getRear(&value)) {
                    printf("Rear: %d\n", value);
                } else {
                    printf("Deque is empty.\n");
                }
                break;
            case 7:
                display();
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid input.\n");
        }
    }
    return 0;
}