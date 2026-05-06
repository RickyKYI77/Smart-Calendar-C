#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui_system.h"

void displayMenu() {
    printf("\n========== SMART CALENDAR ==========\n");
    printf("1. Add Event\n");
    printf("2. Delete Event\n");
    printf("3. Undo Delete\n");
    printf("4. Search by Keyword\n");
    printf("5. Search by Category\n");
    printf("6. Search by Date\n");
    printf("7. Show Free Time Slots\n");
    printf("8. Show Category Tree\n");
    printf("9. Show All Events\n");
    printf("10. Exit\n");
    printf("Enter choice: ");
}

void showAllEvents(struct Calendar* cal) {
    struct Event* curr = cal->head;

    if (!curr) {
        printf("No events found.\n");
        return;
    }

    printf("\n--- ALL EVENTS ---\n");

    while (curr) {
        printf("[ID:%d] %s | %d/%d/%d | %02d:%02d - %02d:%02d | %s | Priority:%d\n",
               curr->id,
               curr->title,
               curr->day, curr->month, curr->year,
               curr->startHour, curr->startMinute,
               curr->endHour, curr->endMinute,
               curr->category,
               curr->priority);

        curr = curr->next;
    }
}

void saveToFile(struct Calendar* cal, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot open file.\n");
        return;
    }

    struct Event* curr = cal->head;

    while (curr) {
        fprintf(fp, "%d|%d|%d|%d|%d|%d|%d|%d|%s|%s|%d\n",
                curr->id,
                curr->day, curr->month, curr->year,
                curr->startHour, curr->startMinute,
                curr->endHour, curr->endMinute,
                curr->title,
                curr->category,
                curr->priority);

        curr = curr->next;
    }

    fclose(fp);
}

void loadFromFile(struct Calendar* cal, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return;

    struct Event temp;

    while (1) {
        int result = fscanf(fp,
            "%d|%d|%d|%d|%d|%d|%d|%d|%49[^|]|%49[^|]|%d\n",
            &temp.id,
            &temp.day, &temp.month, &temp.year,
            &temp.startHour, &temp.startMinute,
            &temp.endHour, &temp.endMinute,
            temp.title,
            temp.category,
            &temp.priority);

        if (result != 11) break;

        struct Event* e = (struct Event*)malloc(sizeof(struct Event));
        if (!e) break;

        *e = temp;
        e->next = NULL;

        if (!cal->head) {
            cal->head = e;
        } else {
            struct Event* curr = cal->head;
            while (curr->next)
                curr = curr->next;
            curr->next = e;
        }
    }

    fclose(fp);
}

struct CatNode {
    char name[50];
    int count;
    struct CatNode* left;
    struct CatNode* right;
};

struct CatNode* insert(struct CatNode* root, char* name) {
    if (!root) {
        struct CatNode* n = malloc(sizeof(struct CatNode));
        if (!n) return NULL;

        strcpy(n->name, name);
        n->count = 1;
        n->left = n->right = NULL;
        return n;
    }

    int cmp = strcmp(name, root->name);

    if (cmp < 0)
        root->left = insert(root->left, name);
    else if (cmp > 0)
        root->right = insert(root->right, name);
    else
        root->count++;

    return root;
}

void printTree(struct CatNode* root) {
    if (!root) return;

    printTree(root->right);
    printf("%s (%d)\n", root->name, root->count);
    printTree(root->left);
}

void freeTree(struct CatNode* root) {
    if (!root) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void showCategoryTree(struct Calendar* cal) {
    struct CatNode* root = NULL;
    struct Event* curr = cal->head;

    while (curr) {
        root = insert(root, curr->category);
        curr = curr->next;
    }

    printf("\n--- CATEGORY TREE ---\n");

    if (root)
        printTree(root);
    else
        printf("No categories found.\n");

    freeTree(root);
}