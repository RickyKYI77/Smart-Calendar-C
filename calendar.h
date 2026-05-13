#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// ================= FUNCTIONS =================
void addEvent(struct Calendar* cal);
void deleteEvent(struct Calendar* cal);
void undoDelete(struct Calendar* cal);

void searchByKeyword(struct Calendar* cal);
void searchByCategory(struct Calendar* cal);
void searchByDate(struct Calendar* cal);
void showFreeTimeSlots(struct Calendar* cal);

void displayCalendar(struct Calendar* cal);
void showAllEvents(struct Calendar* cal);
void showCategoryTree(struct Calendar* cal);

void saveToFile(struct Calendar* cal, const char* filename);
void loadFromFile(struct Calendar* cal, const char* filename);

int hasOverlap(struct Calendar* cal, struct Event* newEvent);

#endif