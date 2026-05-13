#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "calendar.h"

// ================= SAVE TO FILE =================
void saveToFile(struct Calendar* cal, const char* filename) {

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot open file for saving!\n");
        return;
    }

    struct Event* current = cal->head;

    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // write event count first
    fprintf(file, "%d\n", count);

    current = cal->head;

    while (current != NULL) {

        fprintf(file, "%d|%d|%d|%d|%d|%d|%d|%d|%s|%s|%d\n",
                current->id,
                current->day,
                current->month,
                current->year,
                current->startHour,
                current->startMinute,
                current->endHour,
                current->endMinute,
                current->title,
                current->category,
                current->priority);

        current = current->next;
    }

    fclose(file);
}

// ================= LOAD FROM FILE =================
void loadFromFile(struct Calendar* cal, const char* filename) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("No save file found. Starting fresh.\n");
        return;
    }

    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        printf("Invalid file format.\n");
        fclose(file);
        return;
    }

    // clear existing list
    struct Event* current = cal->head;
    while (current != NULL) {
        struct Event* temp = current;
        current = current->next;
        free(temp);
    }
    cal->head = NULL;

    // load events
    for (int i = 0; i < count; i++) {

        struct Event* e = (struct Event*)malloc(sizeof(struct Event));

        if (e == NULL) {
            printf("Memory allocation failed!\n");
            break;
        }

        if (fscanf(file, "%d|%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%d\n",
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

            printf("Error reading event %d\n", i + 1);
            free(e);
            break;
        }

        e->next = NULL;

        // insert sorted by date + time (same behavior as your system)
        if (cal->head == NULL ||
            cal->head->day > e->day) {

            e->next = cal->head;
            cal->head = e;

        } else {

            struct Event* temp = cal->head;

            while (temp->next != NULL &&
                  (temp->next->day < e->day ||
                  (temp->next->day == e->day &&
                   temp->next->startHour * 60 + temp->next->startMinute <
                   e->startHour * 60 + e->startMinute))) {

                temp = temp->next;
            }

            e->next = temp->next;
            temp->next = e;
        }
    }

    fclose(file);

    printf("Calendar loaded successfully (%d events)\n", count);

    // update nextID properly
    int maxID = 0;
    struct Event* t = cal->head;

    while (t != NULL) {
        if (t->id > maxID) {
            maxID = t->id;
        }
        t = t->next;
    }

    cal->nextID = maxID + 1;
}