#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search_algorithms.h"
#include "calendar.h"
#include "event_core.h"

// ================= SEARCH BY KEYWORD =================
void searchByKeyword(struct Calendar* cal) {
    char keyword[100];
    printf("Enter keyword: ");
    scanf(" %[^\n]", keyword);

    struct Event* current = cal->head;
    int found = 0;

    printf("\n========== SEARCH RESULTS ==========\n");

    while (current != NULL) {
        if (strstr(current->title, keyword) || strstr(current->category, keyword)) {
            printf("%s | Date: %d | Time: %02d:%02d - %02d:%02d | Category: %s | Priority: %d\n",
                   current->title,
                   current->day,
                   current->startHour, current->startMinute,
                   current->endHour, current->endMinute,
                   current->category,
                   current->priority);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No matching events found.\n");
    }
}

// ================= SEARCH BY CATEGORY =================
void searchByCategory(struct Calendar* cal) {
    char category[50];
    printf("Enter category: ");
    scanf(" %[^\n]", category);

    struct Event* current = cal->head;
    int found = 0;

    printf("\n========== CATEGORY RESULTS ==========\n");

    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            printf("%s | Date: %d | Time: %02d:%02d - %02d:%02d | Priority: %d\n",
                   current->title,
                   current->day,
                   current->startHour, current->startMinute,
                   current->endHour, current->endMinute,
                   current->priority);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No events found.\n");
    }
}

// ================= SEARCH BY DATE =================
void searchByDate(struct Calendar* cal) {
    int day;
    printf("Enter date (1-30): ");
    scanf("%d", &day);

    struct Event* current = cal->head;
    struct Event* arr[100];
    int count = 0;

    while (current != NULL) {
        if (current->day == day) {
            arr[count++] = current;
        }
        current = current->next;
    }

    // sort by time (NO swap function needed)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            int t1 = arr[j]->startHour * 60 + arr[j]->startMinute;
            int t2 = arr[j+1]->startHour * 60 + arr[j+1]->startMinute;

            if (t1 > t2) {
                struct Event* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    printf("\n========== EVENTS ON %d ==========\n", day);

    for (int i = 0; i < count; i++) {
        printf("%s | %02d:%02d - %02d:%02d | %s | Priority: %d\n",
               arr[i]->title,
               arr[i]->startHour, arr[i]->startMinute,
               arr[i]->endHour, arr[i]->endMinute,
               arr[i]->category,
               arr[i]->priority);
    }

    if (count == 0) {
        printf("No events found.\n");
    }
}

// ================= FREE TIME SLOTS =================
void showFreeTimeSlots(struct Calendar* cal) {
    int day;
    printf("Enter date (1-31): ");
    scanf("%d", &day);

    struct Event* events[100];
    int count = 0;
    struct Event* current = cal->head;

    while (current != NULL) {
        if (current->day == day) {
            events[count++] = current;
        }
        current = current->next;
    }

    // sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            int t1 = events[j]->startHour * 60 + events[j]->startMinute;
            int t2 = events[j+1]->startHour * 60 + events[j+1]->startMinute;

            if (t1 > t2) {
                struct Event* temp = events[j];
                events[j] = events[j+1];
                events[j+1] = temp;
            }
        }
    }

    int workStart = 9 * 60;
    int workEnd = 17 * 60;
    int currentTime = workStart;

    printf("\nFREE TIME SLOTS:\n");

    for (int i = 0; i < count; i++) {

        int start = events[i]->startHour * 60 + events[i]->startMinute;

        if (start > currentTime) {
            printf("%02d:%02d - %02d:%02d\n",
                   currentTime/60, currentTime%60,
                   start/60, start%60);
        }

        int end = events[i]->endHour * 60 + events[i]->endMinute;
        if (end > currentTime) {
            currentTime = end;
        }
    }

    if (currentTime < workEnd) {
        printf("%02d:%02d - %02d:%02d\n",
               currentTime/60, currentTime%60,
               workEnd/60, workEnd%60);
    }
}
