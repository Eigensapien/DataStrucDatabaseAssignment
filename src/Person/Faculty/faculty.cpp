#include <iostream>
#include "faculty.h"
#include "../../BSTree/bstree.h"
#include "../Student/student.h"
#include "../person.h"
#include "./List/dlist.h"

void Faculty::print()
{
    std::cout << "Faculty ID: " << ID      << std::endl;
    std::cout << "Name:       " << name    << std::endl;
    std::cout << "Level:      " << level   << std::endl;
    std::cout << "Department: " << dept    << std::endl;
    std::cout << "Advisee IDs:" << std::endl;
    students.printList();
}

void Faculty::printAdvisees(BST<Student> *studentBST)
{
    TreeNode<Student> *stu;
    int studentID;
    ListNode<int> *curr = students.front;
    while (curr != NULL)
    {
        stu = studentBST->search(studentID);
        stu->print();
        curr = curr->next;
    }
}