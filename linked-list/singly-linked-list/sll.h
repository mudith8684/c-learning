#ifndef SLL_H
#define SLL_H

typedef struct Node {
    int data;
    struct Node *next;
} Node, *NODE;

NODE createNode(int data);
void freeList(NODE head);

void traverseList(NODE head);
int getLength(NODE head);
int findPosition(NODE head, int value);
NODE getNodeAt(NODE head, int pos);

NODE insertBeginning(NODE head, int data);
NODE insertEnd(NODE head, int data);
NODE insertPosition(NODE head, int data, int pos);

NODE deleteBeginning(NODE head);
NODE deleteEnd(NODE head);
NODE deletePosition(NODE head, int pos);

#endif