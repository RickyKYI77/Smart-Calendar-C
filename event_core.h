#ifndef EVENT_CORE_H
#define EVENT_CORE_H

// ================= DATA STRUCTURES =================

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

struct StackNode {
    struct Event* event;
    struct StackNode* next;
};

struct Calendar {
    struct Event* head;
    struct StackNode* deletedStack;
    int nextID;
};

// ================= CORE OPERATIONS =================

struct Event* createEvent(struct Calendar* cal);
void insertEvent(struct Calendar* cal, struct Event* e);
void addEvent(struct Calendar* cal);
void deleteEvent(struct Calendar* cal);
void undoDelete(struct Calendar* cal);
void editEvent(struct Calendar* cal);
int hasOverlap(struct Calendar* cal, struct Event* newEvent);
void freeAllEvents(struct Calendar* cal);

#endif