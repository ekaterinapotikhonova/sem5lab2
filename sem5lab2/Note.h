#ifndef NOTE_H
#define NOTE_H

#include <iostream>

class NOTE {
private:
    char* firstName;
    char* lastName;
    char* phoneNumber;
    int birthday[3];

public:
    NOTE(const char* _firstName, const char* _lastName, const char* _phoneNumber, int day, int month, int year);
    ~NOTE();

    const char* getFirstName() const;
    const char* getLastName() const;
    const char* getPhoneNumber() const;
    const int* getBirthday() const;

    friend std::ostream& operator<<(std::ostream& os, const NOTE& note);
    friend std::istream& operator>>(std::istream& is, NOTE& note);

    void editNote();
    static void insertSorted(NOTE** noteBook, int& numNotes, NOTE* newNote);
};

#endif // NOTE_H
