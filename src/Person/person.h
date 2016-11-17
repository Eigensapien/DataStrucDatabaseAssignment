#ifndef _PERSON_H_
#define _PERSON_H_

/**************************************************************************************
 * class Person                                                                       *
 *                                                                                    *
 * int ID: the student or faculty ID number of the Person                             *
 * string name: the Person's name                                                     *
 * string level: eg. Freshman etc. for students, Professor etc. for Faculty           *
 *                                                                                    *
 * Comparison operators are overloaded based on ID number                             *
 **************************************************************************************/

class Person
{
    public:
        int ID;
        string name;
        string level;

    //overloaded comparison operators for tree sorting
    friend bool operator< (const Person& l, const Person& r) {
        return l.ID <  r.ID;
    }
    friend bool operator> (const Person& l, const Person& r) {
        return l.ID <  r.ID;
    }
    friend bool operator<=(const Person& l, const Person& r) {
        return l.ID <= r.ID;
    }
    friend bool operator>=(const Person& l, const Person& r) {
        return l.ID >= r.ID;
    }
    friend bool operator==(const Person& l, const Person& r) {
        return l.ID == r.ID;
    }
    //overloaded comparison operators for tree searching
    friend bool operator< (const int l, const Person& r) {
        return l <  r.ID;
    }
    friend bool operator> (const int l, const Person& r) {
        return l <  r.ID;
    }
    friend bool operator<=(const int l, const Person& r) {
        return l <= r.ID;
    }
    friend bool operator>=(const int l, const Person& r) {
        return l >= r.ID;
    }
    friend bool operator==(const int l, const Person& r) {
        return l == r.ID;
    }
    friend bool operator< (const Person& l, const int r) {
        return l.ID <  r;
    }
    friend bool operator> (const Person& l, const int r) {
        return l.ID <  r;
    }
    friend bool operator<=(const Person& l, const int r) {
        return l.ID <= r;
    }
    friend bool operator>=(const Person& l, const int r) {
        return l.ID >= r;
    }
    friend bool operator==(const Person& l, const int r) {
        return l.ID == r;
    }
};

#endif