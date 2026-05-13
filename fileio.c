#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"

void saveToFile(struct Calendar* cal, const char* filename) {

    FILE* file = fopen(filename, "w");

    if (!file) {
        printf("Could not save file.\n");
        return;
    }

    struct Event* current = cal->head;

    while (current != NULL) {

        fprintf(file,
                "%d %d %d %d %d %d %d %s %s %d\n",

                current->id,
                current->day,
                current->startHour,
                current->startMinute,
                current->endHour,
                current->endMinute,
                current->priority,
                current->title,
                current->category,
                current->year);

        current = current->next;
    }

    fclose(file);
}

void loadFromFile(struct Calendar* cal, const char* filename) {

    FILE* file = fopen(filename, "r");

    if (!file)
        return;

    while (1) {

        struct Event* e = malloc(sizeof(struct Event));

        if (fscanf(file,
                   "%d %d %d %d %d %d %d %s %s %d",

                   &e->id,
                   &e->day,
                   &e->startHour,
                   &e->startMinute,
                   &e->endHour,
                   &e->endMinute,
                   &e->priority,
                   e->title,
                   e->category,
                   &e->year) != 10) {

            free(e);
            break;
        }

        e->month = 4;
        e->next = NULL;

        insertEvent(cal, e);
    }

    fclose(file);
}