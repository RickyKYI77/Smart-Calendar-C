#include "calendar.h"
#include "event_core.h"
#include "fileio.h"
#include "display.h"
#include <stdio.h>

int main() {
    struct Calendar cal = {NULL, NULL, 1};

    loadFromFile(&cal, "calendar_data.txt");

    int choice;

    while (1) {
        displayCalendar(&cal);
        displayMenu();

        scanf("%d", &choice);

        switch (choice) {
            case 1: addEvent(&cal); break;
            case 2: deleteEvent(&cal); break;
            case 3: undoDelete(&cal); break;
            case 4: break;
            case 9: editEvent(&cal); break;
            case 11:
                saveToFile(&cal, "calendar_data.txt");
                return 0;
        }
    }
}