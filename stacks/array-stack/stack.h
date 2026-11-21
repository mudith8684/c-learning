#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define MAX 1024

void push(int data);
int pop(void);
int peek(void);
bool isEmpty(void);
bool isFull(void);
void display(void);

#endif