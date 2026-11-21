#include "stack.h"
#include <stdio.h>

static int stack[MAX];
static int top = -1;

void push(int data) {
    if (isFull()) {
        printf("Stack is full.\n");
        return;
    }
    stack[++top] = data;
    printf("%d pushed to stack.\n", data);
}

int pop(void) {
    if (isEmpty()) {
        printf("Stack underflow.\n");
        return -1;
    }
    int poppedValue = stack[top--];
    return poppedValue;
}

int peek(void) {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack[top];
}

bool isEmpty(void) {
    return top == -1;
}

bool isFull(void) {
    return top == MAX - 1;
}

void display(void) {
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (top to bottom):\n");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}