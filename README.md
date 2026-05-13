Smart Calendar System

A console-based Smart Calendar Management System written in C that allows users to efficiently manage daily events using Data Structures and Algorithms.
The system supports event scheduling, conflict detection, undo functionality, category organization, and automatic storage using file handling.

This project demonstrates the practical use of:
1.Linked Lists
2.Stacks
3.Binary Search Trees
4.Sorting Algorithms
5.File Handling in C

Project Overview

The Smart Calendar System helps users organize their schedules by allowing them to:
-Add and manage events
-Detect scheduling conflicts
-Search events efficiently
-View free time slots during working hours
-Undo deleted events
-Automatically save and load data
The project focuses on efficient event organization using classic data structures.

Key Features

1.Event Management
Add events with:
-Title
-Date
-Start and end time
-Category
-Priority level
-Delete events using Event ID
-Undo the last deleted event using stack operations
2.Smart Scheduling
-Automatic time conflict detection
-Prevents overlapping events
-Shows available free time slots
3.Search Functions
-Search by keyword
-Search by category
-Search by specific date
4.Data Persistence
-Events are stored in a file system
-Data automatically loads when the program starts
5.Data Structures Used
Data Structure                  Purpose
Linked List    ----->	        Store events dynamically
Stack ----->                    Undo deleted events
Binary Search Tree ----->	Organize event categories
Arrays ----->                   Temporary sorting of events by time

## System Architecture

```
                +---------------------+
                |        User         |
                +----------+----------+
                           |
                           v
                +---------------------+
                |    Calendar System  |
                +----------+----------+
                           |
    +----------------------+----------------------+
    |                      |                      |
    v                      v                      v
+--------------+      +----------------+      +------------------+
| Linked List  |      |      Stack     |      |  Binary Search   |
|  (Events)    |      | (Undo Delete)  |      | Tree (Categories)|
+--------------+      +----------------+      +------------------+
        |
        v
+-----------------------+
|      File Storage     |
|   calendar_data.txt   |
+-----------------------+
```


Event Structure

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

Program Modules

1.Event Management
-createEvent()
-insertEvent()
-addEvent()
-deleteEvent()
-undoDelete()
2.Search System
-searchByKeyword()
-searchByCategory()
-searchByDate()
3.Scheduling Logic
-hasOverlap() – detects time conflicts
-showFreeTimeSlots() – displays available time slots
4.File Handling
-saveToFile() – saves events
-loadFromFile() – loads saved events

Free Time Slot Detection

The system calculates free time slots by:
-Collecting events for the selected day
-Sorting them by start time
-Comparing event times with working hours (9:00 AM – 5:00 PM)
-Detecting gaps between events

How to compile
gcc calendar.c -o calendar

How to Run
./calendar

## Program Startup Output

```
========== SMART CALENDAR ==========
        APRIL 2026
=========================
Sun Mon Tue Wed Thu Fri Sat
        1   2   3   4   5
 6   7   8   9  10  11  12
13  14  15  16  17  18  19
20  21  22  23  24  25  26
27  28  29  30
=========================
* = Event scheduled (number = event count on that day)
Working hours: 9:00 AM - 5:00 PM (Weekdays only)

========== MENU ==========
1. Add Event
2. Delete Event
3. Undo Delete
4. Search by Keyword
5. Search by Category
6. Search by Date
7. Show Free Time Slots
8. Show Category Tree
9. Edit Event
10. Show All Events
11. Exit
Enter choice:
```

Example Menu

1.Add Event
2.Delete Event
3.Undo Delete
4.Search by Keyword
5.Search by Category
6.Search by Date
7.Show Free TIme Slots
8.Show Categoty Tree
9.Edit Event
10.Show All Events
11.Exit

Challenges Faced

-Handling time overlap detection
-Managing dynamic memory allocation
-Keeping events sorted by date and time
-Implementing undo functionality with stacks
-Maintaining persistent storage with file handling

Future Improvements

Possible upgrades to the system:
1.Graphical User Interface (GUI)
2.Monthly calendar view
3.Event reminders
4.Mobile or web integration
5.Multi-user scheduling
6.Database storage instead of text files

Learning Outcomes

This project helped demonstrate:
-Practical use of Data Structures
-Efficient memory management in C
-Building real-world applications with algorithms
-Structuring a modular C program



