#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "calendar.h"

void searchByKeyword(struct Calendar* cal);
void searchByCategory(struct Calendar* cal);
void searchByDate(struct Calendar* cal);
void showFreeTimeSlots(struct Calendar* cal);
void showCategoryTree(struct Calendar* cal);

#endif