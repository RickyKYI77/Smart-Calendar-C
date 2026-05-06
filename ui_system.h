#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H

struct Event {
    int id;
    int day, month, year;
    int startHour, startMinute;
    int endHour, endMinute;
    char title[100];
    char category[50];
    int priority;
    struct Event* next;
};

struct Calendar {
    struct Event* head;
};

void displayMenu();
void showAllEvents(struct Calendar* cal);
void saveToFile(struct Calendar* cal, const char* filename);
void loadFromFile(struct Calendar* cal, const char* filename);
void showCategoryTree(struct Calendar* cal);

#endif