#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "event_core.h"

// ================= SEARCH FUNCTIONS =================
void searchByKeyword(struct Calendar* cal);
void searchByCategory(struct Calendar* cal);
void searchByDate(struct Calendar* cal);

// ================= SCHEDULING ALGORITHM =================
void showFreeTimeSlots(struct Calendar* cal);

#endif