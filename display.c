#include "calendar.h"

static int getEventCount(struct Calendar* cal, int day) {
    struct Event* c = cal->head;
    int count = 0;

    while (c) {
        if (c->day == day) count++;
        c = c->next;
    }
    return count;
}

void displayCalendar(struct Calendar* cal) {

    printf("\n========== SMART CALENDAR ==========\n");
    printf("        APRIL 2026\n");
    printf("=========================\n");
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    int offset = 3; // April 2026 starts Wednesday

    for (int i = 0; i < offset; i++)
        printf("    ");

    for (int day = 1; day <= 30; day++) {

        int count = getEventCount(cal, day);

        if (count == 0)
            printf("%2d  ", day);
        else if (count == 1)
            printf("%2d* ", day);
        else
            printf("%2d*%d", day, count);

        if ((day + offset) % 7 == 0)
            printf("\n");
    }

    printf("\n=========================\n");
    printf("* = Event scheduled (number = event count)\n");
    printf("Working hours: 9:00 AM - 5:00 PM\n");
}