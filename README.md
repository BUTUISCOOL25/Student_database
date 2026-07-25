# Student_database
This is a File management system of a students with there marks in every subject . # Student Record Management System

A simple console-based **Student Record Management System** written in C++.  
This program allows you to add, view, edit, and delete student records, while storing each student’s data in a separate text file.

The project is designed for beginners who want to practice:
- C++ structures
- file handling with `ifstream` and `ofstream`
- vectors
- string handling
- menu-driven programs
- basic input validation

## Features

- Add a new student record
- View all student records
- View a specific student record by roll number
- Edit an existing student record
- Delete a student record
- Store roll numbers in a separate index file
- Validate marks input between 0 and 100
- Prevent duplicate roll number conflicts
- Exit automatically after too many invalid menu choices

## Subjects Included

The program stores marks for these 5 subjects:

- Maths
- Science
- English
- Social Studies
- Computer Science

## Technologies Used

- C++
- Standard Library headers:
  - `<iostream>`
  - `<string>`
  - `<fstream>`
  - `<cstdio>`
  - `<vector>`
  - `<algorithm>`

The program uses the C++ file stream library for text-file storage and retrieval. [web:13][web:15]

## File Storage Format

The program stores data using plain text files:

- `roll_numbers.txt`  
  Stores the list of all student roll numbers.

- `<roll_number>.txt`  
  Stores the full record of an individual student.

Example:

```text
roll_numbers.txt
101.txt
102.txt
103.txt
```

A student file looks like this:

```text
Roll Number : 101
Name : John Doe
Maths:85
Science:90
English:78
Social Studies:88
Computer Science:95
```

## Program Flow

When the program starts, it shows a menu:

```text
1. Add student record
2. Show student records
3. Edit student record
4. Delete student record
5. Exit
```

### Add Record
- Enter a roll number.
- If the roll number already exists, the program gives options to:
  - edit the existing record,
  - use a different roll number,
  - delete the old record and create a new one,
  - or return to the main menu.
- Enter the student name.
- Enter marks for 5 subjects.
- Marks are validated to stay within 0 to 100.
- The record is saved into a text file.

### Show Records
You can:
- show all student records, or
- show one specific record by roll number.

### Edit Record
- Enter the roll number to edit.
- The existing record is displayed first.
- The old file is deleted.
- A new updated record is then saved with the same roll number.

### Delete Record
- Enter the roll number.
- Confirm deletion.
- The student file is removed.
- The roll number is also removed from `roll_numbers.txt`.

## Main Data Structure

The program uses a `struct` to store student information:

```cpp
struct student
{
    string roll_number;
    string name;
    int marks_in_subjects;[4]
};
```

This structure keeps:
- roll number
- student name
- marks in five subjects

## Functions Overview

### `load_roll_numbers()`
Reads all roll numbers from `roll_numbers.txt` into a vector.

### `save_roll_numbers(const vector<string> &rolls)`
Writes the updated roll number list back into `roll_numbers.txt`.

### `student_record_exists(string roll_number)`
Checks whether a record file already exists for a given roll number.

### `delete_student_record(const string &roll_number)`
Deletes the student’s file and removes the roll number from the index file.

### `save_student_to_file(const student &s)`
Saves one student record into a text file.

### `add_student_record()`
Adds a new student record with duplicate handling and marks validation.

### `show_student_records()`
Displays all records or a specific record.

### `edit_student_record()`
Edits an existing student record.

### `delete_student_menu()`
Deletes a student record after confirmation.

### `main()`
Runs the menu-driven program loop.

## Improvements Made in This Version

This version includes several useful improvements:

- Roll numbers are loaded into a `vector<string>` for easier management.
- Roll numbers are rewritten cleanly after delete or edit operations.
- Duplicate roll number handling is improved.
- Marks validation ensures values stay between 0 and 100.
- Record editing no longer relies on broken recursive behavior.
- Delete functionality has been added to the main menu.
- Repeated invalid menu choices are limited for safer execution.

## Compilation

### Using g++

Compile the program with:

```bash
g++ student_record.cpp -o student_record
```

Run it with:

```bash
./student_record
```

### On Windows

```bash
g++ student_record.cpp -o student_record.exe
student_record.exe
```

## Requirements

- A C++ compiler such as `g++`
- Terminal or command prompt
- Write permission in the program folder, because the program creates and updates text files through file streams opened in output mode. [web:14][web:15]

## Example Use Case

1. Add a student with roll number `101`
2. Enter the name and marks
3. Save the record
4. View the student later using roll number `101`
5. Edit or delete the record when needed

## Limitations

- Data is stored in plain text files, not in a database.
- No password protection or user authentication.
- No sorting by marks, rank, or subject.
- No graphical user interface.
- The program depends on correct user input for menu navigation.

## Possible Future Enhancements

- Add total marks and percentage calculation
- Add grade calculation
- Add search by name
- Add sorting of students by marks
- Export reports
- Use binary files or a database
- Add a GUI version using Qt or another framework

## Learning Concepts Covered

This project is helpful for understanding:

- structures in C++
- arrays inside structures
- vectors
- file handling with `ifstream` and `ofstream`
- text-based record storage

