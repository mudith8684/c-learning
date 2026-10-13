#include <stdio.h>

#define MAX 1024

int stack[MAX];
int top = -1;

void push (int data) {
    if (top == MAX - 1) {
        printf("Stack is full.\n");
    } else {
        stack[++top] = data;
        printf("%d pushed to stack.\n", data);
    }
}

int pop (void) {
    if (top == -1) {
        printf("Stack underflow.\n");
    } else {
        --top;
        printf("Popped: %d\n", stack[top]);
    }
}

void peek (void) {
    if (top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Top element is: %d.\n", stack[top]);
    }
}

void isEmpty (void) {
    if (top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack is not empty.\n");
    }
}

void isFull (void) {
    if (top == MAX - 1) {
        printf("Stack is full.\n");
    } else {
        printf("Stack is not full.\n");
    }
}

void display (void) {
    if (top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack:\n");
        for (int i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

void displayMenu (void) {
    printf("STACKS\n");
    printf("1. Push\n2. Pop\n3. Peek\n4. isEmpty\n5. isFull\n6. Display\n0. Exit\n");
    printf("Enter choice: ");
}

int main (void) {
    int choice, item;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("Enter item: ");
                scanf("%d", &item);
                push(item);
                break;
            }
            case 2: {
                int item = pop();
                printf("Item popped: %d\n", item);
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
                isFull();
                break;
            }
            case 6: {
                display();
                break;
            }
            case 0: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice.\n");
            }
        }
    } while (choice != 0);
    return 0;
}