#ifndef CALENDAR_H
#define CALENDAR_H

// Event structure
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

// Calendar structure
struct StackNode;

struct Calendar {
    struct Event* head;
    struct StackNode* deletedStack;
};

// Function declarations ONLY
void addEvent(struct Calendar* cal);
void deleteEvent(struct Calendar* cal);
void undoDelete(struct Calendar* cal);
void displayCalendar(struct Calendar* cal);

#endif