#ifndef FILEIO_H
#define FILEIO_H

#include "event_core.h"

void saveToFile(struct Calendar* cal, const char* filename);
void loadFromFile(struct Calendar* cal, const char* filename);

#endif