#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

typedef struct Node* NODE;
NODE front = NULL, rear = NULL;

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(struct Node));
    if(newNode == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

int isEmpty() {
    return front == NULL;
}

int insertFront(int value) {
    NODE newNode = createNode(value);
    if(newNode == NULL) {
        return 0;
    }
    if(front == NULL) {
        front = rear = newNode;
    } else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }
    return 1;
}

int insertRear(int value) {
    NODE newNode = createNode(value);
    if(newNode == NULL) {
        return 0;
    }
    if(front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }
    return 1;
}

int deleteFront(int *value) {
    if(isEmpty()) {
        return 0;
    }
    NODE temp = front;
    *value = temp->data;
    if(front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
        front->prev = NULL;
    }
    free(temp);
    return 1;
}

int deleteRear(int *value) {
    if(isEmpty()) {
        return 0;
    }
    NODE temp = rear;
    *value = temp->data;
    if(front == rear) {
        front = rear = NULL;
    } else {
        rear = rear->prev;
        rear->next = NULL;
    }
    free(temp);
    return 1;
}

int getFront(int *value) {
    if(isEmpty()) {
        return 0;
    }
    *value = front->data;
    return 1;
}

int getRear(int *value) {
    if(isEmpty()) {
        return 0;
    }
    *value = rear->data;
    return 1;
}

void display() {
    NODE temp = front;
    if(isEmpty()) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque: ");
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeDeque() {
    NODE temp;
    while(front != NULL) {
        temp = front;
        front = front->next;
        free(temp);
    }
    rear = NULL;
}

int main() {
    int choice, value;
    while(1) {
        printf("Linked List-based Deque\n1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n5. Get Front\n6. Get Rear\n7. Display\n8. Exit\nEnter choice: ");
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
                if(deleteFront(&value)) {
                    printf("Deleted at front: %d\n", value);
                } else {
                    printf("Deque is empty.\n");
                }
                break;
            case 4:
                if(deleteRear(&value)) {
                    printf("Deleted at rear: %d\n", value);
                } else {
                    printf("Deque is empty.\n");
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
                freeDeque();
                return 0;
            default:
                printf("Invalid input.\n");
        }
    }
    return 0;
}