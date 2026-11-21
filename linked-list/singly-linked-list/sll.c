#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

NODE createNode(int data) {
    NODE newNode = malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(NODE head) {
    NODE target;
    while(head != NULL) {
        target = head;
        head = head->next;
        free(target);
    }
}

void traverseList(NODE head) {
    if(!head) return;
    NODE cur = head;
    printf("Singly linked list: ");
    while(cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

int getLength(NODE head) {
    int count = 0;
    NODE cur = head;
    while(cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

int findPosition(NODE head, int value) {
    int pos = 1;
    NODE cur = head;
    while(cur != NULL) {
        if(cur->data == value) {
            return pos;
        }
        cur = cur->next;
        pos++;
    }
    return -1; // not found or head is empty
}

NODE getNodeAt(NODE head, int pos) {
    if(head == NULL || pos < 1) {
        return NULL;
    }
    int index = 1;
    NODE cur = head;
    while(cur != NULL && index < pos) {
        cur = cur->next;
        index++;
    }
    return cur;
}

NODE insertBeginning(NODE head, int data) {
    NODE newNode = createNode(data);
    if(newNode == NULL) {
        return head;
    }
    newNode->next = head;
    head = newNode;
    return head;
}

NODE insertEnd(NODE head, int data) {
    NODE newNode = createNode(data);
    if(newNode == NULL) {
        return head;
    }
    if(head == NULL) {
        newNode = head;
        return head;
    }
    NODE cur = head;
    while(cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newNode;
    return head;
}

NODE insertPosition(NODE head, int data, int pos) {
    if(pos < 1) {
        printf("Invalid position.\n");
        return head;
    }
    if(pos == 1) {
        return insertBeginning(head, data);
    }
    NODE cur = head;
    for(int i = 1; i < pos - 1 && cur != NULL; i++) {
        cur = cur->next;
    }
    if(cur == NULL) {
        printf("Position out of bounds.\n");
        return head;
    }
    NODE newNode = createNode(data);
    if(newNode == NULL) {
        return head;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return head;
}

NODE deleteBeginning(NODE head) {
    if(head == NULL) {
        return NULL;
    }
    NODE target = head;
    head = head->next;
    free(target);
    return head;
}

NODE deleteEnd(NODE head) {
    if(head == NULL) {
        return NULL;
    }
    if(head->next == NULL) {
        free(head);
        return NULL;
    }
    NODE cur = head;
    while(cur->next->next != NULL) {
        cur = cur->next;
    }
    free(cur->next);
    cur->next = NULL;
    return head;
}

NODE deletePosition(NODE head, int pos) {
    if(head == NULL || pos < 1) {
        return head;
    }
    if(pos == 1) {
        return deleteBeginning(head);
    }
    NODE cur = head;
    for(int i = 1; i < pos - 1 && cur->next != NULL; i++) {
        cur = cur->next;
    }
    if(cur->next == NULL) {
        return head;
    }
    NODE target = cur->next;
    cur->next = target->next;
    free(target);
    return head;
}