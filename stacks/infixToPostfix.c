#include <stdio.h>
#include <stdlib.h>

struct Node {
    long long data;
    struct Node* next;
};

typedef struct Node* NODE;

NODE createNode (long long data) {
    NODE newNode = malloc (sizeof (struct Node));
    if (newNode == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int push (NODE *top, long long data) {
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return 0; // Failure
    }
    newNode->next = *top;
    *top = newNode;
    return 1; // Success
}

int pop (NODE *top, long long * value) {
    if (*top == NULL) {
        return 0; // Failure
    }
    NODE temp = *top;
    *value = temp->data;
    *top = temp->next;
    free(temp);
    return 1; // Success
}

int isEmpty (NODE top) {
    return top == NULL;
}

void freeStack (NODE *top) {
    long long value;
    while (pop(top, &value)) {
        printf("Popped.\n");
    }
}

int precedence (char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

int appendChar (char output[], size_t capacity, size_t *length, char ch) {
    if (*length + 1 >= capacity) {
        return 0; // Failure
    }
    output[(*length)++] = ch;
    output[*length] = '\0';
    return 1; // Success
}