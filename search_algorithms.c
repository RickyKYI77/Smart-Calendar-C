#include <stdio.h>
#include <string.h>
#include "search_algorithms.h"

void searchByKeyword(struct Calendar* cal) {
    char keyword[100];

    printf("Enter keyword: ");
    scanf(" %[^\n]", keyword);

    struct Event* curr = cal->head;
    int found = 0;

    printf("\n--- SEARCH RESULTS ---\n");

    while (curr != NULL) {
        if (strstr(curr->title, keyword) || strstr(curr->category, keyword)) {
            printf("[ID:%d] %s | %02d/%02d | %02d:%02d - %02d:%02d | %s\n",
                   curr->id,
                   curr->title,
                   curr->day, curr->month,
                   curr->startHour, curr->startMinute,
                   curr->endHour, curr->endMinute,
                   curr->category);
            found = 1;
        }
        curr = curr->next;
    }

    if (!found) printf("No matching events found.\n");
}

void searchByCategory(struct Calendar* cal) {
    char category[50];

    printf("Enter category: ");
    scanf(" %[^\n]", category);

    struct Event* curr = cal->head;
    int found = 0;

    printf("\n--- CATEGORY: %s ---\n", category);

    while (curr) {
        if (strcmp(curr->category, category) == 0) {
            printf("%s | %02d:%02d - %02d:%02d | Day %d\n",
                   curr->title,
                   curr->startHour, curr->startMinute,
                   curr->endHour, curr->endMinute,
                   curr->day);
            found = 1;
        }
        curr = curr->next;
    }

    if (!found) printf("No events in this category.\n");
}

void searchByDate(struct Calendar* cal) {
    int day;
    printf("Enter day (1-31): ");
    scanf("%d", &day);

    struct Event* curr = cal->head;
    int found = 0;

    printf("\n--- EVENTS ON DAY %d ---\n", day);

    while (curr) {
        if (curr->day == day) {
            printf("%s | %02d:%02d - %02d:%02d | %s\n",
                   curr->title,
                   curr->startHour, curr->startMinute,
                   curr->endHour, curr->endMinute,
                   curr->category);
            found = 1;
        }
        curr = curr->next;
    }

    if (!found) printf("No events found.\n");
}

void showFreeTimeSlots(struct Calendar* cal) {
    int day;
    printf("Enter day: ");
    scanf("%d", &day);

    struct Event* curr = cal->head;

    int currentTime = 9 * 60;   // 9:00
    int endWork = 17 * 60;      // 17:00

    printf("\n--- FREE TIME SLOTS ---\n");

    while (currentTime < endWork) {

        int nextBusy = endWork;

        struct Event* temp = cal->head;

        while (temp) {
            if (temp->day == day) {
                int start = temp->startHour * 60 + temp->startMinute;

                if (start >= currentTime && start < nextBusy) {
                    nextBusy = start;
                }
            }
            temp = temp->next;
        }

        if (nextBusy > currentTime) {
            printf("%02d:%02d - %02d:%02d\n",
                   currentTime / 60, currentTime % 60,
                   nextBusy / 60, nextBusy % 60);
        }

        // skip busy event
        struct Event* t = cal->head;
        while (t) {
            if (t->day == day) {
                int start = t->startHour * 60 + t->startMinute;
                int end = t->endHour * 60 + t->endMinute;

                if (start == nextBusy) {
                    currentTime = end;
                    break;
                }
            }
            t = t->next;
        }

        if (currentTime == nextBusy) {
            currentTime++;
        } else {
            currentTime = nextBusy;
        }
    }
}