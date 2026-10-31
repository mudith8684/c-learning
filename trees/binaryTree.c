#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *lchild, *rchild;
};
typedef struct Node * NODE;

NODE getNode() {
    NODE newNode = malloc(sizeof(struct Node));
    if(!newNode) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->lchild = newNode->rchild = NULL;
    return newNode;
}

NODE createTree(int item) {
    int x;
    if(item != -1) {
        NODE temp = getNode();
        temp->data = item;
        printf("Enter the lchild of %d (-1 for no child): ", item);
        scanf("%d", &x);
        temp->lchild = createTree(x);
        printf("Enter the rchild of %d (-1 for no child): ", item);
        temp->rchild = createTree(x);
        return temp;
    }
    return NULL;
}

void preorderTraversal(NODE root) {
    if(root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->lchild);
    preorderTraversal(root->rchild);
}

void inorderTraversal(NODE root) {
    if(root == NULL) {
        return;
    }
    inorderTraversal(root->lchild);
    printf("%d ", root->data);
    inorderTraversal(root->rchild);
}

void postorderTraversal(NODE root) {
    if(root == NULL) {
        return;
    }
    postorderTraversal(root->lchild);
    postorderTraversal(root->rchild);
    printf("%d ", root->data);
}

// Iterative traversals
void preOrderTraversal(NODE root) {
    if(root == NULL) {
        return;
    }
    NODE stack[100];
    int top = -1;
    stack[++top] = root;
    while(top != -1) {
        NODE current = stack[top--];
        printf("%d ", current->data);
        if(current->rchild != NULL) {
            stack[++top] = current->rchild;
        }
        if(current->lchild != NULL) {
            stack[++top] = current->lchild;
        }
    }
}

void inOrderTraversal(NODE root) {
    if(root == NULL) {
        return;
    }
    NODE stack[100];
    int top = -1;
    NODE current = root;
    while(current != NULL && top > -1) {
        while(current != NULL) {
            stack[++top] = current;
            current = current->lchild;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->rchild;
    }
}

void postOrderTraversal(NODE root) {
    if(root == NULL) {
        return;
    }
    NODE current = root, prev = NULL, stack[100];
    int top = -1;
    do {
        while(current != NULL) {
            stack[++top] = current;
            current = current->lchild;
        }
        while(current == NULL && top == -1) {
            current = stack[top];
            if(current->rchild == NULL || current->rchild == prev) {
                printf("%d ", current->data);
                top--;
                prev = current;
                current = NULL;
            } else {
                current = current->rchild;
            }
        }
    } while(top != -1);
}