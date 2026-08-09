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
void search_sll (struct Node *head, int key) {
    struct Node *temp = head;
    int count = 1, found = 0;
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

// Inserting a node
struct Node* insert_beginning (struct Node *head, int data) {
    struct Node *temp = createNode(data);
    temp->next = head;
    head = temp;
    return head;
}

struct Node* insert_end (struct Node *head, int data) {
    struct Node *temp = createNode(data);
    if (head == NULL) {
        return temp;
    }
    struct Node *cur = head;
    while (cur != NULL) {
        cur = cur->next;
    }
    cur->next = temp;
    return head;
}

struct Node* insert_position(struct Node* head, int data, int pos) {
    struct Node* temp = createNode(data);
    if (pos == 0) {
        temp->next = head;
        return temp;
    }
    struct Node* cur = head;
    for (int i = 0; i < pos - 1 && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur == NULL) {
        free(temp);
        printf("Position out of bounds.\n");
        return head;
    }
    temp->next = cur->next;
    cur->next = temp;
    return head;
}

int main () {
    printf("Singly Linked List\n");
    struct Node *head = NULL;
    head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    traversal_sll(head); // print list
    int length = length_sll(head);
    printf("The length of this singly linked list is: %d\n", length);
    search_sll(head, 30);
    search_sll(head, 100);
    struct Node *temp = head;
    int sum = 0;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    printf("The sum of the elements is: %d\n", sum);
    // freeing entire list using temp
    head = insert_beginning(head, 5);
    traversal_sll(head);
    head = insert_end(head, 50);
    traversal_sll(head);
    head = insert_position(head, 15, 3);
    traversal(head);
    temp = head;
    while (temp != NULL) {
        struct Node *next = temp->next;
        free(temp);
        temp = next;
    }
    return 0;
}