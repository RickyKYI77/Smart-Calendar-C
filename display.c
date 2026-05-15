#include <stdio.h>
#include "display.h"
#include "calendar.h"

// ================= GET EVENT COUNT FOR A DAY =================
int getEventCount(struct Calendar* cal, int day) {
    struct Event* current = cal->head;
    int count = 0;

    while (current != NULL) {
        if (current->day == day) {
            count++;
        }
        current = current->next;
    }

    return count;
}

// ================= DISPLAY CALENDAR =================
void displayCalendar(struct Calendar* cal) {

    printf("\n        APRIL 2026\n");
    printf("=========================\n");
    printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // April 2026 starts on Wednesday (offset = 3)
    int firstDayOffset = 3;

    for (int i = 0; i < firstDayOffset; i++) {
        printf("    ");
    }

    for (int day = 1; day <= 30; day++) {

        int eventCount = getEventCount(cal, day);

        if (eventCount == 0) {
            printf("%-6d  ", day);
        } else if (eventCount == 1) {
            printf("%2d* ", day);
        } else {
            printf("%2d*%d", day, eventCount);
        }

        // spacing fix for alignment
        if (eventCount < 10) {
            printf(" ");
        }

        // new line after Saturday
        if ((day + firstDayOffset) % 7 == 0) {
            printf("\n");
        }
    }

    printf("\n=========================\n");
    printf("* = Event scheduled | number = event count\n");
    printf("Updates automatically after add/delete/edit\n");
}
