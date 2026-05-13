#ifndef EVENT_CORE_H
#define EVENT_CORE_H

#include "calendar.h"

// ================= EVENT FUNCTIONS =================
struct Event* createEvent(struct Calendar* cal);

void addEvent(struct Calendar* cal);
void insertEvent(struct Calendar* cal, struct Event* e);

void deleteEvent(struct Calendar* cal);
void undoDelete(struct Calendar* cal);

void editEvent(struct Calendar* cal);

void pushDeleted(struct Calendar* cal, struct Event* e);
struct Event* popDeleted(struct Calendar* cal);

void pushDeleted(struct Calendar* cal, struct Event* e);
struct Event* popDeleted(struct Calendar* cal);

void showAllEvents(struct Calendar* cal);
void showCategoryTree(struct Calendar* cal);

// ================= OVERLAP FUNCTIONS =================
int timeOverlap(int start1, int end1, int start2, int end2);
int hasOverlap(struct Calendar* cal, struct Event* newEvent);

#endif