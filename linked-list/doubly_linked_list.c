#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

typedef struct Node* NODE;

NODE createNode (int data) {
    NODE newNode = malloc (sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

NODE insertBeginning (NODE head, int data) {
    if (head == NULL) {
        printf("Head is empty.\n");
        return head;
    }
    NODE temp = createNode(data);
    temp->next = head;
    head->prev = temp;
    head = temp;
    return head;
}

NODE insertEnd (NODE head, int data) {
    if (head == NULL) {
        printf("Head is empty.\n");
        return head;
    }
    NODE temp = createNode (data);
    NODE cur = head;
    while (cur != NULL) {
        cur = cur->next;
    }
    cur->next = temp;
    temp->prev = cur;
    return head;
}

NODE insertPosition (NODE head, int data, int position) {
    NODE temp = createNode(data);
    NODE cur = head;
    if (head == NULL || position == 1) {
        temp->next = head;
        if (head != NULL) {
            head->prev = temp;
        }
        return temp;
    }
    for (int i = 1; i < position && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Invalid position\n");
        free(temp);
        return head;
    }
    temp->next = cur->next;
    temp->prev = cur;
    if (cur->next != NULL) {
        cur->next->prev = temp;
    }
    cur->next = temp;
    return head;
}

void display (NODE head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

NODE deleteBeginning (NODE head) {
    NODE temp;
    if (head == NULL) {
        printf("Head is empty.\n");
        return head;
    }
    if (head->next == NULL) {
        free (head);
        return NULL;
    }
    temp = head;
    head = head->next;
    free(temp);
    return head;
}

NODE deleteEnd (NODE head) {
    NODE temp;
    if (head == NULL) {
        printf("Head is empty.\n");
        return head;
    }
    if (head->next == NULL) {
        free (head);
        return NULL;
    }
    temp = head;
    while (temp != NULL) {
        temp = temp->next;
    }
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
        return head;
    }
    if (cur == head) {
        head = cur->next;
        if (head != NULL) {
            head->prev = NULL;
        }
    } else if (cur->next) {
        cur->prev->next = NULL;
    } else {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }
    free(cur);
    return head;
}