#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

typedef struct Node* NODE;

NODE createNode (int data) {
    NODE newNode = malloc (sizeof(struct Node));
    if (newNode == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

NODE insertBeginning (NODE head, int data) {
    NODE temp = createNode(data);
    temp->next = head;
    if (head != NULL) {
        head->prev = temp;
    }
    return temp;
}

NODE insertEnd (NODE head, int data) {
    if (head == NULL) {
        printf("Head is empty.\n");
        return head;
    }
    NODE temp = createNode (data);
    NODE cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = temp;
    temp->prev = cur;
    return head;
}

NODE insertPosition(NODE head, int data, int position) {
    if (position < 1) {
        printf("Invalid position.\n");
        return head;
    }
    if (position == 1) {
        return insertBeginning(head, data);
    }
    NODE cur = head;
    for (int i = 1; i < position - 1 && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Invalid position.\n");
        return head;
    }
    NODE temp = createNode(data);
    temp->next = cur->next;
    temp->prev = cur;
    if (cur->next != NULL) {
        cur->next->prev = temp;
    }
    cur->next = temp;
    return head;
}

void display (NODE head) {
    NODE cur = head;
    if (cur == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" <-> ");
        }
        cur = cur->next;
    }
    printf(" <-> NULL\n");
}

NODE deleteBeginning (NODE head) {
    if (head == NULL) {
        return head;
    }
    NODE temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    return head;
}

NODE deleteEnd (NODE head) {
    if (head == NULL) {
        return head;
    }
    if (head->next == NULL) {
        free (head);
        return NULL;
    }
    NODE temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free (temp);
    return head;
}

NODE deletePosition (NODE head, int position) {
    if (head == NULL || position < 1) {
        return head;
    }
    NODE cur = head;
    for (int i = 1; i < position && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Invalid position.\n");
        return head;
    }
    if (cur->prev != NULL) {
        cur->prev->next = cur->next;
    } else {
        head = cur->next;
    }
    if (cur->next != NULL) {
        cur->next->prev = cur->prev;
    }
    free(cur);
    return head;
}

void searchByValue (NODE head, int value) {
    int i = 1;
    while (head != NULL) {
        if (head->data == value) {
            printf("Value %d found at position %d.\n", value, i);
            return;
        }
        head = head->next;
        ++i;
    }
    printf("Value not found.\n");
}

NODE reverse (NODE head) {
    NODE temp = NULL, cur = head;
    while (cur != NULL) {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }
    if (temp != NULL) {
        head = temp->prev;
    }
    return head;
}

void freeList (NODE head) {
    while (head != NULL) {
        NODE temp = head;
        head = head->next;
        free(temp);
    }
}

NODE createList (int n) {
    NODE head = NULL;
    NODE tail = NULL;
    for (int i = 0; i < n; i++) {
        int data;
        printf("Enter data for node %d: ", i + 1);
        if (scanf("%d", &data) != 1) {
            printf("Invalid input.\n");
            freeList(head);
        }
        NODE temp = createNode(data);
        if(head == NULL) {
            head = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    return head;
}

void displayMenu () {
    printf("\nDOUBLY LINKED LIST MENU\n");
    printf("1.  Create a list\n");
    printf("2.  Insert at beginning\n");
    printf("3.  Insert at end\n");
    printf("4.  Insert at position\n");
    printf("5.  Delete at beginning\n");
    printf("6.  Delete at end\n");
    printf("7.  Delete at position\n");
    printf("8.  Search by value\n");
    printf("9.  Display list\n");
    printf("10. Reverse list\n");
    printf("0.  Exit\n");
    printf("Enter your choice: ");
}

int main () {
    NODE head = NULL;
    int choice, data, position, n;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice) {
            case 1: {
                printf("Enter number of nodes: ");
                if (scanf("%d", &n) != 1) {
                    printf("Invalid number of nodes.\n");
                    freeList(head);
                    return EXIT_FAILURE;
                }
                freeList(head);
                head = createList(n);
                printf("List created successfully.\n");
                display(head);
                break;
            }
            case 2: {
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    return EXIT_FAILURE;
                }
                head = insertBeginning(head, data);
                break;
            }
            case 3: {
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid value.\n");
                    return EXIT_FAILURE;
                }
                head = insertEnd(head, data);
                break;
            }
            case 4: {
                printf("Enter data and position: ");
                if (scanf("%d%d", &data, &position) != 2) {
                    printf("Invalid value for data and/or position.\n");
                    return EXIT_FAILURE;
                }
                head = insertPosition(head, data, position);
                break;
            }
            case 5: {
                head = deleteBeginning(head);
                break;
            }
            case 6: {
                head = deleteEnd(head);
                break;
            }
            case 7: {
                printf("Enter position: ");
                if (scanf("%d", &position) != 1) {
                    printf("Invalid position.\n");
                    return EXIT_FAILURE;
                }
                head = deletePosition (head, position);
                break;
            }
            case 8: {
                printf ("Enter value to search: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid data format.\n");
                    return EXIT_FAILURE;
                }
                searchByValue (head, data);
                break;
            }
            case 9: {
                display (head);
                break;
            }
            case 10: {
                head = reverse(head);
                printf("List reversed.\n");
                display(head);
                break;
            }
            case 0: {
                printf("Exiting program.\n");
                break;
            }
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    freeList(head);
    return EXIT_SUCCESS;
}