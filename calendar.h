#ifndef CALENDAR_H
#define CALENDAR_H

// ================= STRUCTURES =================

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

struct CategoryNode {
    char name[50];
    int eventCount;
    struct CategoryNode* left;
    struct CategoryNode* right;
};

#endif