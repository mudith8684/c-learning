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

// BFS Traversal to be added

int search(NODE root, int element) {
    static int t = 0;
    if(root) {
        if(root->data == element) {
            t++;
            return t;
        }
        if(t == 0) {
            search(root->lchild, element);
        }
        if(t == 0) {
            search(root->rchild, element);
        }
    }
}

NODE copy(NODE root) {
    if(root == NULL) {
        return NULL;
    }
    NODE temp = getNode();
    temp->data = root->data;
    temp->lchild = copy(root->lchild);
    temp->rchild = copy(root->rchild);
    return temp;
}

int countNodes(NODE root) {
    static int count = 0;
    if(root != NULL) {
        countNodes(root->lchild);
        count++;
        countNodes(root->rchild);
    }
    return count;
}

int countLeafNodes(NODE root) {
    static int count = 0;
    if(root != NULL) {
        if(root->lchild == NULL && root->rchild == NULL) {
            count++;
        }
        countLeafNodes(root->lchild);
        countLeafNodes(root->rchild);
    }
    return count;
}

int isEqual(NODE root1, NODE root2) {
    return ((!root1 && !root2) || 
        (root1 && root2 && (root1->data == root2->data) && 
        isEqual(root1->lchild, root2->lchild) && isEqual(root1->rchild, root2->rchild)));
}