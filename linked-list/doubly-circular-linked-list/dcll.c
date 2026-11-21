#include "dcll.h"
#include <stdio.h>
#include <stdlib.h>

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Node malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = newNode;
    newNode->next = newNode;
    return newNode;
}

void freeList(NODE head) {
    if (head == NULL) {
        return;
    }
    NODE cur = head->next;
    while (cur != head) {
        NODE next = cur->next;
        free(cur);
        cur = next;
    }
    free(head);
}

void displayList(NODE head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    NODE cur = head;
    do {
        printf("%d", cur->data);
        if (cur->next != head) {
            printf(" <-> ");
        }
        cur = cur->next;
    } while (cur != head);
    printf(" <-> (head: %d)\n", head->data);
}

int getLength(NODE head) {
    if (head == NULL) {
        return 0;
    }
    int count = 0;
    NODE cur = head;
    do {
        count++;
        cur = cur->next;
    } while (cur != head);
    return count;
}

int findPosition(NODE head, int value) {
    if (head == NULL) {
        return -1;
    }
    int pos = 1;
    NODE cur = head;
    do {
        if (cur->data == value) {
            return pos;
        }
        cur = cur->next;
        pos++;
    } while (cur != head);
    return -1;
}

NODE insertBeginning(NODE head, int data) {
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    if (head == NULL) {
        return newNode;
    }
    NODE tail = head->prev;
    newNode->next = head;
    newNode->prev = tail;
    tail->next = newNode;
    head->prev = newNode;
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
    NODE tail = head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
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
    if (head == NULL) {
        printf("Position out of bounds.\n");
        return head;
    }
    NODE cur = head;
    int i = 1;
    for (; i < pos - 1 && cur->next != head; i++) {
        cur = cur->next;
    }
    if (i < pos - 1) {
        printf("Position out of bounds.\n");
        return head;
    }
    if (cur->next == head) {
        return insertEnd(head, data);
    }
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    NODE nextNode = cur->next;
    newNode->next = nextNode;
    newNode->prev = cur;
    cur->next = newNode;
    nextNode->prev = newNode;
    return head;
}

NODE deleteBeginning(NODE head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == head) {
        free(head);
        return NULL;
    }
    NODE tail = head->prev;
    NODE newHead = head->next;
    tail->next = newHead;
    newHead->prev = tail;
    free(head);
    return newHead;
}

NODE deleteEnd(NODE head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == head) {
        free(head);
        return NULL;
    }
    NODE tail = head->prev;
    NODE newTail = tail->prev;
    newTail->next = head;
    head->prev = newTail;
    free(tail);
    return head;
}

NODE deletePosition(NODE head, int pos) {
    if (head == NULL || pos < 1) {
        return head;
    }
    if (pos == 1) {
        return deleteBeginning(head);
    }
    NODE cur = head;
    int i = 1;
    while (i < pos && cur->next != head) {
        cur = cur->next;
        i++;
    }
    if (i < pos) {
        printf("Position out of bounds.\n");
        return head;
    }
    if (cur->next == head) {
        return deleteEnd(head);
    }
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur);
    return head;
}