#ifndef CALENDAR_H
#define CALENDAR_H

// ================= STRUCTURES =================

struct Event {
    int day, month, year;
    char title[100];
    char category[50];
    int priority;
    struct Event* next;
};

struct StackNode {
    struct Event* event;
    struct StackNode* next;
};

struct Calendar {
    struct Event* head;
    struct StackNode* deletedStack;
};

// ================= STACK FUNCTIONS =================
void pushDeleted(struct Calendar* cal, struct Event* e);
struct Event* popDeleted(struct Calendar* cal);

// ================= EVENT FUNCTIONS =================
struct Event* createEvent();
void insertEvent(struct Calendar* cal, struct Event* e);
void addEvent(struct Calendar* cal);
void deleteEvent(struct Calendar* cal);
void undoDelete(struct Calendar* cal);

// ================= SEARCH FUNCTIONS =================
void searchByKeyword(struct Calendar* cal);
void searchByCategory(struct Calendar* cal);

// ================= EDIT FUNCTION =================
void editEvent(struct Calendar* cal);

// ================= CALENDAR DISPLAY =================
int hasEvent(struct Calendar* cal, int day);
void displayCalendar(struct Calendar* cal);

// ================= MEMORY CLEANUP =================
void freeAllEvents(struct Calendar* cal);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"
#include "file.h"

// ================= STACK FUNCTIONS =================

void pushDeleted(struct Calendar* cal, struct Event* e) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->event = e;
    newNode->next = cal->deletedStack;
    cal->deletedStack = newNode;
}

struct Event* popDeleted(struct Calendar* cal) {
    if (cal->deletedStack == NULL) return NULL;

    struct StackNode* temp = cal->deletedStack;
    struct Event* e = temp->event;

    cal->deletedStack = cal->deletedStack->next;
    free(temp);

    return e;
}

// ================= EVENT FUNCTIONS =================

struct Event* createEvent() {
    struct Event* e = (struct Event*)malloc(sizeof(struct Event));
    if (e == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter event title: ");
    scanf(" %[^\n]", e->title);

    printf("Enter date (1-31): ");
    scanf("%d", &e->day);
    while (e->day < 1  e->day > 31) {
        printf("Invalid day! Enter day (1-31): ");
        scanf("%d", &e->day);
    }

    e->month = 4; // Fixed for demo
    e->year = 2026;

    printf("Enter category: ");
    scanf(" %[^\n]", e->category);

    printf("Enter priority (1=Low,2=Medium,3=High): ");
    scanf("%d", &e->priority);
    while (e->priority < 1  e->priority > 3) {
        printf("Invalid priority! Enter (1-3): ");
        scanf("%d", &e->priority);
    }

    e->next = NULL;
    return e;
}

void insertEvent(struct Calendar* cal, struct Event* e) {
    if (cal->head == NULL || cal->head->day > e->day) {
        e->next = cal->head;
        cal->head = e;
        return;
    }

    struct Event* current = cal->head;

    while (current->next != NULL && current->next->day < e->day) {
        current = current->next;
    }

    e->next = current->next;
    current->next = e;
}

void addEvent(struct Calendar* cal) {
    struct Event* e = createEvent();
    if (e == NULL) return;
    insertEvent(cal, e);
    printf("Event added successfully!\n");
    saveToFile(cal, "calendar_data.txt"); // Save immediately
}

void deleteEvent(struct Calendar* cal) {
    char title[100];
    printf("Enter event title to delete: ");
    scanf(" %[^\n]", title);

    struct Event* current = cal->head;
    struct Event* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            if (prev == NULL)
                cal->head = current->next;
            else
                prev->next = current->next;

            pushDeleted(cal, current);
            printf("Event deleted successfully!\n");
            saveToFile(cal, "calendar_data.txt"); // Save immediately
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Event not found.\n");
}

void undoDelete(struct Calendar* cal) {
    struct Event* e = popDeleted(cal);

    if (e == NULL) {
        printf("No deleted events to undo.\n");
        return;
    }

    insertEvent(cal, e);
    printf("Last deleted event restored successfully!\n");
    saveToFile(cal, "calendar_data.txt"); // Save immediately
}

// ================= SEARCH FUNCTIONS =================

void searchByKeyword(struct Calendar* cal) {
    char keyword[100];
    printf("Enter keyword: ");
    scanf(" %[^\n]", keyword);

    struct Event* current = cal->head;
    int found = 0;

    printf("\n========== SEARCH RESULTS ==========\n");
    while (current != NULL) {
        if (strstr(current->title, keyword)) {
            printf("%s | Date: %d | Category: %s | Priority: %d\n",
                   current->title, current->day,
                   current->category, current->priority);
            found = 1;
        }
        current = current->next;
    }

    if (!found) printf("No matching events found.\n");
}
void searchByCategory(struct Calendar* cal) {
    char category[50];
    printf("Enter category: ");
    scanf(" %[^\n]", category);

    struct Event* current = cal->head;
    int found = 0;

    printf("\nCategory: %s (sorted by date)\n", category);

    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            printf("%s | Date: %d | Priority: %d\n",
                   current->title, current->day, current->priority);
            found = 1;
        }
        current = current->next;
    }

    if (!found) printf("No events found.\n");
}

// ================= EDIT FUNCTION =================

void editEvent(struct Calendar* cal) {
    int day;
    printf("Enter date to edit: ");
    scanf("%d", &day);

    struct Event* current = cal->head;
    int index = 1;

    while (current != NULL) {
        if (current->day == day) {
            printf("%d. %s\n", index, current->title);
            index++;
        }
        current = current->next;
    }

    if (index == 1) {
        printf("No events found.\n");
        return;
    }

    int choice;
    printf("Enter event number to edit: ");
    scanf("%d", &choice);

    current = cal->head;
    index = 1;

    while (current != NULL) {
        if (current->day == day) {
            if (index == choice) {
                printf("Enter new title: ");
                scanf(" %[^\n]", current->title);

                printf("Enter new date: ");
                scanf("%d", &current->day);

                printf("Enter new category: ");
                scanf(" %[^\n]", current->category);

                printf("Enter new priority: ");
                scanf("%d", &current->priority);

                printf("Event updated successfully!\n");
                saveToFile(cal, "calendar_data.txt"); // Save immediately
                return;
            }
            index++;
        }
        current = current->next;
    }
}

// ================= CALENDAR DISPLAY =================

int hasEvent(struct Calendar* cal, int day) {
    struct Event* current = cal->head;
    while (current != NULL) {
        if (current->day == day)
            return 1;
        current = current->next;
    }
    return 0;
}

void displayCalendar(struct Calendar* cal) {
    printf("\n        APRIL 2026\n");
    printf("=========================\n");
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    // April 2026 starts on Wednesday (adjust as needed)
    int firstDayOffset = 3; // 0=Sunday, 3=Wednesday for April 1, 2026
    
    // Print initial spaces
    for (int i = 0; i < firstDayOffset; i++) {
        printf("    ");
    }
    
    // Print days 1-30 (April has 30 days)
    for (int day = 1; day <= 30; day++) {
        if (hasEvent(cal, day))
            printf("%2d* ", day);
        else
            printf("%2d  ", day);
        
        // New line after Saturday
        if ((day + firstDayOffset) % 7 == 0)
            printf("\n");
    }
    printf("\n=========================\n");
    printf("* = Event scheduled\n");
}

// ================= MEMORY CLEANUP =================

void freeAllEvents(struct Calendar* cal) {
    struct Event* current = cal->head;
    while (current != NULL) {
        struct Event* temp = current;
        current = current->next;
        free(temp);
    }
    
    struct StackNode* stackCurrent = cal->deletedStack;
    while (stackCurrent != NULL) {
        struct StackNode* temp = stackCurrent;
        stackCurrent = stackCurrent->next;
        free(temp->event);
        free(temp);
    }
    
    cal->head = NULL;
    cal->deletedStack = NULL;
}
