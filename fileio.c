#include <stdio.h>
#include "fileio.h"

void saveToFile(struct Calendar* cal, const char* file) {
    FILE* f = fopen(file, "w");
    if (!f) return;

    struct Event* c = cal->head;

    while (c) {
        fprintf(f, "%d %d %d %d %d %d %d %s %s\n",
            c->id, c->day, c->month, c->year,
            c->startHour, c->startMinute,
            c->endHour, c->endMinute,
            c->title, c->category);

        c = c->next;
    }

    fclose(f);
}