#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// ================= SAVE =================

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

// ================= LOAD =================

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