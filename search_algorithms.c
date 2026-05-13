#include <stdio.h>
#include <string.h>
#include "search_algorithms.h"

// ===== KEYWORD =====

void searchByKeyword(struct Calendar* cal) {
    char key[100];
    printf("Keyword: ");
    scanf(" %[^\n]", key);

    struct Event* c = cal->head;
    while (c) {
        if (strstr(c->title, key) || strstr(c->category, key)) {
            printf("%d | %s\n", c->id, c->title);
        }
        c = c->next;
    }
}

// ===== CATEGORY =====

void searchByCategory(struct Calendar* cal) {
    char cat[50];
    printf("Category: ");
    scanf(" %[^\n]", cat);

    struct Event* c = cal->head;
    while (c) {
        if (strcmp(c->category, cat) == 0) {
            printf("%s (%d)\n", c->title, c->id);
        }
        c = c->next;
    }
}

// ===== DATE =====

void searchByDate(struct Calendar* cal) {
    int day;
    printf("Day: ");
    scanf("%d", &day);

    struct Event* c = cal->head;
    while (c) {
        if (c->day == day) {
            printf("%s\n", c->title);
        }
        c = c->next;
    }
}

// ===== FREE TIME =====

void showFreeTimeSlots(struct Calendar* cal) {
    int day;
    printf("Day: ");
    scanf("%d", &day);

    int current = 9 * 60;
    int end = 17 * 60;

    while (current < end) {
        int next = end;

        struct Event* c = cal->head;

        while (c) {
            if (c->day == day) {
                int s = c->startHour * 60 + c->startMinute;
                int e = c->endHour * 60 + c->endMinute;

                if (s >= current && s < next)
                    next = s;

                if (s <= current && e > current) {
                    current = e;
                    break;
                }
            }
            c = c->next;
        }

        if (current < next) {
            printf("%02d:%02d - %02d:%02d\n",
                current/60, current%60,
                next/60, next%60);

            current = next;
        }
    }
}