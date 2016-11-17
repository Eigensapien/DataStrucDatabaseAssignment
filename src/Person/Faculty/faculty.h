/*
Faculty Class:
	subclass of Person
	string dept
	list of ints of advisees
		need a list class

*/


#ifndef _FACULTY_H_
#define _FACULTY_H_

#include "../person.h"
#include "./List/dlist.h"

class Faculty : public Person
{
    public:
        string dept;
        DList<int> students;
        int numStudents; //NEED TO UPDATE PROPERLY FOR FILE IO TO WORK
        void print()
        {
            std::cout << "Faculty ID: " << ID      << std::endl;
            std::cout << "Name:       " << name    << std::endl;
            std::cout << "Level:      " << level   << std::endl;
            std::cout << "Department: " << dept    << std::endl;
            std::cout << "Advisee IDs:" << std::endl;
            students.printList();
        }
};

#endif