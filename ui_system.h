#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

#include "calendar.h"

// UI only
void displayMenu();
void showAllEvents(struct Calendar* cal);
void showCategoryTree(struct Calendar* cal);

#endif