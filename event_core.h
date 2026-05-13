#ifndef EVENT_CORE_H
#define EVENT_CORE_H

#include "calendar.h"

struct Event* createEvent(struct Calendar* cal);
void insertEvent(struct Calendar* cal, struct Event* e);
void addEvent(struct Calendar* cal);
void deleteEvent(struct Calendar* cal);
void undoDelete(struct Calendar* cal);
void editEvent(struct Calendar* cal);

int hasOverlap(struct Calendar* cal, struct Event* newEvent);
int timeOverlap(int start1, int end1, int start2, int end2);

#endif