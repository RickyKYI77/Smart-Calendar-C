#ifndef CALENDAR_H
#define CALENDAR_H

#include "event_core.h"

// Search features
void searchByKeyword(struct Calendar* cal);
void searchByCategory(struct Calendar* cal);
void searchByDate(struct Calendar* cal);

// Scheduling
void showFreeTimeSlots(struct Calendar* cal);

// Category
void showCategoryTree(struct Calendar* cal);

// Memory management
void freeAllEvents(struct Calendar* cal);

#endif