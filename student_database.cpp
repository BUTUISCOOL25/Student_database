#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct student
{
    string roll_number;
    string name;
    int marks_in_subjects[5];
};

string subject_names[5] = {"Maths", "Science", "English", "Social Studies", "Computer Science"};

// [CHANGED] Reads all roll numbers from file into a vector for easier manipulation
vector<string> load_roll_numbers()
{
    vector<string> rolls;
    ifstream file("roll_numbers.txt");
    string line;
    while (getline(file, line))
    {
        if (!line.empty())
            rolls.push_back(line);
    }
    return rolls;
}

// [CHANGED] Saves the full roll number list back to file (used after delete/edit)
void save_roll_numbers(const vector<string> &rolls)
{
    ofstream file("roll_numbers.txt", ios::trunc);
    for (const string &r : rolls)
        file << r << "\n";
}

bool student_record_exists(string roll_number)
{
    string file_name = roll_number + ".txt";
    ifstream file(file_name);
    return file.is_open();
}

// [CHANGED] Also removes the roll number from roll_numbers.txt on delete
void delete_student_record(const string &roll_number)
{
    string file_name = roll_number + ".txt";
    if (remove(file_name.c_str()) == 0)
    {
        cout << "Record deleted successfully.\n";
    }
    else
    {
        cout << "Error deleting record.\n";
        return;
    }

    // Remove from roll_numbers.txt
    vector<string> rolls = load_roll_numbers();
    rolls.erase(remove(rolls.begin(), rolls.end(), roll_number), rolls.end());
    save_roll_numbers(rolls);
}

// [CHANGED] Extracted saving logic into its own function to avoid duplication
void save_student_to_file(const student &s)
{
    string file_name = s.roll_number + ".txt";
    ofstream file(file_name);
    if (file.is_open())
    {
        file << "Roll Number : " << s.roll_number << "\n";
        file << "Name : " << s.name << "\n";
        for (int i = 0; i < 5; i++)
        {
            file << subject_names[i] << ":" << s.marks_in_subjects[i] << "\n";
        }
        cout << "Student record saved successfully.\n";
    }
    else
    {
        cout << "Error opening the file.\n";
    }
}

// [CHANGED] Replaced recursion with a loop; fixed option 1 actually editing; fixed roll_numbers.txt duplication
void add_student_record()
{
    string roll_number;
    student new_student;

    // Loop instead of recursion for "try different roll number" case
    while (true)
    {
        cout << "Enter the roll number of the student: ";
        cin >> roll_number;
        new_student.roll_number = roll_number;

        if (!student_record_exists(roll_number))
            break; // No conflict, proceed

        cout << "A record with this roll number already exists.\n";
        cout << " 1. Edit the existing record\n";
        cout << " 2. Add a new record with a different roll number\n";
        cout << " 3. Delete this record and add a new one with the same roll number\n";
        cout << " 4. Return to the main menu\n";
        cout << "Enter your choice: ";
        int choice_add;
        cin >> choice_add;

        if (choice_add == 1)
        {
            // [CHANGED] Option 1 now actually edits: deletes file, keeps same roll number, continues below
            delete_student_record(roll_number);
            break;
        }
        else if (choice_add == 2)
        {
            continue; // Loop back and ask for a new roll number
        }
        else if (choice_add == 3)
        {
            cout << "Do you really want to delete the existing record? (Y/N): ";
            string confirm;
            cin >> confirm;
            if (confirm == "y" || confirm == "Y")
            {
                delete_student_record(roll_number);
                break;
            }
            else
            {
                cout << "Returning to main menu.\n";
                return;
            }
        }
        else
        {
            cout << "Returning to main menu.\n";
            return;
        }
    }

    // [CHANGED] Only append to roll_numbers.txt once, here, after conflict resolution
    vector<string> rolls = load_roll_numbers();
    if (find(rolls.begin(), rolls.end(), roll_number) == rolls.end())
    {
        rolls.push_back(roll_number);
        save_roll_numbers(rolls);
    }

    cout << "Enter the name of the student: ";
    cin.ignore();
    getline(cin, new_student.name);

    for (int i = 0; i < 5; i++)
    {
        // [CHANGED] Added validation: marks must be 0-100
        while (true)
        {
            cout << "Enter the marks for " << subject_names[i] << " (0-100): ";
            cin >> new_student.marks_in_subjects[i];
            if (new_student.marks_in_subjects[i] >= 0 && new_student.marks_in_subjects[i] <= 100)
                break;
            cout << "Invalid marks. Please enter a value between 0 and 100.\n";
        }
    }

    save_student_to_file(new_student);
    cout << "\n";
}

void show_student_records()
{
    cout << "1. Show all student records\n";
    cout << "2. Show a specific student record\n";
    cout << "Enter your choice: ";
    int choice_show;
    cin >> choice_show;

    switch (choice_show)
    {
    case 1:
    {
        vector<string> rolls = load_roll_numbers();
        if (rolls.empty())
        {
            cout << "No student records found.\n";
            break;
        }
        for (const string &roll : rolls)
        {
            ifstream record_file(roll + ".txt");
            if (!record_file.is_open())
            {
                cout << "Warning: record for roll " << roll << " not found on disk.\n";
                continue;
            }
            string line;
            // [CHANGED] Removed the extra endl inside the loop — cleaner output
            while (getline(record_file, line))
                cout << line << "\n";
            cout << "-----------------------------\n";
        }
        break;
    }
    case 2:
    {
        cout << "Enter the roll number: ";
        string roll_number;
        cin >> roll_number;

        if (student_record_exists(roll_number))
        {
            ifstream record_file(roll_number + ".txt");
            string line;
            while (getline(record_file, line))
                cout << line << "\n";
        }
        else
        {
            cout << "No record found for this roll number.\n";
        }
        break;
    }
    default:
        cout << "Invalid input.\n";
        return;
    }
    cout << "\n";
}

// [CHANGED] edit_student_record now asks for roll number, deletes properly, then re-adds under the same roll number
void edit_student_record()
{
    cout << "Enter the roll number you want to edit: ";
    string roll_number;
    cin >> roll_number;

    if (!student_record_exists(roll_number))
    {
        cout << "No record found for this roll number.\n";
        return;
    }

    // Show existing record before editing
    cout << "\nCurrent record:\n";
    ifstream record_file(roll_number + ".txt");
    string line;
    while (getline(record_file, line))
        cout << line << "\n";
    record_file.close();
    cout << "\n";

    delete_student_record(roll_number);

    // Pre-fill roll number so add_student_record doesn't ask again
    student updated;
    updated.roll_number = roll_number;

    vector<string> rolls = load_roll_numbers();
    if (find(rolls.begin(), rolls.end(), roll_number) == rolls.end())
    {
        rolls.push_back(roll_number);
        save_roll_numbers(rolls);
    }

    cout << "Enter the new name of the student: ";
    cin.ignore();
    getline(cin, updated.name);

    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            cout << "Enter the marks for " << subject_names[i] << " (0-100): ";
            cin >> updated.marks_in_subjects[i];
            if (updated.marks_in_subjects[i] >= 0 && updated.marks_in_subjects[i] <= 100)
                break;
            cout << "Invalid marks. Please enter a value between 0 and 100.\n";
        }
    }

    save_student_to_file(updated);
    cout << "\n";
}

// [CHANGED] Added delete option to main menu
void delete_student_menu()
{
    cout << "Enter the roll number to delete: ";
    string roll_number;
    cin >> roll_number;

    if (!student_record_exists(roll_number))
    {
        cout << "No record found for this roll number.\n";
        return;
    }

    cout << "Are you sure you want to delete this record? (Y/N): ";
    string confirm;
    cin >> confirm;
    if (confirm == "y" || confirm == "Y")
        delete_student_record(roll_number);
    else
        cout << "Delete cancelled.\n";
}

int main()
{
    int choice;
    bool continue_program = true;
    int invalid_choice_count = 0;

    while (continue_program)
    {
        cout << "1. Add student record\n";
        cout << "2. Show student records\n";
        cout << "3. Edit student record\n";
        cout << "4. Delete student record\n"; // [CHANGED] Added delete option
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_student_record();
            invalid_choice_count = 0;
            break;
        case 2:
            show_student_records();
            invalid_choice_count = 0;
            break;
        case 3:
            edit_student_record();
            invalid_choice_count = 0;
            break;
        case 4:
            delete_student_menu();
            invalid_choice_count = 0;
            break;
        case 5:
            continue_program = false;
            break;
        default:
            invalid_choice_count++;
            if (invalid_choice_count >= 3)
            {
                cout << "Too many invalid choices. Exiting.\n";
                continue_program = false;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n\n";
            }
            break;
        }
    }

    return 0;
}