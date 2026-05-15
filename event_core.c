#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event_core.h"
#include "calendar.h"

// ================= TIME OVERLAP =================
int timeOverlap(int start1, int end1, int start2, int end2) {
    return (start1 < end2 && start2 < end1);
}

// ================= HAS OVERLAP (BLOCKING FUNCTION) =================
int hasOverlap(struct Calendar* cal, struct Event* newEvent) {
    struct Event* current = cal->head;

    int newStart = newEvent->startHour * 60 + newEvent->startMinute;
    int newEnd = newEvent->endHour * 60 + newEvent->endMinute;

    while (current != NULL) {
        if (current != newEvent && current->day == newEvent->day) {

            int currStart = current->startHour * 60 + current->startMinute;
            int currEnd = current->endHour * 60 + current->endMinute;

            if (timeOverlap(newStart, newEnd, currStart, currEnd)) {
                return 1; // OVERLAP FOUND
            }
        }
        current = current->next;
    }
    return 0;
}

// ================= CREATE EVENT =================
struct Event* createEvent(struct Calendar* cal) {
    struct Event* e = (struct Event*)malloc(sizeof(struct Event));
    if (e == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter event title: ");
    scanf(" %[^\n]", e->title);

    printf("Enter date (1-31): ");
    scanf("%d", &e->day);

    while (e->day < 1 || e->day > 31) {
        printf("Invalid day! Enter again: ");
        scanf("%d", &e->day);
    }

    e->month = 4;
    e->year = 2026;

    printf("Enter start hour (0-23): ");
    scanf("%d", &e->startHour);

    printf("Enter start minute (0-59): ");
    scanf("%d", &e->startMinute);

    printf("Enter end hour (0-23): ");
    scanf("%d", &e->endHour);

    printf("Enter end minute (0-59): ");
    scanf("%d", &e->endMinute);

    int start = e->startHour * 60 + e->startMinute;
    int end = e->endHour * 60 + e->endMinute;

    while (end <= start) {
        printf("Invalid time! End must be after start.\n");

        printf("Re-enter end hour: ");
        scanf("%d", &e->endHour);

        printf("Re-enter end minute: ");
        scanf("%d", &e->endMinute);

        end = e->endHour * 60 + e->endMinute;
    }

    printf("Enter category: ");
    scanf(" %[^\n]", e->category);

    printf("Enter priority (1-3): ");
    scanf("%d", &e->priority);

    while (e->priority < 1 || e->priority > 3) {
        printf("Invalid priority! Enter again: ");
        scanf("%d", &e->priority);
    }

    e->id = cal->nextID++;
    e->next = NULL;

    return e;
}

// ================= INSERT EVENT =================
void insertEvent(struct Calendar* cal, struct Event* e) {
    if (cal->head == NULL ||
        cal->head->day > e->day) {

        e->next = cal->head;
        cal->head = e;
        return;
    }

    struct Event* current = cal->head;

    while (current->next != NULL &&
          (current->next->day < e->day ||
          (current->next->day == e->day &&
           current->next->startHour * 60 + current->next->startMinute <
           e->startHour * 60 + e->startMinute))) {

        current = current->next;
    }

    e->next = current->next;
    current->next = e;
}

// ================= ADD EVENT =================
void addEvent(struct Calendar* cal) {
    struct Event* e = createEvent(cal);
    if (e == NULL) return;

    if (hasOverlap(cal, e)) {
        printf("WARNING: Event overlaps existing event!\n");
        printf("Event NOT added.\n");
        free(e);
        return;
    }

    insertEvent(cal, e);
    printf("Event added successfully!\n");
}

// ================= DELETE EVENT =================
void deleteEvent(struct Calendar* cal) {
    int id;
    printf("Enter Event ID to delete: ");
    scanf("%d", &id);

    struct Event* current = cal->head;
    struct Event* prev = NULL;

    while (current != NULL) {
        if (current->id == id) {

            if (prev == NULL)
                cal->head = current->next;
            else
                prev->next = current->next;

            pushDeleted(cal, current);

            printf("Event deleted successfully!\n");
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Event not found.\n");
}

// ================= UNDO DELETE =================
void undoDelete(struct Calendar* cal) {
    struct Event* e = popDeleted(cal);

    if (e == NULL) {
        printf("Nothing to undo.\n");
        return;
    }

    insertEvent(cal, e);
    printf("Undo successful!\n");
}

// ================= EDIT EVENT =================
void editEvent(struct Calendar* cal) {
    int id;
    printf("Enter Event ID to edit: ");
    scanf("%d", &id);

    struct Event* current = cal->head;

    while (current != NULL) {
        if (current->id == id) {

            struct Event backup = *current;

            printf("Enter new title: ");
            scanf(" %[^\n]", current->title);

            printf("Enter new date: ");
            scanf("%d", &current->day);

            printf("Enter new start hour: ");
            scanf("%d", &current->startHour);

            printf("Enter new start minute: ");
            scanf("%d", &current->startMinute);

            printf("Enter new end hour: ");
            scanf("%d", &current->endHour);

            printf("Enter new end minute: ");
            scanf("%d", &current->endMinute);

            printf("Enter new category: ");
            scanf(" %[^\n]", current->category);

            printf("Enter new priority: ");
            scanf("%d", &current->priority);

            if (hasOverlap(cal, current)) {
                printf("WARNING: Overlap detected! Reverting changes.\n");
                *current = backup;
                return;
            }

            printf("Event updated successfully!\n");
            return;
        }

        current = current->next;
    }

    printf("Event not found.\n");
}

void pushDeleted(struct Calendar* cal, struct Event* e) {
    struct StackNode* node = malloc(sizeof(struct StackNode));
    node->event = e;
    node->next = cal->deletedStack;
    cal->deletedStack = node;
}

struct Event* popDeleted(struct Calendar* cal) {
    if (cal->deletedStack == NULL) return NULL;

    struct StackNode* temp = cal->deletedStack;
    struct Event* e = temp->event;

    cal->deletedStack = cal->deletedStack->next;
    free(temp);

    return e;
}

void showAllEvents(struct Calendar* cal) {
    struct Event* current = cal->head;

    if (current == NULL) {
        printf("No events.\n");
        return;
    }

    while (current != NULL) {
        printf("ID:%d %s %d %02d:%02d-%02d:%02d\n",
               current->id,
               current->title,
               current->day,
               current->startHour, current->startMinute,
               current->endHour, current->endMinute);
        current = current->next;
    }
}

void showCategoryTree(struct Calendar* cal) {
    struct Event* current = cal->head;

    printf("\nCATEGORY LIST:\n");

    while (current != NULL) {
        printf("%s\n", current->category);
        current = current->next;
    }
}

//working version
