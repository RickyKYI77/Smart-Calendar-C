#ifndef CALENDAR_H
#define CALENDAR_H

struct Event {
    int id;
    int day, month, year;
    int startHour, startMinute;
    int endHour, endMinute;
    char title[100];
    char category[50];
    int priority;
    struct Event* next;
};

struct Calendar {
    struct Event* head;
};

#endif