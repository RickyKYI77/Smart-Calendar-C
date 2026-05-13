#include "calendar.h"

void searchByKeyword(struct Calendar* cal) {
    char k[100];
    printf("Enter keyword: ");
    scanf(" %[^\n]", k);

    struct Event* c = cal->head;

    while (c) {
        if (strstr(c->title, k) || strstr(c->category, k)) {
            printf("%s\n", c->title);
        }
        c = c->next;
    }
}

void searchByCategory(struct Calendar* cal) {
    char cat[50];
    printf("Enter category: ");
    scanf(" %[^\n]", cat);

    struct Event* c = cal->head;

    while (c) {
        if (!strcmp(c->category, cat)) {
            printf("%s\n", c->title);
        }
        c = c->next;
    }
}

void searchByDate(struct Calendar* cal) {
    int d;
    printf("Enter date: ");
    scanf("%d", &d);

    struct Event* c = cal->head;

    while (c) {
        if (c->day == d)
            printf("%s\n", c->title);
        c = c->next;
    }
}

void showFreeTimeSlots(struct Calendar* cal) {
    int day;
    printf("Enter day (1-31): ");
    scanf("%d", &day);

    struct Event* arr[100];
    int n = 0;

    struct Event* c = cal->head;

    while (c) {
        if (c->day == day) {
            arr[n++] = c;
        }
        c = c->next;
    }

    if (n == 0) {
        printf("Whole day is free (no events).\n");
        printf("09:00 - 17:00 available.\n");
        return;
    }

    /* SORT by start time */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (timeToMinutes(arr[j]->startHour, arr[j]->startMinute) >
                timeToMinutes(arr[j+1]->startHour, arr[j+1]->startMinute)) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

    int workStart = 9 * 60;
    int workEnd = 17 * 60;

    int current = workStart;

    printf("\n--- FREE TIME SLOTS ---\n");

    for (int i = 0; i < n; i++) {
        int s = timeToMinutes(arr[i]->startHour, arr[i]->startMinute);
        int e = timeToMinutes(arr[i]->endHour, arr[i]->endMinute);

        if (s > current) {
            printf("%02d:%02d - %02d:%02d\n",
                   current / 60, current % 60,
                   s / 60, s % 60);
        }

        if (e > current)
            current = e;
    }

    if (current < workEnd) {
        printf("%02d:%02d - %02d:%02d\n",
               current / 60, current % 60,
               workEnd / 60, workEnd % 60);
    }
}