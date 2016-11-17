/*

Student Class:
	subclass of Person
	string major
	double GPA
    
    */

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "../person.h"

class Student : public Person
{
    public:
        string major;
        double GPA;
        int advisor;
        void print()
        {
            std::cout << "Student ID: " << ID      << std::endl;
            std::cout << "Name:       " << name    << std::endl;
            std::cout << "Level:      " << level   << std::endl;
            std::cout << "Major:      " << major   << std::endl;
            std::cout << "GPA:        " << GPA     << std::endl;
            std::cout << "Advisor:    " << advisor << std::endl;
        }
};

#endif