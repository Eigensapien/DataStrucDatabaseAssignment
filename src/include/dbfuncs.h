#ifndef _DBFUNCS_H_
#define _DBFUNCS_H_

#include <string>
#include "bstree.h"
#include "faculty.h"
#include "student.h"
#include "rollbackstack.h"

using std::string;

class Database
{
	public:
		Database();
		~Database();
        
		BST<Student> *studentBST;
		BST<Faculty> *facultyBST;
        
        void showMenu();
        bool stop; //tells main loop when to stop
        
		void printAllStudents(); //1
		void printAllFaculty(); //2
        
		void findStudent(); //3
		void findFaculty(); //4
		void myAdvisorIs(); //5
		void myAdviseesAre(); //6
        
        bool addStudent( int ID
                       , string name
                       , string level
                       , string major
                       , double GPA
                       , int advisor);
        void addStudentPrompt(); //7
		void deleteStudent(); //8
        
		bool addFaculty( int ID
                       , string name
                       , string level
                       , string dept
                       , DList<int> students);
        void addFacultyPrompt(); //9
		void deleteFaculty(); //10
        
		void changeAdvisor(int stuID);
        void changeAdvisorPrompt(); //11
		void removeAdvisee(); //12
        
		void rollback(); //13
		void exit(); //14
    
    private:
        //input helper functions
        int advisorPrompt();
        string promptForClass();
        string professorship();
        
        //rollback
        void rollbackPushTrees();
        RollbackStack<BST<Student> > studentRollback;
        RollbackStack<BST<Faculty> > facultyRollback;
};

#endif