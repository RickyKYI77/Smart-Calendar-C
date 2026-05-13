#ifndef DISPLAY_H
#define DISPLAY_H

#include "event_core.h"

void displayMenu();
void displayCalendar(struct Calendar* cal);
void showAllEvents(struct Calendar* cal);

#endif