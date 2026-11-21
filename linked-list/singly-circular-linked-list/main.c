#include "scll.h"
#include <stdio.h>
#include <stdlib.h>

static void displayMenu(void) {
    printf("\nSINGLY CIRCULAR LINKED LIST MENU\n");
    printf("1. Display list\n");
    printf("2. Get length\n");
    printf("3. Find position by value\n");
    printf("4. Insert at beginning\n");
    printf("5. Insert at end\n");
    printf("6. Insert at position\n");
    printf("7. Delete at beginning\n");
    printf("8. Delete at end\n");
    printf("9. Delete at position\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    NODE head = NULL;
    int choice = 0, data = 0, position = 0;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice) {
            case 1:
                displayList(head);
                break;
            case 2:
                printf("Length: %d\n", getLength(head));
                break;
            case 3:
                printf("Enter value to find: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                position = findPosition(head, data);
                if (position != -1) {
                    printf("First occurrence of %d is at position %d.\n", data, position);
                } else {
                    printf("%d not found in the list.\n", data);
                }
                break;
            case 4:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = insertBeginning(head, data);
                break;
            case 5:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = insertEnd(head, data);
                break;
            case 6:
                printf("Enter data and position: ");
                if (scanf("%d%d", &data, &position) != 2) {
                    printf("Invalid value for data and/or position.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = insertPosition(head, data, position);
                break;
            case 7:
                head = deleteBeginning(head);
                break;
            case 8:
                head = deleteEnd(head);
                break;
            case 9:
                printf("Enter position: ");
                if (scanf("%d", &position) != 1) {
                    printf("Invalid position.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = deletePosition(head, position);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 0);
    freeList(head);
    return EXIT_SUCCESS;
}