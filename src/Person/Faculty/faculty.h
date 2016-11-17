#ifndef _FACULTY_H_
#define _FACULTY_H_

#include "../../BSTree/bstree.h"
#include "../Student/student.h"
#include "../person.h"
#include "./List/dlist.h"

class Faculty : public Person
{
    public:
        string dept;
        DList<int> students;
        int numStudents; //NEED TO UPDATE PROPERLY FOR FILE IO TO WORK
        void print();
        void printAdvisees(BST<Student> *studentBST);
};

#endif