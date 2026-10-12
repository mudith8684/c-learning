#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node* NODE;

NODE createNode (int data) {
    NODE newNode = malloc (sizeof(struct Node));
    if (newNode == NULL) {
        printf("Node malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = newNode;
    return newNode;
}

NODE insertBeginning (NODE head, int data) {
    NODE temp = createNode(data);
    NODE cur;
    if (temp == NULL) {
        printf("malloc failed for temp.\n");
        return head;
    }
    if (head == NULL) {
        head = temp;
        temp->next = head;
    } else {
        temp->next = head;
        cur = head;
        while (cur->next != head) {
            cur = cur->next;
        }
        cur->next = temp;
        head = temp;
    }
    return head;
}

NODE insertEnd (NODE head, int data) {
    NODE temp = createNode (data);
    NODE cur;
    if (temp == NULL) {
        printf("malloc failed for temp.\n");
        return head;
    }
    if (head == NULL) {
        head = temp;
        temp->next = head;
    } else {
        cur = head;
        while (cur->next != head) {
            cur = cur->next;
        }
        cur->next = temp;
        temp->next = head;
    }
    return head;
}

NODE insertPosition (NODE head, int data, int position) {
    NODE newNode = createNode (data);
    if (head == NULL || position == 1) {
        if (head == NULL) {
            head = newNode;
            return head;
        }
        NODE temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
        head = newNode;
        return head;
    }
    NODE cur = head;
    int i = 1;
    for (; i < position - 1 && cur->next != head; i++) {
        cur = cur->next;
    }
    if (cur->next == head && i < position - 1) {
        printf("Position out of bounds.\n");
        free (newNode);
        return head;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return head;
}