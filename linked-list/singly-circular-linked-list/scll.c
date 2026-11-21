#include "scll.h"
#include <stdio.h>
#include <stdlib.h>

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Node malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
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
        printf("%d -> ", cur->data);
        cur = cur->next;
    } while (cur != head);
    printf("(head: %d)\n", head->data);
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
    NODE temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    newNode->next = head;
    temp->next = newNode;
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
    NODE temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
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
    if (head == NULL) {
        printf("Position out of bounds.\n");
        return head;
    }
    NODE cur = head;
    int i = 1;
    for (; i < position - 1 && cur->next != head; i++) {
        cur = cur->next;
    }
    if (i < position - 1) {
        printf("Position out of bounds.\n");
        return head;
    }

    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    newNode->next = cur->next;
    cur->next = newNode;
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
    NODE cur = head;
    NODE temp = head;
    while (cur->next != head) {
        cur = cur->next;
    }
    head = head->next;
    cur->next = head;
    free(temp);
    return head;
}

NODE deleteEnd(NODE head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == head) {
        free(head);
        return NULL;
    }
    NODE cur = head;
    while (cur->next->next != head) {
        cur = cur->next;
    }
    NODE temp = cur->next;
    cur->next = head;
    free(temp);
    return head;
}

NODE deletePosition(NODE head, int position) {
    if (head == NULL || position < 1) {
        return head;
    }
    if (position == 1) {
        return deleteBeginning(head);
    }
    NODE cur = head;
    int i = 1;
    while (i < position - 1 && cur->next != head) {
        cur = cur->next;
        i++;
    }
    if (cur->next == head) {
        printf("Position out of bounds.\n");
        return head;
    }
    NODE target = cur->next;
    cur->next = target->next;
    free(target);
    return head;
}