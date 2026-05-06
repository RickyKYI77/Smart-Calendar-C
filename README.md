Smart Calendar System (Data Structures Project)

This project is a terminal-based Smart Calendar System written in C, developed for a Data Structures course.
It allows users to manage events efficiently with features such as event scheduling, searching, editing, undo functionality, and persistent data storage.

The system uses fundamental data structures such as linked lists and stacks to manage calendar events dynamically.

Introduction

Managing events and schedules is an essential part of daily life. Traditional calendars often lack:

Quick searching of events
Category-based organization
Priority management
Undo functionality after deletion
Persistent storage when the program closes

This Smart Calendar System solves these issues by:

Using a Linked List to store events dynamically
Using a Stack to track deleted events for Undo
Providing search functions by keyword and category
Allowing users to edit events easily
Saving data to a text file for persistence
Overview

This application enables users to organize events efficiently through a command-line interface.

Users can:

Add events with date, category, and priority
Delete and undo deleted events
Search events by keyword or category
Edit existing events
View a dynamic monthly calendar
Automatically mark days with events using *
Save and load events from a file

This project demonstrates how data structures can be used to build practical real-world applications.

Features
Event Management
Add New Event
Edit Existing Event
Delete Event
Undo Last Deleted Event
Smart Searching
Search Events by Keyword
Search Events by Category
View events sorted by date
Dynamic Calendar Display
Monthly calendar display
Dates with events marked using *
Automatic calendar update after adding or deleting events
Data Persistence
Save events to text file
Load events automatically when the program starts
Prevent data loss after exiting the program
Data Structures Used
Data Structure	Purpose	Time Complexity
Linked List	Store events dynamically	Insert: O(n), Search: O(n)
Stack	Store deleted events for Undo	Push/Pop: O(1)
File System (.txt)	Persistent event storage	Read/Write: O(n)
File Structure
Smart-Calendar-System/
│
├── src/
│   ├── main.c          # Program entry point and menu
│   ├── calendar.c      # Event operations and calendar display
│   ├── calendar.h      # Event structures and function declarations
│   ├── file.c          # File save/load functions
│   └── file.h          # File operation declarations
│
├── data/
│   └── calendar_data.txt   # Stored event data
│
├── README.md
└── .gitignore
How to Run the Code
Requirements
C Compiler (GCC recommended)
All .c and .h files in the correct folders
Compilation

Run the following command:

gcc -o calendar src/main.c src/calendar.c src/file.c
Run the Program
MacOS / Linux
./calendar
Windows
calendar.exe
Sample Menu
========== SMART CALENDAR ==========

1. Add Event
2. Delete Event
3. Undo Delete
4. Search by Keyword
5. Search by Category
6. Edit Event
7. Exit

Enter choice:
Example Calendar Display
        APRIL 2026
=========================
Sun Mon Tue Wed Thu Fri Sat
            1   2   3
 4   5*  6   7   8   9  10
11  12   13  14* 15  16  17
18  19   20  21  22  23  24
25  26   27  28  29  30
=========================

* = Event scheduled
Test Cases
Test Case 1 — Add Event

Input:

Option: 1
Title: Assignment Submission
Date: 5
Category: School
Priority: 3

Output:

Event added successfully!
Test Case 2 — Delete Event

Input:

Option: 2
Event Title: Assignment Submission

Output:

Event deleted successfully!
Test Case 3 — Undo Delete

Input:

Option: 3

Output:

Last deleted event restored successfully!
Test Case 4 — Search Event

Input:

Option: 4
Keyword: Assignment

Output:

Assignment Submission | Date: 5 | Category: School | Priority: 3
Edge Cases Tested
Deleting events that do not exist
Searching with no matching results
Undo when there is no deleted event
Invalid date inputs
Invalid priority values
Empty calendar operations
Group Members
Name	Role / Responsibilities
Member 1	Event Management Functions (Add, Delete, Edit)
Member 2	Search Functions, Undo Stack, File Storage
Member 3	Calendar Display, Program Flow, System Documentation
Project Documentation

Report, flowcharts, and presentation slides were created collaboratively by all team members.

The project demonstrates the practical use of data structures such as linked lists and stacks in a real-world application.
