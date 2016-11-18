#include <iostream>
#include "faculty.h"
#include "bstree.h"
#include "student.h"
#include "person.h"
#include "dlist.h"

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
    //create pointer to student node
    TreeNode<Student> *stu;
    
    //pointer to current student id node
    ListNode<int> *curr = students.front;
    
    while (curr != NULL)
    {
        //set student node pointer
        stu = studentBST->search(curr->data);
        
        //print student data
        stu->data.print();
        
        //move to next student in list
        curr = curr->next;
    }
}