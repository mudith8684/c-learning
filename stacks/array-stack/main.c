#include "stack.h"
#include <stdio.h>

static void displayMenu(void) {
    printf("\nSTACKS (array-based)\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Peek\n");
    printf("4. isEmpty\n");
    printf("5. isFull\n");
    printf("6. Display\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

int main(void) {
    int choice = 0, item = 0;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice) {
            case 1:
                printf("Enter item: ");
                if (scanf("%d", &item) == 1) {
                    push(item);
                } else {
                    printf("Invalid item.\n");
                }
                break;
            case 2: {
                if (!isEmpty()) {
                    int popped = pop();
                    printf("Item popped: %d\n", popped);
                } else {
                    pop();
                }
                break;
            }
            case 3: {
                int topVal = peek();
                if (!isEmpty()) {
                    printf("Top element is: %d\n", topVal);
                }
                break;
            }
            case 4:
                printf(isEmpty() ? "Stack is empty.\n" : "Stack is not empty.\n");
                break;
            case 5:
                printf(isFull() ? "Stack is full.\n" : "Stack is not full.\n");
                break;
            case 6:
                display();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}