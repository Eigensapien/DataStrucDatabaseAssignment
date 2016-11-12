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
};

#endif