#define _CRT_SECURE_NO_WARNINGS
#include "note.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main() {
    const int MAX_NOTES = 100;
    NOTE** noteBook = new NOTE * [MAX_NOTES];
    int numNotes = 0;

    int exercise;
    do {
        std::cout << "\nMenu:\n"
            "1. Exercise 1\n"
            "2. Exercise 2\n"
            "3. Exit\n"
            "Enter your choice: ";
        std::cin >> exercise;
        switch (exercise) {
        case 1: {
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
                case 1: // Add a new note
                    if (numNotes < MAX_NOTES) {
                        NOTE* newNote = new NOTE("", "", "", 0, 0, 0);
                        std::cin >> *newNote;
                        NOTE::insertSorted(noteBook, numNotes, newNote);
                        std::cout << "Note added successfully.\n";
                    }
                    else {
                        std::cout << "Phone book is full.\n";
                    }
                    break;

                case 2: // View notes whose birthdays are in a specific month
                {
                    int targetMonth;
                    std::cout << "Enter the month (1-12): ";
                    std::cin >> targetMonth;

                    bool found = false;
                    for (int i = 0; i < numNotes; ++i) {
                        if (noteBook[i]->getBirthday()[1] == targetMonth) {
                            std::cout << *noteBook[i] << std::endl;
                            found = true;
                        }
                    }

                    if (!found) {
                        std::cout << "No notes with birthdays in the specified month.\n";
                    }
                }
                break;

                case 3: // View all notes
                    if (numNotes > 0) {
                        std::cout << "\nAll Notes:\n";
                        for (int i = 0; i < numNotes; ++i) {
                            std::cout << *noteBook[i] << std::endl;
                        }
                    }
                    else {
                        std::cout << "No notes available.\n";
                    }
                    break;

                case 4: // Edit a note
                    int editIndex;
                    std::cout << "Enter the index of the note to edit (1-" << numNotes << "): ";
                    std::cin >> editIndex;

                    if (editIndex >= 1 && editIndex <= numNotes) {
                        noteBook[editIndex - 1]->editNote();
                        std::cout << "Note edited successfully.\n";
                    }
                    else {
                        std::cout << "Invalid index.\n";
                    }
                    break;

                case 5: // Delete a note
                    int deleteIndex;
                    std::cout << "Enter the index of the note to delete (1-" << numNotes << "): ";
                    std::cin >> deleteIndex;

                    if (deleteIndex >= 1 && deleteIndex <= numNotes) {
                        delete noteBook[deleteIndex - 1];
                        for (int i = deleteIndex - 1; i < numNotes - 1; ++i) {
                            noteBook[i] = noteBook[i + 1];
                        }
                        --numNotes;
                        std::cout << "Note deleted successfully.\n";
                    }
                    else {
                        std::cout << "Invalid index.\n";
                    }
                    break;

                case 6: // Exit
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 6);

            // Clean up memory
            for (int i = 0; i < numNotes; ++i) {
                delete noteBook[i];
            }
            delete[] noteBook;

            return 0;
        }
        case 2: {
            std::string fileName;
            // Определяем флаг для повторного ввода
            bool repeatInput = true;
            while (repeatInput) {
                // Запрашиваем у пользователя ввести имя файла
                std::cout << "Enter file name : ";
                std::cin >> fileName;

                // Открываем файл для чтения
                std::ifstream inputFile(fileName);

                // Проверяем, успешно ли открыт файл
                if (inputFile.is_open()) {
                    repeatInput = false; // Файл успешно открыт, выходим из цикла
                    // Создаем строковый поток для хранения текста
                    std::ostringstream textStream;

                    // Считываем текст из файла в строковый поток
                    textStream << inputFile.rdbuf();

                    // Получаем текст из строкового потока
                    std::string text = textStream.str();

                    // Закрываем файл после считывания
                    inputFile.close();

                    // Флаг, указывающий, что предыдущий символ - не буква
                    bool prevNotAlpha = true;

                    // Заменяем первые буквы слов, начинающихся с гласной буквы, на прописные
                    for (std::size_t i = 0; i < text.length(); ++i) {
                        if (std::isalpha(text[i])) {
                            if (prevNotAlpha && isVowel(text[i])) {
                                text[i] = std::toupper(text[i]);
                            }
                            prevNotAlpha = false;
                        }
                        else {
                            prevNotAlpha = true;
                        }
                    }

                    // Выводим измененный текст на экран
                    std::cout << "Changed text :\n" << text << std::endl;
                }
                else {
                    std::cerr << "Failed to open file. Try again." << std::endl;
                }
            }
            break;
        }
        case 3:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (exercise != 3);

    return 0;
}
