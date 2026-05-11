#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui_system.h"

// ================= UI MENU =================

void displayMenu() {
    printf("\n========== SMART CALENDAR ==========\n");
    printf("1. Add Event\n");
    printf("2. Delete Event\n");
    printf("3. Undo Delete\n");
    printf("4. Search by Keyword\n");
    printf("5. Search by Category\n");
    printf("6. Show All Events\n");
    printf("7. Show Category Tree\n");
    printf("8. Exit\n");
    printf("Enter choice: ");
}

// ================= DISPLAY ALL EVENTS =================

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