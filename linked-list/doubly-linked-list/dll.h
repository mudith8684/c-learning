#ifndef DLL_H
#define DLL_H

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node, *NODE;

NODE createNode(int data);
void freeList(NODE head);

NODE insertBeginning(NODE head, int data);
NODE insertEnd(NODE head, int data);
NODE insertPosition(NODE head, int data, int position);

NODE deleteBeginning(NODE head);
NODE deleteEnd(NODE head);
NODE deletePosition(NODE head, int position);

void searchByValue(NODE head, int value);
void display(NODE head);
NODE reverse(NODE head);

#endif