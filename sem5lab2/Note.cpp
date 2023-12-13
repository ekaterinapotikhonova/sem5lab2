#define _CRT_SECURE_NO_WARNINGS
#include "note.h"
#include <cstring>

NOTE::NOTE(const char* _firstName, const char* _lastName, const char* _phoneNumber, int day, int month, int year)
    : firstName(nullptr), lastName(nullptr), phoneNumber(nullptr) {
    std::cout << "Constructor called for a new note" << std::endl;

    // Проверка на успешность выделения памяти
    try {
        firstName = new char[strlen(_firstName) + 1];
        strcpy(firstName, _firstName);

        lastName = new char[strlen(_lastName) + 1];
        strcpy(lastName, _lastName);

        phoneNumber = new char[strlen(_phoneNumber) + 1];
        strcpy(phoneNumber, _phoneNumber);
    }
    catch (std::bad_alloc& e) {
        // Обработка ошибки выделения памяти
        std::cerr << "Memory allocation error: " << e.what() << std::endl;

        // Освобождение ранее выделенной памяти (если что-то было выделено)
        delete[] firstName;
        delete[] lastName;
        delete[] phoneNumber;

        // Перебрасываем исключение дальше
        throw;
    }

    birthday[0] = day;
    birthday[1] = month;
    birthday[2] = year;
}

NOTE::~NOTE() {
    std::cout << "Destructor called for " << firstName << " " << lastName << std::endl;

    try {
        delete[] firstName;
        delete[] lastName;
        delete[] phoneNumber;
    }
    catch (std::exception& e) {
        // Обработка ошибки при освобождении памяти
        std::cerr << "Error in destructor: " << e.what() << std::endl;
    }
}

const char* NOTE::getFirstName() const {
    return firstName;
}

const char* NOTE::getLastName() const {
    return lastName;
}

const char* NOTE::getPhoneNumber() const {
    return phoneNumber;
}

const int* NOTE::getBirthday() const {
    return birthday;
}

std::ostream& operator<<(std::ostream& os, const NOTE& note) {
    os << "Name: " << note.firstName << " " << note.lastName << std::endl;
    os << "Phone Number: " << note.phoneNumber << std::endl;
    os << "Birthday: " << note.birthday[0] << "." << note.birthday[1] << "." << note.birthday[2] << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, NOTE& note) {
    char tempFirstName[50];
    char tempLastName[50];
    char tempPhoneNumber[20];
    int tempDay, tempMonth, tempYear;

    std::cout << "Enter First Name: ";
    is >> tempFirstName;
    delete[] note.firstName;
    note.firstName = new char[strlen(tempFirstName) + 1];
    strcpy(note.firstName, tempFirstName);

    std::cout << "Enter Last Name: ";
    is >> tempLastName;
    delete[] note.lastName;
    note.lastName = new char[strlen(tempLastName) + 1];
    strcpy(note.lastName, tempLastName);

    std::cout << "Enter Phone Number: ";
    is >> tempPhoneNumber;
    delete[] note.phoneNumber;
    note.phoneNumber = new char[strlen(tempPhoneNumber) + 1];
    strcpy(note.phoneNumber, tempPhoneNumber);

    std::cout << "Enter Birthday (day month year): ";
    is >> tempDay >> tempMonth >> tempYear;
    note.birthday[0] = tempDay;
    note.birthday[1] = tempMonth;
    note.birthday[2] = tempYear;

    return is;
}

void NOTE::editNote() {
    std::cout << "Editing Note:" << std::endl;
    std::cin >> *this;
}

void NOTE::insertSorted(NOTE** phoneBook, int& numNotes, NOTE* newNote) {
    int insertIndex = numNotes;
    for (int i = 0; i < numNotes; ++i) {
        if (strcmp(newNote->getLastName(), phoneBook[i]->getLastName()) < 0 ||
            (strcmp(newNote->getLastName(), phoneBook[i]->getLastName()) == 0 &&
                strcmp(newNote->getFirstName(), phoneBook[i]->getFirstName()) < 0)) {
            insertIndex = i;
            break;
        }
    }

    for (int i = numNotes; i > insertIndex; --i) {
        phoneBook[i] = phoneBook[i - 1];
    }

    phoneBook[insertIndex] = newNote;
    ++numNotes;
}
