#ifndef FILE_H
#define FILE_H

#include "calendar.h"

void saveToFile(struct Calendar* cal, const char* filename);
void loadFromFile(struct Calendar* cal, const char* filename);

#endif