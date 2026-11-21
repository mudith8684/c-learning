#ifndef DCLL_H
#define DCLL_H

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

typedef struct Node* NODE;

NODE createNode(int data);
void freeList(NODE head);

void displayList(NODE head);
int getLength(NODE head);
int findPosition(NODE head, int value);

NODE insertBeginning(NODE head, int data);
NODE insertEnd(NODE head, int data);
NODE insertPosition(NODE head, int data, int position);

NODE deleteBeginning(NODE head);
NODE deleteEnd(NODE head);
NODE deletePosition(NODE head, int position);

#endif