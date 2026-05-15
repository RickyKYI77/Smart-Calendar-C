# Smart Calendar System (Data Structures Project)

This project is a **terminal-based Smart Calendar Management System written in C**, developed for the **CPE112 Data Structures** course.

The system allows users to efficiently manage daily events with features such as scheduling, conflict detection, undo functionality, category organization, and automatic data storage using file handling.

The project demonstrates the practical use of the following **Data Structures and Algorithms**:

- Linked Lists  
- Stacks  
- Binary Search Trees  
- Sorting Algorithms  
- File Handling in C  

---

# Introduction

Managing events and schedules can become complicated when multiple tasks occur within limited time periods. Traditional calendars often lack features such as automatic conflict detection, dynamic scheduling, and structured data organization.

The **Smart Calendar System** was designed to address these challenges by implementing classic **data structures** to manage events efficiently. The program allows users to add, search, edit, and organize events while ensuring scheduling conflicts are avoided.

By combining **linked lists, stacks, binary search trees, and sorting algorithms**, the system provides an organized and reliable way to manage daily schedules through a **command-line interface**.

---

# Overview

The Smart Calendar System helps users organize their schedules by allowing them to:

- Add and manage events
- Detect scheduling conflicts automatically
- Search events efficiently
- View free time slots during working hours
- Undo deleted events
- Automatically save and load event data

The project focuses on efficient event management using classic **data structures and algorithms**.

---

# Features

## Event Management
- Add events with:
  - Title
  - Date
  - Start and End Time
  - Category
  - Priority Level
- Delete events using **Event ID**
- Undo the last deleted event using **stack operations**

## Smart Scheduling
- Automatic **time conflict detection**
- Prevents overlapping events
- Displays available **free time slots**

## Search Functions

Users can search events by:

- Keyword
- Category
- Specific Date

## Data Persistence

- Events are stored in a **text file**
- Data is **automatically loaded when the program starts**

---

# Data Structures Used

| Data Structure | Purpose | Time Complexity |
|----------------|--------|----------------|
| Linked List | Store events dynamically | Insert: O(1), Search: O(n) |
| Stack | Undo deleted events | Push/Pop: O(1) |
| Binary Search Tree | Organize event categories | Average: O(log n) |
| Arrays | Temporary sorting of events by time | Sorting: O(n²) (Bubble Sort) |

---

# System Architecture


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


## Event Structure

```
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
```

# Program Modules

The Smart Calendar System is organized into several modules. Each module is responsible for a specific part of the system to maintain clean structure and modular programming.

## Event Management

This module handles the creation, insertion, deletion, and restoration of events within the calendar. Events are stored using a **linked list** to allow dynamic memory allocation.

Key functions include:

- `createEvent()` – Creates a new event structure and initializes its values  
- `insertEvent()` – Inserts the event into the linked list in sorted order based on date and time  
- `addEvent()` – Collects user input and adds a new event to the calendar  
- `deleteEvent()` – Removes an event using its unique **Event ID**  
- `undoDelete()` – Restores the most recently deleted event using **stack operations**

---

## Search System

This module provides functions that allow users to locate events quickly using different criteria.

Key functions include:

- `searchByKeyword()` – Searches for events containing a specific keyword in the title  
- `searchByCategory()` – Displays events belonging to a selected category  
- `searchByDate()` – Shows events scheduled on a particular date  

---

## Scheduling Logic

This module manages time-related operations and ensures that event schedules do not conflict.

Key functions include:

- `hasOverlap()` – Detects time conflicts between events  
- `showFreeTimeSlots()` – Displays available time slots during working hours  

The system checks for overlapping events before inserting a new event to ensure scheduling conflicts are avoided.

---

## File Handling

This module manages **data persistence** so that events remain saved even after the program exits.

Key functions include:

- `saveToFile()` – Saves all events to a file for persistent storage  
- `loadFromFile()` – Loads saved events from the file when the program starts  

Event data is stored in a text file (`calendar_data.txt`) and automatically loaded whenever the program is executed.

```
## Example Program Output
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

## Challenges Faced

- Handling time overlap detection
- Managing dynamic memory allocation
- Keeping events sorted by date and time
- Implementing undo functionality with stacks
- Maintaining persistent storage with file handling


## Future Improvements

Possible upgrades to the system:

1. Graphical User Interface (GUI)
2. Monthly calendar view
3. Event reminders
4. Mobile or web integration
5. Multi-user scheduling
6. Database storage instead of text files

## Group Members

| Name | Student ID | GitHub | Responsibilities | Key Functions |
|-----|------------|--------|------------------|---------------|
| **Thaw Lin Htut** | 68070503408 | [GitHub Profile](https://github.com/thawlinhtut) | • File saving and loading system <br> • Menu design and user interaction <br> • Calendar and event display <br> • Category Tree implementation using Binary Search Tree (BST) | `saveToFile()` <br> `loadFromFile()` <br> `displayCalendar()` <br> `displayMenu()` <br> `showAllEvents()` <br> `showCategoryTree()` |
| **Aye Theingi Myo** | 68070503463 | [GitHub Profile](https://github.com/AyeTheingiMyo) | • Event search features <br> • Event sorting using Bubble Sort <br> • Free time slot calculation | `searchByKeyword()` <br> `searchByCategory()` <br> `searchByDate()` <br> `showFreeTimeSlots()` |
| **Kyi Phyu Thaw** | 68070503464 | [GitHub Profile](https://github.com/RickyKYI77) | • Linked List for event storage <br> • Event insertion sorted by date and time <br> • Delete and undo operations using Stack <br> • Time conflict detection <br> • Memory management and ID handling | `createEvent()` <br> `insertEvent()` <br> `deleteEvent()` <br> `undoDelete()` <br> `hasOverlap()` <br> `timeOverlap()` <br> `freeAllEvents()` |

## Learning Outcomes

This project helped demonstrate:

- Practical use of Data Structures
- Efficient memory management in C
- Building real-world applications with algorithms
- Structuring a modular C program


## Acknowledgement

We would like to thank our professor for giving us valuable advice and guidance throughout the development of this project. We also appreciate the cooperation and teamwork among our group members in completing the Smart Calendar System.
