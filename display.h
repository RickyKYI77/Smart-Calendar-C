#ifndef DISPLAY_H
#define DISPLAY_H

#include "calendar.h"

void displayCalendar(struct Calendar* cal);
int getEventCount(struct Calendar* cal, int day);

#endif