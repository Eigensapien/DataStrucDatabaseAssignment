#include <iostream>
#include <string>
#include <stdlib.h> //rand
#include "dbfuncs.h"
#include "bstree.h"
#include "faculty.h"
#include "student.h"
#include "fileio.h"
#include "rollbackstack.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::stoi;
using std::stod;
using std::rand;


string stuFilePath = "../saved/studentTable";
string facFilePath = "../saved/facultyTable";

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                Constructor                              		            Constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * Constructor                                                                        *
 * Initializes the trees and imports files if they exist.                             *
 * If no file or import fails, results in blank tree                                  *
 **************************************************************************************/
Database::Database()
{
    stop = false;
    
    // make new databases
    studentBST = new BST<Student>;
    facultyBST = new BST<Faculty>;
    
    // import files if they exist
    if ( filesExist() )
    {
        // import databases
        int stuImportCode = importStudentTree(studentBST, stuFilePath);
        int facImportCode = importFacultyTree(facultyBST, facFilePath);
        
        // if import fails, delete BST in case it has been partially modified and make a blank one
        if (stuImportCode==1)
        {
            delete studentBST;
            studentBST = new BST<Student>;
        }
        if (facImportCode==1)
        {
            delete facultyBST;
            facultyBST = new BST<Faculty>;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                Destructor                                                 Destructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * Destructor                                                                         *
 * The destructor only needs to free up the memory allocated to the trees             *
 **************************************************************************************/

Database::~Database()
{
    // needs to delete the BSTs, should ask to save tree in exit()
    delete studentBST;
    delete facultyBST;
    stop = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                showMenu                                                     showMenu
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * showMenu                                                                           *
 * This function displays the possible operations to the user and calls the           *
 * appropriate functions based on user input.                                         *
 **************************************************************************************/

void Database::showMenu()
{
    string userInput;
    int intInput;
    
    // Display menu
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "What would you like to do? (choose one):"  << endl;
    cout << "1. Display all student information"        << endl;
    cout << "2. Display all faculty information"        << endl;
    cout << "3. Display student information"            << endl;
    cout << "4. Display faculty information"            << endl;
    cout << "5. Display student's advisor"              << endl;
    cout << "6. Display faculty's students"             << endl;
    cout << "7. Add a new student"                      << endl;
    cout << "8. Delete a student"                       << endl;
    cout << "9. Add a new faculty member"               << endl;
    cout << "10. Delete a faculty member"               << endl;
    cout << "11. Change a student’s advisor"            << endl;
    cout << "12. Remove an advisee from faculty member" << endl;
    cout << "13. Rollback recent edit"                  << endl;
    cout << "14. Exit"                                  << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
    // Get user input
    cin >> userInput;
    intInput = stoi(userInput);
    switch(intInput)
    {
        case 1 : printAllStudents();
                 break;
        case 2 : printAllFaculty();
                 break;
        case 3 : findStudent();
                 break;
        case 4 : findFaculty();
                 break;
        case 5 : myAdvisorIs();
                 break;
        case 6 : myAdviseesAre();
                 break;
        case 7 : addStudentPrompt();
                 break;
        case 8 : deleteStudent();
                 break;
        case 9 : addFacultyPrompt();
                 break;
        case 10: deleteFaculty(); //loop
                 break;
        case 11: changeAdvisorPrompt(); //loop
                 break;
        case 12: removeAdvisee(); //loop
                 break;
        case 13: rollback();
                 cout << "The database has been rolled back" << endl;
                 break;
        case 14: exit();
                 break;
        default: cout << "Improper input. Please try again." << endl;
                 break;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printAllStudents                                     printAllStudents
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * printAllStudents                                                                   *
 * This function displays the information for each student by ascending ID            *
 **************************************************************************************/
void Database::printAllStudents()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Students by ascending ID: " << endl;
	studentBST->printTree();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printAllFaculty                                       printAllFaculty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * printAllFaculty                                                                    *
 * This function displays the information for each faculty member by ascending ID     *
 **************************************************************************************/

void Database::printAllFaculty()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Faculty by ascending ID: " << endl;
	facultyBST->printTree();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findStudent                              		            findStudent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * findStudent                                                                        *
 * This function displays the information for a single student by their ID#           *
 **************************************************************************************/

void Database::findStudent() //3
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Search by student ID number" << endl;
	cout << "\tEnter student ID number: ";
    
    // get input from user
    string userInput;
	cin >> userInput;
	int studentID = stoi(userInput);
    
    // create pointer to node with student
    TreeNode<Student> *stu;
    stu = studentBST->search(studentID);
    
	if ( stu != NULL) { // student found
		stu->data.print(); // prints all data on student
    }
	else { // student not found
		cout << "Student \"" << studentID << "\"  does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findFaculty                             	 		 findFaculty 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * findFaculty                                                                        *
 * This function displays the information for a single student by their ID#           *
 **************************************************************************************/

void Database::findFaculty() //4
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Search by faculty ID number" << endl;
	cout << "\tEnter faculty ID number: ";
    
    // get input from user
	string userInput;
    cin >> userInput;
	int facultyID = stoi(userInput);
    
    // create pointer to node with faculty
    TreeNode<Faculty> *fac;
    fac = facultyBST->search(facultyID);
    
	if ( fac != NULL ) { // faculty found
		fac->data.print(); // all data on the faculty
    }
	else { // not found
		cout << "Faculty member \"" << facultyID << "\"  does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                myAdvisorIs                              		            myAdvisorIs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * myAdvisorIs                                                                        *
 * This function asks the user for a student ID and then displays information on that *
 * student's advisor                                                                  *
 **************************************************************************************/

void Database::myAdvisorIs() //5 
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Search student's faculty advisor" << endl;
	cout << "\tEnter student ID number: ";
    
    // get user input
    string userInput;
    cin >> userInput;
	int studentID = stoi(userInput);
    
    // create pointer to node with student
    TreeNode<Student> *stu;
    stu = studentBST->search(studentID);
    
	if ( stu != NULL ) // found student
	{
        // find the faculty member and print information
		TreeNode<Faculty> *fac;
        fac = facultyBST->search(stu->data.advisor);
        fac->data.print();
	}
	else
    {
		cout << "Student \"" << studentID << "\" does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                myAdviseesAre                                           myAdviseesAre
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * myAdviseesAre                                                                      *
 * This function asks the user for a faculty ID and then displays information on that *
 * faculty member's advisees                                                          *
 **************************************************************************************/

void Database::myAdviseesAre() //6
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Search for advisees" << endl;
	cout << "\tEnter faculty ID number: ";
    
    //get user input
    string userInput;
	cin >> userInput;
	int facultyID = stoi(userInput);
    
    //create pointer to node with faculty
    TreeNode<Faculty> *fac;
    fac = facultyBST->search(facultyID);
    
	if ( fac != NULL ) // found faculty
	{
        //print all advisees
		fac->data.printAdvisees(studentBST);
	}
	else //not found
    {
		cout << "Faculty member does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addStudent                                                 addStudent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * addStudent                                                                         *
 * Takes individual pieces of data about a student as input and adds that student to  *
 * the tree. The rollback stack is updated.                                           *
 * Returns false if unsuccessful                                                      *
 **************************************************************************************/

bool Database::addStudent( int ID
                         , string name
                         , string level
                         , string major
                         , double GPA
                         , int advisor)
{
    if ( studentBST->search(ID) != NULL ) //ID already taken
    {
        return false; // did not succeed
    }
    
    //create student
    Student stu;
    
    //set the student's data fields
    stu.ID      = ID;
    stu.name    = name;
    stu.level   = level;
    stu.major   = major;
    stu.GPA     = GPA;
    stu.advisor = advisor;
    
    //find advisor's node
    TreeNode<Faculty> *fac;
    fac = facultyBST->search(advisor);
    
    //update advisor's list of students
    fac->data.students.insertFront(ID);
    fac->data.numStudents++;
    
    
    //push current tree to the stack
    rollbackPushTrees();
    
    //add the student to the tree
    studentBST->insert(stu);
    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addStudentPrompt                                     addStudentPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * addStudentPrompt                                                                   *
 * This function asks the user for data about a student and adds that student to the  *
 * tree. The rollback stack is updated.                                               *
 **************************************************************************************/

void Database::addStudentPrompt() //7
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Add student to records" << endl;
	
    //generate random studentID
    int studentID = rand()%100000000; //8 digit random integer
    
    //get data from user
	cout << "Enter student's full name: " << endl;
    string studentName;
	cin >> studentName;
	string classStanding = promptForClass();
	cout << "Enter student's major: " << endl;
    string studentMajor;
	cin >> studentMajor;
	cout << "Enter student GPA: " << endl;
    string userInput;
	cin >> userInput;
	double studentGPA = stod(userInput);
    int studentAdvisor = advisorPrompt();
    
    if (studentAdvisor==-1)
    {
        cout << "New student aborted." << endl;
        return;
    }
    
    //try to add the student, fails if ID already taken
    bool success = addStudent( studentID
                             , studentName
                             , classStanding
                             , studentMajor
                             , studentGPA
                             , studentAdvisor);
    while ( !success ) // until an unused ID is found
    {
        // generate new ID and try again
        int studentID = rand()%100000000; //8 digit random integer
        
        bool success = addStudent( studentID
                                 , studentName
                                 , classStanding
                                 , studentMajor
                                 , studentGPA
                                 , studentAdvisor);
    }
    
	cout << "Student has been added with ID#" << studentID << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                advisorPrompt                   (helper)                advisorPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * advisorPrompt()                                                                    *
 * This is a helper function for addStudentPrompt that asks for an advisor, checks    *
 * that the advisor exists, and returns the ID.                                       *
 **************************************************************************************/
int Database::advisorPrompt()
{
    //get user input
    string userInput;
    cout << "Input student advisor ID#: " << endl;
    cin >> userInput;
    int studentAdvisor = stoi(userInput);
    
    //if input is invalid
    if ( facultyBST->search(studentAdvisor)==NULL ) // if advisor does not exist
    {
        //check if they want to try again to let them break out of loops
        cout << "Advisor must exist. Try again? (y)" << endl;
        cin >> userInput;
        if (userInput=="y")
        {
            return advisorPrompt();
        }
        else
        {
            return -1;
        }
    }
    else
    {
        //everything is fine, return the input
        return studentAdvisor;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                promptForClass              (helper)         		     promptForClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * promptForClass                                                                     *
 * This is a helper function that asks the user for class standing                    *
 **************************************************************************************/

string Database::promptForClass()
{
	cout << "Enter student's class standing: \n\t(1) Freshman \n\t(2) Sophomore \n\t(3) Junior \n\t(4) Senior \n\t(5) Graduate student" << endl;
    string userInput;
	cin >> userInput;
	int classLevel = stoi(userInput);
	if (classLevel ==1)
		return "Freshman";
	else if (classLevel ==2)
		return "Sophomore";
	else if (classLevel ==3)
		return "Junior";
	else if (classLevel ==4)
		return "Senior";
	else if (classLevel ==5)
		return "Graduate student";
	else
	{
		cout << "Invalid input. Input an integer 1 through 5." << endl;
		return promptForClass();
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                deleteStudent                              	    	  deleteStudent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * deleteStudent                                                                      *
 * This function prompts the user for a student ID, updates the rollback stack and    *
 * advisor, then deletes the student                                                  *
 **************************************************************************************/

void Database::deleteStudent()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Delete student from records" << endl;
	cout << "\tEnter student ID: " << endl;
    
    //get user input
    string userInput;
	cin >> userInput;
	int studentID = stoi(userInput);
    
    //create a pointer to node with student
    TreeNode<Student> *stu;
    stu = studentBST->search(studentID);
    
    //delete the student if it exists
	if ( stu != NULL )
	{
        //update rollback
        rollbackPushTrees();
        
        //delete from advisor list
        TreeNode<Faculty> *fac;
        fac = facultyBST->search(stu->data.advisor);
        fac->data.students.remove(studentID);
        fac->data.numStudents--;
        
        //delete student
		studentBST->deleteN(studentID);
        
		cout << "Student \"" << studentID << "\" has been deleted." << endl;
	}
	else
    {
		cout << "Student \"" << studentID << "\" does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addFaculty                                                 addFaculty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * addFaculty                                                                         *
 * Takes individual pieces of data about a faculty member as input and adds that      *
 * faculty member to the tree. The rollback stack is updated.                         *
 * Returns false if unsuccessful                                                      *
 **************************************************************************************/

bool Database::addFaculty( int ID
                         , string name
                         , string level
                         , string dept
                         , DList<int> students)
{
    if ( facultyBST->search(ID) != NULL ) //ID already taken
    {
        return false; // did not succeed
    }
    
    //create faculty member
    Faculty fac;
    
    //set data fields
    fac.ID          = ID;
    fac.name        = name;
    fac.level       = level;
    fac.dept        = dept;
    fac.students    = students;
    
    //find numStudents and update student advisor fields
    fac.numStudents = 0;
    ListNode<int> *curr = fac.students.front;
    TreeNode<Student> *stu;
    while (curr!=NULL)
    {
        stu = studentBST->search(curr->data);
        stu->data.advisor = fac.ID;
        fac.numStudents++;
        curr = curr->next;
    }
    
    //place faculty in tree
    facultyBST->insert(fac);
    
    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addFacultyPrompt                                     addFacultyPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * addFacultyPrompt                                                                   *
 * This function asks the user for data about a faculty member and adds that faculty  *
 * member to the tree. The rollback stack is updated.                                 *
 **************************************************************************************/

void Database::addFacultyPrompt() //9
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
    //update rollback stack
    rollbackPushTrees();
    
	cout << "Add faculty to records" << endl;
	
    //generate facultyID
    int facultyID = rand()%100000000; //8 digit random integer
    
    //get user input
	cout << "Enter faculty's full name: " << endl;
    string facultyName;
	cin >> facultyName;
	string facultyLevel = professorship();
	cout << "Enter faculty's department: " << endl;
    string facultyDept;
    cin >> facultyDept;
    //need to know how many students to advise
    cout << "How many students does this faculty member advise?: " << endl;
    string userInput;
    cin >> userInput;
    int N = stoi(userInput);
    //create list for student ID
    DList<int> facultyStudents;
    int inputStuID;
    //loop to get all students
    int i=0;
    while (i<N)
    {
        //get user input for student ID
        cout << "Enter advisee's ID#: " << endl;
        cin >> userInput;
        inputStuID = stoi(userInput);
        
        //if valid, add student to list
        if (studentBST->search(inputStuID) != NULL)
        {
            facultyStudents.insertFront(inputStuID);
            ++i;
        }
        else
        {
            //check if they want to try again to let them break out of loops
            cout << "Student must exist. Try again? (y): " << endl;
            cin >> userInput;
            if (userInput!="y")
            {
                cout << "New faculty member aborted." << endl;
                rollback();
                return;
            }
            //note that i does not incriment
        }
    }
    
    //add to the tree. updates student advisor fields as needed
    bool success = addFaculty( facultyID
                             , facultyName
                             , facultyLevel
                             , facultyDept
                             , facultyStudents);
    
    while ( !success ) //until an unused ID is found
    {
        int facultyID = rand()%100000000; //8 digit random integer
        
        bool success = addFaculty( facultyID
                                 , facultyName
                                 , facultyLevel
                                 , facultyDept
                                 , facultyStudents);
    }
    
	cout << "Faculty has been added with ID#" << facultyID << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                professorship                (helper)           		  professorship
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * professorship                                                                      *
 * This helper function asks for user input for a faculty member's level and          *
 * reprompts if invalid                                                               *
 **************************************************************************************/

string Database::professorship()
{
    string userInput;
	cout << "Enter faculty member's level of professorship: \n\t(1) Full Professor \n\t(2) Assistant Professor \n\t(3) Associate Professor \n\t(4) Adjunct Professor \n\t(5) Lecturer" << endl;
	cin >> userInput;
	int profLevel = stoi(userInput);
	if (profLevel ==1)
		return "Full Professor";
	else if (profLevel ==2)
		return "Assistant Professor";
	else if (profLevel ==3)
		return "Associate Professor";
	else if (profLevel ==4)
		return "Adjunct Professor";
	else if (profLevel ==5)
		return "Lecturer";
	else
	{
		cout << "Invalid input. Input an integer 1 through 5." << endl;
		return professorship();
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                deleteFaculty                              		      deleteFaculty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * deleteFaculty                                                                      *
 * This function prompts the user for a faculty ID, updates the rollback stack and    *
 * advisor, then deletes the faculty member                                           *
 **************************************************************************************/

void Database::deleteFaculty() //10
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Delete faculty from records" << endl;
	cout << "\tEnter faculty ID: " << endl;
    
    //get user input
    string userInput;
	cin >> userInput;
	int facultyID = stoi(userInput);
    
    //create pointer to the node with faculty
    TreeNode<Faculty> *fac;
    fac = facultyBST->search(facultyID);
    
    //delete faculty if it exists
	if ( fac != NULL )
	{
        //update rollback stack
        rollbackPushTrees();
        
        //move all students
        ListNode<int> *curr;
        curr = fac->data.students.front;
        while (curr != NULL)
        {
            changeAdvisor(curr->data);
        }
        
        //delete the faculty member
		facultyBST->deleteN(facultyID);
        
		cout << "Faculty \"" << facultyID << "\" has been deleted." << endl;
	}
	else
    {
		cout << "Faculty \"" << facultyID << "\" does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                changeAdvisor                                           changeAdvisor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * changeAdvisor                                                                      *
 * this function takes a student ID as input and updates the advisor field based on   *
 * user input.                                                                        *
 **************************************************************************************/

void Database::changeAdvisor(int stuID) //11
{
    
    //get a pointer to the student node
	TreeNode<Student> *stu;
    stu = studentBST->search(stuID);
    
    //get a pointer to the former advisor node
    TreeNode<Faculty> *oldFac;
    oldFac = facultyBST->search(stu->data.advisor);
    
    //get user input
    cout << "Enter new advisor's ID for student #" << stuID << endl;
    string userInput;
    cin >> userInput;
    int newFacID = stoi(userInput);
    
    //get a pointer to the new advisor node
    TreeNode<Faculty> *newFac;
    newFac = facultyBST->search(newFacID);
    
    //if advisor doesn't exist, recursively make user try again
    if (newFac==NULL)
    {
        cout << "Try again. Advisor must exist." << endl;
        changeAdvisor(stuID);
        
        //check if they want to try again to let them break out of loops
        cout << "Advisor must exist. Try again? (y)" << endl;
        cin >> userInput;
        if (userInput=="y")
        {
            changeAdvisor(stuID);
        }
        else
        {
            cout << "Changing student's advisor aborted" << endl;
            return;
        }
        
    }
    else
    {
        //update rollback stack
        rollbackPushTrees();
        
        //update fields accordingly
        stu->data.advisor = newFacID;
        oldFac->data.students.remove(stu->data.ID);
        oldFac->data.numStudents--;
        newFac->data.students.insertFront(stu->data.ID);
        newFac->data.numStudents++;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                changeAdvisorPrompt                               changeAdvisorPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * changeAdvisor                                                                      *
 * this function takes is essentially changeAdvisor with an additional prompt for the *
 * student ID                                                                         *
 **************************************************************************************/
void Database::changeAdvisorPrompt()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
    //get user inputs
    string userInput;
    int stuID;
    cout << "Change advisor in student record" << endl;
    cout << "\tEnter student ID:" << endl;
    cin >> userInput;
    stuID = stoi(userInput);
    
    //if student exists, call changeAdvisor(stuID)
    if (studentBST->search(stuID) != NULL)
    {
        changeAdvisor(stuID);
    }
    else
    {
        //check if they want to try again to let them break out of loops
        cout << "Student must exist. Try again? (y)" << endl;
        cin >> userInput;
        if (userInput=="y")
        {
            return changeAdvisorPrompt();
        }
        else
        {
            cout << "Changing student's advisor aborted" << endl;
            return;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                removeAdvisee                              		      removeAdvisee
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * removeAdvisee                                                                      *
 * This function prompts the user for a faculty ID and the ID of an advisee of the    *
 * faculty member. The function removes the student from the list of advisees and     *
 * prompts the user for the student's new advisor.                                    *
 **************************************************************************************/

void Database::removeAdvisee() //12
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
	cout << "Remove Advisee from faculty record" << endl;
	cout << "\tEnter faculty ID: " << endl;
    
    //get user input for faculty ID
    string userInput;
	cin >> userInput;
	int facultyID = stoi(userInput);
    
    //get pointer to faculty node
    TreeNode<Faculty> *fac;
    fac = facultyBST->search(facultyID);
    
    //if faculty exists
	if (fac!=NULL)
	{
        //get user input for student ID
		cout << "\tEnter student ID: " << endl;
		cin >> userInput;
		int studentID = stoi(userInput);
        
        //get a pointer to the student node
        TreeNode<Student> *stu;
        stu = studentBST->search(studentID);
        
		if (stu!=NULL) //student exists
		{
            //make sure student is currently an advisee of the faculty member
            if (fac->data.students.find(studentID)==-1) //not a student of fac
            {
                cout << "Student is not advised by this faculty member." << endl;
            }
            else
            {
                //use changeAdvisor to give them a new advisor
                //this function updates the stack
                changeAdvisor(stu->data.ID);
            }
		}
		else
        {
			cout << "Student not found." << endl;
        }
	}
	else
    {
        cout << "Faculty member not found." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                rollbackPushTrees                                   rollbackPushTrees
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * rollbackPushTrees                                                                  *
 * This function pushes pointers to both trees to the rollback stack                  *
 **************************************************************************************/

void Database::rollbackPushTrees()
{
    if ( !studentBST->isEmpty() )
    {
        studentRollback.push(NULL);
    }
    else
    {
        BST<Student> *backupStudent = new BST<Student>;
        *backupStudent = *studentBST;
        studentRollback.push(backupStudent);
    }
    if ( !facultyBST->isEmpty() )
    {
        facultyRollback.push(NULL);
    }
    else
    {
        BST<Faculty> *backupFaculty = new BST<Faculty>;
        *backupFaculty = *facultyBST;
        facultyRollback.push(backupFaculty);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                rollback                              		               rollback
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * rollback                                                                           *
 * This function reverts the database to it's previous state. Up to five edits are    *
 * stored for this purpose.                                                           *
 **************************************************************************************/

void Database::rollback() //13
{
	if ( studentRollback.isEmpty() )
    {
        cout << "Cannot undo. No stored changes available." << endl;
    }
    else
    {
        //rollback faculty
        BST<Faculty> *backupFaculty;
        backupFaculty =  facultyRollback.pop();
        if (backupFaculty==NULL)
        {
            delete facultyBST;
            facultyBST = new BST<Faculty>;
        }
        else
        {
            delete facultyBST;
            facultyBST = backupFaculty;
        }
        
        //rollback students
        BST<Student> *backupStudent;
        backupStudent =  studentRollback.pop();
        if (backupStudent==NULL)
        {
            delete studentBST;
            studentBST = new BST<Student>;
        }
        else
        {
            delete studentBST;
            studentBST = backupStudent;
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                	exit                              		 		               exit
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * exit                                                                               *
 * This function asks the user if they would like to save the changes made. If they   *
 * do, the data is saved to file. If they do not, the program makes sure this is      *
 * their intention. The function ends by setting the stop variable to true so that    *
 * the main loop knows to stop.                                                       *
 **************************************************************************************/

void Database::exit() //14
{
    bool notSureYet = true;
    string userInput;
    while (notSureYet)
    {
        cout << "Would you like to save to file? (y/n): " << endl;
        cin >> userInput;
        if (userInput=="n")
        {
            string confirm;
            cout << "Enter \"YES\" to confirm exit without saving changes: " << endl;
            cin >> confirm;
            if (confirm=="YES")
            {
                notSureYet = false;
            }
        }
        else if (userInput=="y")
        {
            cout << "Saving data to file." << endl;
            saveFacultyTreeToFile(facultyBST, facFilePath);
            saveStudentTreeToFile(studentBST, stuFilePath);
            notSureYet = false;
        }
    }
	cout << "Goodbye" << endl;
    stop = true;
}