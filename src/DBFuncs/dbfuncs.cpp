#include <iostream>
#include <string>
#include <stdlib.h> //rand
#include "dbfuncs.h"
#include "../BSTree/bstree.h"
#include "../Person/Faculty/faculty.h"
#include "../Person/Student/student.h"
#include "../FileIO/fileio.h"
#include "../RollbackStack/rollbackstack.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::stoi;
using std::stod;
using std::rand;

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
        int stuImportCode = importStudentTree(studentBST, "../../saved/studentTable");
        int facImportCode = importFacultyTree(facultyBST, "../../saved/facultyTable");
        
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
        case 10: deleteFaculty();
                 break;
        case 11: changeAdvisorPrompt();
                 break;
        case 12: removeAdvisee();
                 break;
        case 13: rollback();
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
	cout << "Search by faculty ID number" << endl;
	cout << "\tEnter faculty ID number: ";
    
    // get input from user
	string userInput;
    cin >> userInput;
	int facultyID = stoi(userInput);
    
    // create pointer to node with faculty
    TreeNode<Faulty> *fac;
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
	cout << "Search student's faculty advisor" << endl;
	cout << "\tEnter student ID number: ";
    
    // get user input
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
        fac->print;
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
    fac->data.students.insert(ID);
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
	cout << "Add student to records" << endl;
	
    //generate random studentID
    int studentID = rand()%1E8; //8 digit random integer
    
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
        int studentID = rand()%1E8; //8 digit random integer
        
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
//                advisorPrompt                                           advisorPrompt
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
    if (studentAdvisor<0 || studentAdvisor>1E8)
    {
        //make them try again recursively
        cout << "Try again. Advisor ID# must be between 0 and 1E8" << endl;
        return advisorPrompt();
    }
    else if ( facultyBST->search(studentAdvisor)==NULL ) // if advisor does not exist
    {
        //make them try again recursively
        cout << "Try again. Advisor must exist." << endl;
        return advisorPrompt();
    }
    else
    {
        //everything is fine, return the input
        return studentAdvisor;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                promptForClass                              		     promptForClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * promptForClass                                                                     *
 * This is a helper function that asks the user for class standing                    *
 **************************************************************************************/

string Database::promptForClass()
{
	cout << "Enter student's class standing: \n\t(1) Freshman \n\t(2) Sophomore \n\t (3) Junior \n\t(4) Senior \n\t(5) Graduate student" << endl;
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
		cout << "Invalid input. Input an integer 1 through 5."
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

void Database::addFaculty( int ID
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
    
    //update rollback stack
    rollbackPushTrees();
    
    //find numStudents and update student advisor fields
    fac.numStudents = 0;
    ListNode<int> *curr = fac.students.front;
    TreeNode<Student> *stu;
    while (curr!=NULL)
    {
        stu = studentBST->search(curr->data);
        stu->advisor = fac.ID;
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
	cout << "Add faculty to records" << endl;
	
    //generate facultyID
    int facultyID = rand()%1E8; //8 digit random integer
    
    //get user input
	cout << "Enter faculty's full name: " << endl;
    string facultyName;
	cin >> facultyName;
	string facultyLevel = professorship();
	cout << "Enter falculty's department: " << endl;
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
            facultyStudents.insert(inputStuID);
            ++i;
        }
        else
        {
            cout << "Try again. Student must exist." << endl;
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
        int facultyID = rand()%1E8; //8 digit random integer
        
        bool success = addFaculty( facultyID
                                 , facultyName
                                 , facultyLevel
                                 , facultyDept
                                 , facultyStudents);
    }
    
	cout << "Faculty has been added with ID#" << facultyID << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                professorship                                 		  professorship
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * professorship                                                                      *
 * This helper function asks for user input for a faculty member's level and          *
 * reprompts if invalid                                                               *
 **************************************************************************************/

string Database::professorship()
{
	cout << "Enter faculty member's level of professorship: \n\t(1) Full Professor \n\t(2) Assistant Professor \n\t (3) Associate Professor \n\t(4) Adjunct Professor \n\t(5) Lecturer" << endl;
	cin >> profLevel;
	profLevel = stoi(classLevel);
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
		cout << "Invalid input. Input an integer 1 through 5."
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
    }
    else
    {
        //update rollback stack
        rollbackPushTrees();
        
        //update fields accordingly
        stu->data.advisor = newFacID;
        oldFac->data.students.remove(stu->data.ID);
        oldFac->data.numStudents--;
        newFac->data.students.insert(stu->data.ID);
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
        //student doesn't exist, recursive do-over
        cout << "Student does not exist. Please try again." << endl;
        changeAdvisorPrompt();
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
	cout << "Remove Advisee from faculty record" << endl;
	cout << "\tEnter faculty ID: " << endl;
    
    //get user input for faculty ID
    string userInput;
	cin >> userInput;
	facultyID = stoi(userInput);
    
    //get pointer to faculty node
    TreeNode<Faculty> *fac;
    fac = facultyBST->search(facultyID);
    
    //if faculty exists
	if (fac!=NULL)
	{
        //get user input for student ID
		cout << "\tEnter student ID: " << endl;
		cin >> userInput;
		studentID = stoi(userInput);
        
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
 * This function pushes both trees to the rollback stack                              *
 **************************************************************************************/

void Database::rollbackPushTrees()
{
    studentRollback.push(studentBST);
    facultyRollback.psuh(facultyBST);
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
        *facultyBST = facultyRollback.pop();
        *studentBST = studentRollback.pop();
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
    bool notSureYet = false;
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
            saveFacultyTreeToFile(&facultyBST, "../saved/facultyTable");
            saveStudentTreeToFile(&studentBST, "../saved/studentTable");
        }
    }
	cout << "Goodbye" << endl;
    stop = true;
}