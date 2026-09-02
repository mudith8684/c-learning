// =====================
// Singly Linked List (SLL)
// =====================

#include <stdio.h>
#include <stdlib.h>

// 1. Node structure of SLL
struct Node {
    int data;
    struct Node *next;
};

struct Node* create_list () {
    int n, key;
    struct Node *head = NULL, *temp = NULL;
    printf("Enter number of elements/nodes: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &key);
        struct Node* newNode = createNode(key);
        if (head == NULL) {
            head = newNode;
            temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }
    return head;
}

struct Node* createNode (int data) {
    struct Node *newNode = malloc (sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 2. Traversal of SLL
void traversal_sll (struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
}

// 3. Length of SLL
int length_sll (struct Node *head) {
    struct Node *temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// 4. Searching in SLL
int search_sll (struct Node *head, int key) {
    struct Node *temp = head;
    int count = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            return count;
        }
        count++;
        temp = temp->next;
    }
    return -1;
}

// Inserting a node
struct Node* insert_beginning (struct Node *head, int data) {
    struct Node *newNode = createNode(data);
    newNode->next = head;
    head = newNode;
    return head;
}

struct Node* insert_end (struct Node *head, int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

struct Node* insert_position (struct Node* head, int data, int pos) {
    struct Node* newNode = createNode(data);
    if (pos == 1) {
        newNode->next = head;
        return newNode;
    }
    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        free(newNode);
        printf("Position out of bounds.\n");
        return head;
    }
    newNode->next = temp->next;
    temp->next = temp;
    return head;
}

// Deleting a node
struct Node* delete_beginning (struct Node* head) {
    if (head == NULL) {
        return head; // NULL
    }
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

struct Node* delete_end (struct Node* head) {
    if (head == NULL) {
        return head; // NULL
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return head;
    }
    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}

struct Node* delete_position (struct Node* head, int pos) {
    if (head == NULL || pos < 1) {
        return head;
    }
    if (pos == 1) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        return head;
    }
    struct Node* temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
    return head;
} // temp2 is the node being deleted. Use deleteNode later. 

// Search by position
struct Node* get_node_by_position (struct Node* head, int pos) {
    if (head == NULL || pos < 1) {
        return NULL;
    }
    struct Node* temp = head;
    int count = 1;
    while (temp != NULL && count < pos) {
        temp = temp->next;
        count++;
    }
    return temp;
}

// Find first position of the key
int find_first_position (struct Node* head, int key) {
    struct Node* temp = head;
    int position = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;
}

void display_menu() {
    printf("\nSingly Linked List Menu\n");
    printf("1. Display List\n");
    printf("2. Find Length\n");
    printf("3. Search by Value\n");
    printf("4. Search by Position\n");
    printf("5. Insert at Beginning\n");
    printf("6. Insert at End\n");
    printf("7. Insert at Position\n");
    printf("8. Delete Beginning\n");
    printf("9. Delete End\n");
    printf("10. Delete at Position\n");
    printf("11. Exit\n");
    printf("Enter choice: ");
}

int main () {
    printf("Singly Linked List\n");
    struct Node* head = create_list();
    printf("\nLinked list created successfully!\n");
    printf("List: ");
    traversal_sll(head);
    int choice;
    do {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("List: ");
                traversal_sll(head);
                printf("\n");
                break;
            }
            case 2: {
                printf("Length: %d\n", length_sll(head));
                break;
            }
            case 3: {
                int key;
                printf("Enter value to search: ");
                scanf("%d", &key);
                int position = search_sll(head, key);
                if (position != -1) {
                    printf("Element found at position %d.\n", position);
                } else {
                    printf("Element not found.\n");
                }
                break;
            }
            case 11: {
                printf("Exiting...");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
            }
        }
    } while (choice != 11);
    return 0;
}