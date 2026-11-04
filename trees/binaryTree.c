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

void displayList() {
    printf("\nBinary Tree\n1. Create Tree\n2. Preorder Traversal (recursive)\n3. Inorder Traversal (recursive)\n4. Postorder Traversal (recursive)\n5. Preorder Traversal (iterative)\n6. Inorder Traversal (iterative)\n7. Postorder Traversal (iterative)\n8. Search an element\n9. Count Nodes\n10. Count Leaf Nodes\n11. Check if two trees are equal\nEnter your choice: ");
}

int main() {
    int choice, value;
    NODE root, root1, root2;
    do {
        displayList();
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        switch(choice) {
            case 1: {
                printf("Enter root value: ");
                if(scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    return 1;
                }
                root = createTree(value);
                break;
            }
            case 2: {
                preorderTraversal(root);
                break;
            }
            case 3: {
                inorderTraversal(root);
                break;
            }
            case 4: {
                postorderTraversal(root);
                break;
            }
            case 5: {
                preOrderTraversal(root);
                break;
            }
            case 6: {
                inOrderTraversal(root);
                break;
            }
            case 7: {
                postOrderTraversal(root);
                break;
            }
            case 8: {
                printf("Enter element to search: ");
                if(scanf("%d", &value) != 1){
                    printf("Invalid input.\n");
                    return 1;
                }
                search(root, value);
                break;
            }
            case 9: {
                value = countNodes(root);
                printf("Number of nodes: %d\n", value);
                break;
            }
            case 10: {
                value = countLeafNodes(root);
                printf("Number of leaf nodes: %d\n", value);
                break;
            }
            case 11: {
                if(isEqual(root1, root2)) {
                    printf("Both trees are equal.\n");
                } else {
                    printf("Both trees are not equal.\n");
                }
                break;
            }
            // copy function
            default: {
                printf("Invalid input.\n");
            }
        }
    } while(choice != 0);
    return 0;
}

// add exit option in do-while loop
// fix rchild bug
// add copy function in do-while loop