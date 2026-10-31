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
    NODE newNode = createNode(data);
    NODE temp;
    if (newNode == NULL) {
        printf("malloc failed.\n");
        return head;
    }
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        newNode->next = head;
        temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        head = newNode;
    }
    return head;
}

NODE insertEnd (NODE head, int data) {
    NODE newNode = createNode (data);
    NODE temp;
    if (newNode == NULL) {
        printf("malloc failed for newNode.\n");
        return head;
    }
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
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

NODE deleteBeginning(NODE head) {
    if(head == NULL) {
        return head;
    }
    if(head->next == head) {
        free(head);
        return NULL;
    }
    NODE cur = head, temp = head;
    while(cur->next != head) {
        cur = cur->next;
    }
    head = head->next;
    cur->next = head;
    free(temp);
    return head;
}

NODE deleteEnd(NODE head) {
    if(head == NULL) {
        return head;
    } else if(head->next == NULL) {
        free(head);
        return NULL;
    }
    NODE cur = head, temp = NULL;
    while(cur->next->next != head) {
        cur = cur->next;
    }
    temp = cur->next;
    cur->next = head;
    free(temp);
    return head;
}