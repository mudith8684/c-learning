#include "sll.h"
#include <stdio.h>

static void displayMenu(void) {
    printf("\nSingly Linked List Menu\n");
    printf("1. Display List\n");
    printf("2. Get Length\n");
    printf("3. Find Position by Value\n");
    printf("4. Get Node by Position\n");
    printf("5. Insert at Beginning\n");
    printf("6. Insert at End\n");
    printf("7. Insert at Position\n");
    printf("8. Delete Beginning\n");
    printf("9. Delete End\n");
    printf("10. Delete at Position\n");
    printf("11. Exit\n");
    printf("Enter choice: ");
}

int main(void) {
NODE head = NULL;
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("List: ");
                traverseList(head);
                printf("\n");
                break;
            case 2:
                printf("Length: %d\n", getLength(head));
                break;
            case 3: {
                int value = 0;
                printf("Enter value to find: ");
                scanf("%d", &value);
                int pos = findPosition(head, value);
                if (pos != -1) {
                    printf("First occurrence of %d is at position %d.\n", value, pos);
                } else {
                    printf("%d not found in the list.\n", value);
                }
                break;
            }
            case 4: {
                int pos = 0;
                printf("Enter position: ");
                scanf("%d", &pos);
                NODE node = getNodeAt(head, pos);
                if (node != NULL) {
                    printf("Element at position %d: %d\n", pos, node->data);
                } else {
                    printf("Invalid position.\n");
                }
                break;
            }
            case 5: {
                int data = 0;
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                head = insertBeginning(head, data);
                break;
            }
            case 6: {
                int data = 0;
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                head = insertEnd(head, data);
                break;
            }
            case 7: {
                int data = 0, pos = 0;
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                head = insertPosition(head, data, pos);
                break;
            }
            case 8:
                head = deleteBeginning(head);
                printf("Deletion from beginning completed.\n");
                break;
            case 9:
                head = deleteEnd(head);
                printf("Deletion from end completed.\n");
                break;
            case 10: {
                int pos = 0;
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                head = deletePosition(head, pos);
                printf("Deletion operation completed.\n");
                break;
            }
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 11);
    freeList(head);
    return 0;
}