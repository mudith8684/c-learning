#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node * link;
};

typedef struct node *NODE;

NODE getnode() {
    NODE x;
    x = malloc (sizeof(struct node));
    if (x == NULL) {
        perror("malloc failed");
        return NULL;
    }
    return x;
}

NODE insert_front (int item, NODE first) {
    NODE temp;
    temp = getnode();
    if (temp == NULL) {
        return first;
    }
    temp->info = item;
    temp->link = first;
    return temp;
}

void display (NODE first) {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("The contents in a singly linked list.\n");
    NODE cur = first;
    while (cur != NULL) {
        printf("%d ", cur->info);
        cur = cur->link;
    }
    printf("\n");
}

NODE delete_front (NODE first) {
    if (first == NULL) {
        printf("Empty list can't be deleted!\n");
        return NULL;
    }
    NODE temp = first;
    temp = temp->link;
    printf("Item deleted: %d\n", first->info);
    free(first);
    return temp;
}

NODE insert_rear (int item, NODE first) {
    NODE temp, cur;
    temp = getnode();
    temp->info = item;
    temp->link = NULL;
    if (first == NULL) {
        return temp;
    }
    cur = first;
    while (cur->link != NULL) {
        cur = cur->link;
    }
    cur->link = temp;
    return first;
}

NODE delete_rear (NODE first) {
    NODE cur, prev;
    if (first == NULL) {
        printf("List is empty, can't delete it.\n");
        return first;
    }
    if (first->link == NULL) {
        printf("The item to be deleted is %d.\n", first->info);
        free(first);
        return NULL;
    }
    prev = NULL;
    cur = first;
    while (cur->link != NULL) {
        prev = cur;
        cur = cur->link;
    }
    printf("The item deleted is %d.\n", cur->info);
    free(cur);
    prev->link = NULL;
    return first;
}

void free_list(NODE first) {
    NODE temp;
    while (first != NULL) {
        temp = first;
        first = first->link;
        free(temp);
    }
}

int main () {
    NODE first = NULL;
    int choice, item;
    while (1) {
        printf("\nMENU\n");
        printf("1. Insert Front\n");
        printf("2. Insert Rear\n");
        printf("3. Delete Front\n");
        printf("4. Delete Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter item: ");
                scanf("%d", &item);
                first = insert_front(item, first);
                break;
            case 2:
                printf("Enter item: ");
                scanf("%d", &item);
                first = insert_rear(item, first);
                break;
            case 3:
                first = delete_front(first);
                break;
            case 4:
                first = delete_rear(first);
                break;
            case 5:
                display(first);
                break;
            case 6:
                printf("Exiting...\n");
                NODE temp;
                while (first != NULL) {
                    temp = first;
                    first = first->link;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid choice!\n");
    }
    return 0;
}