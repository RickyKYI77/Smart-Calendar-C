#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"

int getEventCount(struct Calendar* cal, int day) {
    struct Event* current = cal->head;
    int count = 0;

    while (current != NULL) {
        if (current->day == day)
            count++;

        current = current->next;
    }

    return count;
}

void displayCalendar(struct Calendar* cal) {

    printf("\n        APRIL 2026\n");
    printf("=============================\n");
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    int offset = 3;

    for (int i = 0; i < offset; i++)
        printf("    ");

    for (int day = 1; day <= 30; day++) {

        int count = getEventCount(cal, day);

        if (count > 0)
            printf("%2d* ", day);
        else
            printf("%2d  ", day);

        if ((day + offset) % 7 == 0)
            printf("\n");
    }

    printf("\n=============================\n");
}

void showAllEvents(struct Calendar* cal) {

    struct Event* current = cal->head;

    if (!current) {
        printf("No events.\n");
        return;
    }

    while (current != NULL) {

        printf("\nID: %d\n", current->id);

        printf("Title: %s\n", current->title);

        printf("Date: %d/%d/%d\n",
               current->day,
               current->month,
               current->year);

        printf("Time: %02d:%02d - %02d:%02d\n",
               current->startHour,
               current->startMinute,
               current->endHour,
               current->endMinute);

        printf("Category: %s\n", current->category);

        printf("Priority: %d\n", current->priority);

        printf("--------------------------\n");

        current = current->next;
    }
}

void displayMenu() {
    printf("\n========== MENU ==========\n");

    printf("1. Add Event\n");
    printf("2. Delete Event\n");
    printf("3. Undo Delete\n");
    printf("4. Search by Keyword\n");
    printf("5. Search by Category\n");
    printf("6. Search by Date\n");
    printf("7. Show Free Time Slots\n");
    printf("8. Show Category Tree\n");
    printf("9. Edit Event\n");
    printf("10. Show All Events\n");
    printf("11. Save & Exit\n");

    printf("Enter choice: ");
}

void showCategoryTree(struct Calendar* cal) {
    if (cal->head == NULL) {
        printf("\nNo events available.\n");
        return;
    }

    printf("\n========== CATEGORY OVERVIEW ==========\n");

    struct Event* current = cal->head;

    // Simple frequency display using temporary arrays
    char categories[100][50];
    int counts[100];
    int size = 0;

    while (current != NULL) {
        int found = 0;

        for (int i = 0; i < size; i++) {
            if (strcmp(categories[i], current->category) == 0) {
                counts[i]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(categories[size], current->category);
            counts[size] = 1;
            size++;
        }

        current = current->next;
    }

    for (int i = 0; i < size; i++) {
        printf("%s : %d event(s)\n", categories[i], counts[i]);
    }
}