#include <stdio.h>

#include "calendar.h"

int main() {

    struct Calendar cal = {NULL, NULL, 1};

    int choice;

    loadFromFile(&cal, "calendar.txt");

    while (1) {

        displayCalendar(&cal);

        displayMenu();

        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addEvent(&cal);
                saveToFile(&cal, "calendar.txt");
                break;

            case 2:
                deleteEvent(&cal);
                saveToFile(&cal, "calendar.txt");
                break;

            case 3:
                undoDelete(&cal);
                saveToFile(&cal, "calendar.txt");
                break;

            case 4:
                showAllEvents(&cal);
                break;

            case 5:
                editEvent(&cal);
                saveToFile(&cal, "calendar.txt");
                break;

            case 6:
                saveToFile(&cal, "calendar.txt");
                return 0;

            default:
                printf("Invalid.\n");
        }
    }
}