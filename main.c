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
                break;

            case 2:
                deleteEvent(&cal);
                break;

            case 3:
                undoDelete(&cal);
                break;

            case 4:
                searchByKeyword(&cal);
                break;

            case 5:
                searchByCategory(&cal);
                break;

            case 6:
                searchByDate(&cal);
                break;

            case 7:
                showFreeTimeSlots(&cal);
                break;

            case 8:
                showCategoryTree(&cal);
                break;

            case 9:
                editEvent(&cal);
                break;

            case 10:
                showAllEvents(&cal);
                break;

            case 11:
                saveToFile(&cal, "calendar.txt");
                freeAllEvents(&cal);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }

        saveToFile(&cal, "calendar.txt");
    }
}