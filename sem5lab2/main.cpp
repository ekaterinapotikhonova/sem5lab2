﻿#define _CRT_SECURE_NO_WARNINGS
#include "note.h"

int main() {
    const int MAX_NOTES = 100;
    NOTE** phoneBook = new NOTE * [MAX_NOTES];
    int numNotes = 0;

    int choice;
    do {
        std::cout << "\nMenu:\n"
            "1. Add a new note\n"
            "2. View notes whose birthdays are in a specific month\n"
            "3. View all notes\n"
            "4. Edit a note\n"
            "5. Delete a note\n"
            "6. Exit\n"
            "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:  // Add a new note
            if (numNotes < MAX_NOTES) {
                NOTE* newNote = new NOTE("", "", "", 0, 0, 0);
                std::cin >> *newNote;
                NOTE::insertSorted(phoneBook, numNotes, newNote);
                std::cout << "Note added successfully.\n";
            }
            else {
                std::cout << "Phone book is full.\n";
            }
            break;

        case 2:  // View notes whose birthdays are in a specific month
        {
            int targetMonth;
            std::cout << "Enter the month (1-12): ";
            std::cin >> targetMonth;

            bool found = false;
            for (int i = 0; i < numNotes; ++i) {
                if (phoneBook[i]->getBirthday()[1] == targetMonth) {
                    std::cout << *phoneBook[i] << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "No notes with birthdays in the specified month.\n";
            }
        }
        break;


        case 3:  // View all notes
            if (numNotes > 0) {
                std::cout << "\nAll Notes:\n";
                for (int i = 0; i < numNotes; ++i) {
                    std::cout << *phoneBook[i] << std::endl;
                }
            }
            else {
                std::cout << "No notes available.\n";
            }
            break;

        case 4:  // Edit a note
            int editIndex;
            std::cout << "Enter the index of the note to edit (1-" << numNotes << "): ";
            std::cin >> editIndex;

            if (editIndex >= 1 && editIndex <= numNotes) {
                phoneBook[editIndex - 1]->editNote();
                std::cout << "Note edited successfully.\n";
            }
            else {
                std::cout << "Invalid index.\n";
            }
            break;

        case 5:  // Delete a note
            int deleteIndex;
            std::cout << "Enter the index of the note to delete (1-" << numNotes << "): ";
            std::cin >> deleteIndex;

            if (deleteIndex >= 1 && deleteIndex <= numNotes) {
                delete phoneBook[deleteIndex - 1];
                for (int i = deleteIndex - 1; i < numNotes - 1; ++i) {
                    phoneBook[i] = phoneBook[i + 1];
                }
                --numNotes;
                std::cout << "Note deleted successfully.\n";
            }
            else {
                std::cout << "Invalid index.\n";
            }
            break;

        case 6:  // Exit
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";

        }

    } while (choice != 6);

    // Clean up memory
    for (int i = 0; i < numNotes; ++i) {
        delete phoneBook[i];
    }
    delete[] phoneBook;

    return 0;
}