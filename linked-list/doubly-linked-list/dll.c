#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

NODE insertBeginning(NODE head, int data) {
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode;
}

NODE insertEnd(NODE head, int data) {
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    if (head == NULL) {
        return newNode;
    }
    NODE cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newNode;
    newNode->prev = cur;
    return head;
}

NODE insertPosition(NODE head, int data, int pos) {
    if (pos < 1) {
        printf("Invalid position.\n");
        return head;
    }
    if (pos == 1) {
        return insertBeginning(head, data);
    }
    NODE cur = head;
    for (int i = 1; i < pos - 1 && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Invalid position.\n");
        return head;
    }
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    newNode->next = cur->next;
    newNode->prev = cur;
    if (cur->next != NULL) {
        cur->next->prev = newNode;
    }
    cur->next = newNode;
    return head;
}

void display(NODE head) {
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

NODE deleteBeginning(NODE head) {
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

NODE deleteEnd(NODE head) {
    if (head == NULL) {
        return head;
    }
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    NODE temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
    return head;
}

NODE deletePosition(NODE head, int pos) {
    if (head == NULL || pos < 1) {
        return head;
    }
    NODE cur = head;
    for (int i = 1; i < pos && cur != NULL; i++) {
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

void searchByValue(NODE head, int value) {
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

NODE reverse(NODE head) {
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

void freeList(NODE head) {
    while (head != NULL) {
        NODE temp = head;
        head = head->next;
        free(temp);
    }
}