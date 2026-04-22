void searchByCategory(struct Calendar* cal) {
    char category[50];
    printf("Enter category: ");
    scanf(" %[^\n]", category);

    struct Event* current = cal->head;
    int found = 0;

    printf("\nCategory: %s (sorted by date)\n", category);

    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            printf("%s | Date: %d | Priority: %d\n",
                   current->title, current->day, current->priority);
            found = 1;
        }
        current = current->next;
    }

    if (!found) printf("No events found.\n");
}

// ================= EDIT FUNCTION =================

void editEvent(struct Calendar* cal) {
    int day;
    printf("Enter date to edit: ");
    scanf("%d", &day);

    struct Event* current = cal->head;
    int index = 1;

    while (current != NULL) {
        if (current->day == day) {
            printf("%d. %s\n", index, current->title);
            index++;
        }
        current = current->next;
    }

    if (index == 1) {
        printf("No events found.\n");
        return;
    }

    int choice;
    printf("Enter event number to edit: ");
    scanf("%d", &choice);

    current = cal->head;
    index = 1;

    while (current != NULL) {
        if (current->day == day) {
            if (index == choice) {
                printf("Enter new title: ");
                scanf(" %[^\n]", current->title);

                printf("Enter new date: ");
                scanf("%d", &current->day);

                printf("Enter new category: ");
                scanf(" %[^\n]", current->category);

                printf("Enter new priority: ");
                scanf("%d", &current->priority);

                printf("Event updated successfully!\n");
                saveToFile(cal, "calendar_data.txt"); // Save immediately
                return;
            }
            index++;
        }
        current = current->next;
    }
}

// ================= CALENDAR DISPLAY =================

int hasEvent(struct Calendar* cal, int day) {
    struct Event* current = cal->head;
    while (current != NULL) {
        if (current->day == day)
            return 1;
        current = current->next;
    }
    return 0;
}

void displayCalendar(struct Calendar* cal) {
    printf("\n        APRIL 2026\n");
    printf("=========================\n");
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    // April 2026 starts on Wednesday (adjust as needed)
    int firstDayOffset = 3; // 0=Sunday, 3=Wednesday for April 1, 2026
    
    // Print initial spaces
    for (int i = 0; i < firstDayOffset; i++) {
        printf("    ");
    }
    
    // Print days 1-30 (April has 30 days)
    for (int day = 1; day <= 30; day++) {
        if (hasEvent(cal, day))
            printf("%2d* ", day);
        else
            printf("%2d  ", day);
        
        // New line after Saturday
        if ((day + firstDayOffset) % 7 == 0)
            printf("\n");
    }
    printf("\n=========================\n");
    printf("* = Event scheduled\n");
}

// ================= MEMORY CLEANUP =================

void freeAllEvents(struct Calendar* cal) {
    struct Event* current = cal->head;
    while (current != NULL) {
        struct Event* temp = current;
        current = current->next;
        free(temp);
    }
    
    struct StackNode* stackCurrent = cal->deletedStack;
    while (stackCurrent != NULL) {
        struct StackNode* temp = stackCurrent;
        stackCurrent = stackCurrent->next;
        free(temp->event);
        free(temp);
    }
    
    cal->head = NULL;
    cal->deletedStack = NULL;
}
