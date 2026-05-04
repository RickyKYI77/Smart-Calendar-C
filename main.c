#include <stdio.h>
#include "calendar.h"

int main() {
    struct Calendar cal = {NULL, NULL, 1};
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEvent(&cal); break;
            case 2: deleteEvent(&cal); break;
            case 3: undoDelete(&cal); break;
            case 4: showAllEvents(&cal); break;
            case 5: editEvent(&cal); break;
            case 6: return 0;
            default: printf("Invalid.\n");
        }
    }
}