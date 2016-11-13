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
};

#endif