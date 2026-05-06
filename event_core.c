#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event_core.h"

void pushDeleted(struct Calendar* cal, struct Event* e) {
    struct StackNode* node = malloc(sizeof(struct StackNode));
    node->event = e;
    node->next = cal->deletedStack;
    cal->deletedStack = node;
}

struct Event* popDeleted(struct Calendar* cal) {
    if (!cal->deletedStack) return NULL;

    struct StackNode* temp = cal->deletedStack;
    struct Event* e = temp->event;

    cal->deletedStack = temp->next;
    free(temp);
    return e;
}

int timeOverlap(int s1, int e1, int s2, int e2) {
    return (s1 < e2 && s2 < e1);
}

int hasOverlap(struct Calendar* cal, struct Event* newEvent) {
    struct Event* curr = cal->head;

    int ns = newEvent->startHour * 60 + newEvent->startMinute;
    int ne = newEvent->endHour * 60 + newEvent->endMinute;

    while (curr) {
        if (curr->day == newEvent->day) {
            int cs = curr->startHour * 60 + curr->startMinute;
            int ce = curr->endHour * 60 + curr->endMinute;

            if (timeOverlap(ns, ne, cs, ce)) return 1;
        }
        curr = curr->next;
    }
    return 0;
}

struct Event* createEvent(struct Calendar* cal) {
    struct Event* e = malloc(sizeof(struct Event));

    printf("Title: ");
    scanf(" %[^\n]", e->title);

    printf("Day: ");
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

    struct Event* curr = cal->head;
    while (curr->next && curr->next->day <= e->day)
        curr = curr->next;

    e->next = curr->next;
    curr->next = e;
}

void addEvent(struct Calendar* cal) {
    struct Event* e = createEvent(cal);

    if (hasOverlap(cal, e)) {
        printf("Overlap detected!\n");
        free(e);
        return;
    }

    insertEvent(cal, e);
    printf("Added.\n");
}

void deleteEvent(struct Calendar* cal) {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    struct Event *curr = cal->head, *prev = NULL;

    while (curr) {
        if (curr->id == id) {
            if (!prev) cal->head = curr->next;
            else prev->next = curr->next;

            pushDeleted(cal, curr);
            printf("Deleted.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Not found.\n");
}

void undoDelete(struct Calendar* cal) {
    struct Event* e = popDeleted(cal);

    if (!e) {
        printf("Nothing to undo.\n");
        return;
    }

    insertEvent(cal, e);
    printf("Restored.\n");
}

void editEvent(struct Calendar* cal) {
    printf("Edit feature (can extend later)\n");
}