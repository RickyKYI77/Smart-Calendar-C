#include <stdio.h>
#include "calendar.h"
#include "event_core.h"
#include "search_algorithms.h"
#include "display.h"
#include "fileio.h"

// ================= MENU =================
void displayMenu() {
    printf("\n========== MENU ==========\n");
    printf("1. Add Event\n");
    printf("2. Delete Event\n");
    printf("3. Undo Delete\n");
    printf("4. Search by Keyword\n");
    printf("5. Search by Category\n");
    printf("6. Search by Date\n");
    printf("7. Show Free Time Slots\n");
    printf("8. Show Category Tree\n");
    printf("9. Edit Event\n");
    printf("10. Show All Events\n");
    printf("11. Exit\n");
    printf("Enter choice: ");
}

// ================= MAIN =================
int main() {

    struct Calendar cal;

    cal.head = NULL;
    cal.deletedStack = NULL;
    cal.nextID = 1;

    int choice;

    // Load saved data
    loadFromFile(&cal, "calendar_data.txt");

    while (1) {

        printf("\n========== SMART CALENDAR ==========\n");
        displayCalendar(&cal);

        displayMenu();
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addEvent(&cal);
                saveToFile(&cal, "calendar_data.txt");
                break;

            case 2:
                deleteEvent(&cal);
                saveToFile(&cal, "calendar_data.txt");
                break;

            case 3:
                undoDelete(&cal);
                saveToFile(&cal, "calendar_data.txt");
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
                saveToFile(&cal, "calendar_data.txt");
                break;

            case 10:
                showAllEvents(&cal);
                break;

            case 11:
                saveToFile(&cal, "calendar_data.txt");
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}