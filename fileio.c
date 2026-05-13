#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

void saveToFile(struct Calendar* cal, const char* filename) {
    FILE* f = fopen(filename, "w");

    struct Event* cur = cal->head;

    while (cur) {
        fprintf(f,
            "%d|%d|%d|%d|%d|%d|%d|%d|%s|%s|%d\n",
            cur->id,
            cur->day,
            cur->month,
            cur->year,
            cur->startHour,
            cur->startMinute,
            cur->endHour,
            cur->endMinute,
            cur->title,
            cur->category,
            cur->priority
        );

        cur = cur->next;
    }

    fclose(f);
}

void loadFromFile(struct Calendar* cal, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return;

    struct Event* e;
    int maxID = 0;

    while (!feof(f)) {
        e = malloc(sizeof(struct Event));

        if (fscanf(f, "%d|%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%d\n",
            &e->id,
            &e->day,
            &e->month,
            &e->year,
            &e->startHour,
            &e->startMinute,
            &e->endHour,
            &e->endMinute,
            e->title,
            e->category,
            &e->priority) != 11) {
            free(e);
            break;
        }

        e->next = cal->head;
        cal->head = e;

        if (e->id > maxID) maxID = e->id;
    }

    cal->nextID = maxID + 1;

    fclose(f);
}