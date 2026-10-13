#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node* NODE;
NODE top = NULL;

NODE createNode (int data) {
    NODE newNode = malloc (sizeof (struct Node));
    if (newNode == NULL) {
        printf("malloc failed for newNode.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push (int data) {
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        printf("Push operation failed.\n");
        return;
    }
    newNode->next = top;
    top = newNode;
    printf("%d pushed to stack.\n", top->data);
}

void pop (void) {
    if (top == NULL) {
        printf("Stack underflow.\n");
        return;
    }
    NODE temp = top;
    printf("Popped element: %d\n", temp->data);
    top = top->next;
    free(temp);
}

void peek (void) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Top element: %d\n", top->data);
}

void isEmpty (void) {
    if (top == NULL) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack is not empty.\n");
    }
}

void display (void) {
    NODE temp = top;
    if (temp == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (top to bottom): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeStack (void) {
    NODE temp = NULL;
    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}

void displayMenu (void) {
    printf("Stacks\n1. Push\n2. Pop\n3. Peek\n4. isEmpty\n5. Display\n0. Exit\nEnter choice: ");
}

int main (void) {
    int choice, value;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }
        switch (choice) {
            case 1: {
                printf("Enter item to push: ");
                scanf("%d", &value);
                push(value);
                break;
            }
            case 2: {
                pop();
                break;
            }
            case 3: {
                peek();
                break;
            }
            case 4: {
                isEmpty();
                break;
            }
            case 5: {
                display();
                break;
            }
            case 0: {
                freeStack();
                printf("Exiting...");
                break;
            }
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
    freeStack();
    return 0;
}