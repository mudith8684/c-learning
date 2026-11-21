#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

static void displayMenu(void) {
    printf("\nDOUBLY LINKED LIST MENU\n");
    printf("1. Insert at beginning\n");
    printf("2. Insert at end\n");
    printf("3. Insert at pos\n");
    printf("4. Delete at beginning\n");
    printf("5. Delete at end\n");
    printf("6. Delete at pos\n");
    printf("7. Search by value\n");
    printf("8. Display list\n");
    printf("9. Reverse list\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    NODE head = NULL;
    int choice = 0, data = 0, pos = 0;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice) {
            case 1:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = insertBeginning(head, data);
                break;
            case 2:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = insertEnd(head, data);
                break;
            case 3:
                printf("Enter data and position: ");
                if (scanf("%d%d", &data, &pos) != 2) {
                    printf("Invalid value for data and/or position.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = insertPosition(head, data, pos);
                break;
            case 4:
                head = deleteBeginning(head);
                break;
            case 5:
                head = deleteEnd(head);
                break;
            case 6:
                printf("Enter pos: ");
                if (scanf("%d", &pos) != 1) {
                    printf("Invalid position.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                head = deletePosition(head, pos);
                break;
            case 7:
                printf("Enter value to search: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid data format.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                searchByValue(head, data);
                break;
            case 8:
                display(head);
                break;
            case 9:
                head = reverse(head);
                printf("List reversed.\n");
                display(head);
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