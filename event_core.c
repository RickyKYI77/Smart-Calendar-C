#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event_core.h"
#include "fileio.h"

int timeOverlap(int start1, int end1, int start2, int end2) {
    return (start1 < end2 && start2 < end1);
}

int hasOverlap(struct Calendar* cal, struct Event* newEvent) {
    struct Event* current = cal->head;

    int newStart = newEvent->startHour * 60 + newEvent->startMinute;
    int newEnd = newEvent->endHour * 60 + newEvent->endMinute;

    while (current != NULL) {
        if (current != newEvent && current->day == newEvent->day) {
            int currStart = current->startHour * 60 + current->startMinute;
            int currEnd = current->endHour * 60 + current->endMinute;

            if (timeOverlap(newStart, newEnd, currStart, currEnd))
                return 1;
        }
        current = current->next;
    }
    return 0;
}

struct Event* createEvent(struct Calendar* cal) {
    struct Event* e = malloc(sizeof(struct Event));

    printf("Enter event title: ");
    scanf(" %[^\n]", e->title);

    printf("Enter day (1-31): ");
    scanf("%d", &e->day);

    e->month = 4;
    e->year = 2026;

    printf("Start hour: ");
    scanf("%d", &e->startHour);
    printf("Start minute: ");
    scanf("%d", &e->startMinute);

    printf("End hour: ");
    scanf("%d", &e->endHour);
    printf("End minute: ");
    scanf("%d", &e->endMinute);

    printf("Category: ");
    scanf(" %[^\n]", e->category);

    printf("Priority (1-3): ");
    scanf("%d", &e->priority);

    e->id = cal->nextID++;
    e->next = NULL;

    return e;
}

void insertEvent(struct Calendar* cal, struct Event* e) {
    if (!cal->head || cal->head->day > e->day) {
        e->next = cal->head;
        cal->head = e;
        return;
    }

    struct Event* cur = cal->head;

    while (cur->next &&
        (cur->next->day < e->day ||
        (cur->next->day == e->day &&
         cur->next->startHour <= e->startHour))) {
        cur = cur->next;
    }

    e->next = cur->next;
    cur->next = e;
}

void addEvent(struct Calendar* cal) {
    struct Event* e = createEvent(cal);

    if (hasOverlap(cal, e)) {
        printf("Overlap detected!\n");
        free(e);
        return;
    }

    insertEvent(cal, e);
    saveToFile(cal, "calendar_data.txt");
    printf("Event added!\n");
}

/* STACK */
void deleteEvent(struct Calendar* cal) {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    struct Event *cur = cal->head, *prev = NULL;

    while (cur) {
        if (cur->id == id) {
            if (prev) prev->next = cur->next;
            else cal->head = cur->next;

            free(cur);
            saveToFile(cal, "calendar_data.txt");
            printf("Deleted!\n");
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    printf("Not found.\n");
}

void undoDelete(struct Calendar* cal) {
    (void)cal;
}

void editEvent(struct Calendar* cal) {
    int id;
    printf("Enter ID to edit: ");
    scanf("%d", &id);

    struct Event* cur = cal->head;

    while (cur) {
        if (cur->id == id) {
            printf("New title: ");
            scanf(" %[^\n]", cur->title);

            printf("New day: ");
            scanf("%d", &cur->day);

            saveToFile(cal, "calendar_data.txt");
            printf("Updated!\n");
            return;
        }
        cur = cur->next;
    }

    printf("Not found.\n");
}