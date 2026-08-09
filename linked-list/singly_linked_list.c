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

struct Node* createNode (int data) {
    struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
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
void search_sll (struct Node *head, int key) {
    struct Node *temp = head;
    int count = 0, found = 0;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("Element %d found at position %d.\n", temp->data, count);
            found = 1;
        }
        count++;
        temp = temp->next;
    }
    if (!found) {
        printf("Element %d not found.\n", key);
    }
}

int main () {
    printf("Singly Linked List\n");
    struct Node *head = NULL;
    head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    traversal_sll(head);
    length_sll(head);
    search_sll(head, 30);
    return 0;
}