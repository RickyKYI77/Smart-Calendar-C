#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"
#include "file.h"

// ================= MENU =================

void displayMenu() {
    printf("\n========== MENU ==========\n");
    printf("1. Add Event\n");
    printf("2. Delete Event\n");
    printf("3. Undo Delete\n");
    printf("4. Search by Keyword\n");
    printf("5. Search by Category\n");
    printf("6. Edit Event\n");
    printf("7. Exit\n");
    printf("Enter choice: ");
}

// ================= MAIN =================

int main() {
    struct Calendar myCalendar = {NULL, NULL};
    int choice;
    
    loadFromFile(&myCalendar, "calendar_data.txt");
    
    while (1) {
        printf("\n========== SMART CALENDAR ==========");
        displayCalendar(&myCalendar);
        displayMenu();

        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                addEvent(&myCalendar); 
                break;
            case 2: 
                deleteEvent(&myCalendar); 
                break;
            case 3: 
                undoDelete(&myCalendar); 
                break;
            case 4: 
                searchByKeyword(&myCalendar); 
                break;
            case 5: 
                searchByCategory(&myCalendar); 
                break;
            case 6: 
                editEvent(&myCalendar); 
                break;
            case 7:
                saveToFile(&myCalendar, "calendar_data.txt");
                freeAllEvents(&myCalendar);
                printf("Calendar saved. Exiting program...\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}
