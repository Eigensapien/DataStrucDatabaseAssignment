#include <iostream>
#include <string>
#include <stdlib.h> //rand
#include "../BSTree/bstree.h"
#include "../Person/Faculty/faculty.h"
#include "../Person/Student/student.h"
#include "../FileIO/fileio.h"
#include "../RollbackStack/rollbackstack.h"

using namespace std;

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
		
		string promptForClass(); //prompts for class standing used in addStudent()
		void addStudent(); //7
		void deleteStudent(); //8
		
		string professorship(); //prompts for professorship used in addFaculty()
		void addFaculty(); //9
		void deleteFaculty(); //10
		
		void changeAdvisor(); //11
		void removeAdvisee(); //12
		
		void rollback(); //13
		void exit(); //14
    
    private:
        RollbackStack<BST<Student>> studentRollback;
        RollbackStack<BST<Faculty>> facultyRollback;
        RollbackStack<bool> isFacRollback; // when popping, true means faculty was most recently edited, false means student
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                Constructor                              		            Constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Database::Database()
{
    // needs to check for existing files
    //     import if found
    //     new if not
    // set stop to false
    
    stop = false;
    
    if ( filesExist() ) // calls function from fileio
    {
        // import databases
        studentBST = importStudentTree(".../saved/studentTable"); // need to make this function in fileio, should return BST<Student>*
    }
    else
    {
        studentBST = new BST<Student>;
        // make new databases
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                Destructor                                                 Destructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Database::~Database()
{
    // needs to delete the BSTs, should ask to save tree in exit()
    delete studentBST;
    delete facultyBST;
    stop = true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printAllStudents                                     printAllStudents
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::printAllStudents() {
	cout << "Students by ascending ID: " << endl;
	studentBST.printTree();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printAllFaculty                                       printAllFaculty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::printAllFaculty() {
	//Option 1, in order traversal, prints beginning with minimum faculty ID
	cout << "Faculty by ascending ID: " << endl;
	facultyBST.printTree();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findStudent                              		 findStudent 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::findStudent() //3
{
	cout << "Search by student ID number" << endl;
	cout << "\tEnter student ID number: ";
    string userInput;
	cin >> userInput;
	int studentID = stoi(userInput);
    TreeNode<Student> *stu;
    stu = studentBST.search(studentID);
	if ( stu != NULL) // search returns pointer to node
		stu->data.print(); // prints all data on student
	else
		cout << "Student \"" << studentID << "\"  does not exist." << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findFaculty                             	 		 findFaculty 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::findFaculty() //4
{
	cout << "Search by faculty ID number" << endl;
	cout << "\tEnter faculty ID number: ";
	string userInput;
    cin >> userInput;
	int facultyID = stoi(userInput);
    TreeNode<Faulty> *fac;
    fac = facultyBST.search(facultyID);
	if ( fac != NULL ) // search returns pointer to node
		fac->data.print(); // all data on the faculty
	else
		cout << "Faculty member \"" << facultyID << "\"  does not exist." << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                myAdvisorIs                              		            myAdvisorIs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::myAdvisorIs() //5 
{
	cout << "Search student's faculty advisor" << endl;
	cout << "\tEnter student ID number: ";
	cin >> userInput;
	int studentID = stoi(userInput);
    TreeNode<Student> *stu;
    stu = studentBST.search(studentID);
	if ( stu != NULL )
	{
		TreeNode<Faculty> *fac = facultyBST.search(stu->data.advisor);
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

void Database::myAdviseesAre() //6
{
	cout << "Search for advisees" << endl;
	cout << "\tEnter faculty ID number: ";
    string userInput;
	cin >> userInput;
	int facultyID = stoi(userInput);
    TreeNode<Faculty> *fac;
    fac = facultyBST.search(facultyID);
	if ( fac != NULL )
	{
		fac->data.printAdvisees()
	}
	else
    {
		cout << "Faculty member does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addStudent                                                 addStudent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Database::addStudent( int ID
                         , string name
                         , string level
                         , string major
                         , double GPA
                         , int advisor)
{
    if ( studentBST.search(ID) != NULL ) //ID already taken
    {
        return false; // did not succeed
    }
    
    Student stu;
    
    stu.ID      = ID;
    stu.name    = name;
    stu.level   = level;
    stu.major   = major;
    stu.GPA     = GPA;
    stu.advisor = advisor;
    
    TreeNode<Faculty> *fac;
    fac = facultyBST.search(advisor);
    fac->data.students.insert(ID);
    
    studentRollback.push(studentBST);
    isFacRollback.push(false);
    
    studentBST.insert(stu);
    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addStudentPrompt                                     addStudentPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Database::addStudentPrompt() //7
{
	//this block of code 
	//1) prompts for student elements to fill in student node
	//2) inserts student node into the tree
	//3) adds student to advisor list
	//4) saves for rollback
	
	cout << "Add student to records" << endl;
	
    //generate studentID
    int studentID = rand()%1E8; //8 digit random integer

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
    
    bool success = addStudent( studentID
                             , studentName
                             , classStanding
                             , studentMajor
                             , studentGPA
                             , studentAdvisor);
    while ( !success ) //until an unused ID is found
    {
        int studentID = rand()%1E8; //8 digit random integer
        
        bool success = addStudent( studentID
                                 , studentName
                                 , classStanding
                                 , studentMajor
                                 , studentGPA
                                 , studentAdvisor);
    }
    
	cout << "Student has been added." << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                advisorPrompt                                           advisorPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int advisorPrompt()
{
    string userInput;
    cout << "Input student advisor ID#: " << endl;
    cin >> userInput;
    int studentAdvisor = stoi(userInput);
    if (studentAdvisor<0 || studentAdvisor>1E8)
    {
        cout << "Try again. Advisor ID# must be between 0 and 1E8" << endl;
        return advisorPrompt();
    }
    else if ( facultyTree.search(studentAdvisor)==NULL ) // if advisor does not exist
    {
        cout << "Try again. Advisor must exist." << endl;
        return advisorPrompt();
    }
    else
    {
        return studentAdvisor;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                promptForClass                              		     promptForClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

string Database::promptForClass()
{
	//this block of code prompts for student's class standing level and reprompts if invalid input
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
//                deleteStudent                              		 deleteStudent 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::deleteStudent()
{
	//option 8
	//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK
	cout << "Delete student from records" << endl;
	cout << "\tEnter student ID: " << endl;
    string userInput;
	cin >> userInput;
	int studentID = stoi(userInput);
    
    TreeNode<Student> *stu;
    stu = studentBST.search(studentID)

	if ( stu != NULL )
	{
        studentRollback.push(studentBST);
        isFacRollback.push(false);
        
        //delete from advisor list
        TreeNode<Faculty> *fac = facultyBST.search(stu->data.advisor);
        fac->students.remove(studentID);
        
		studentBST.deleteN(studentID);
        
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
void Database::addFaculty( int ID
                         , string name
                         , string level
                         , string dept
                         , DList<int> students)
{
    if ( facultyBST.search(ID) != NULL ) //ID already taken
    {
        return false; // did not succeed
    }
    
    Faculty fac;
    
    fac.ID      = ID;
    fac.name    = name;
    fac.level   = level;
    fac.dept    = dept;
    fac.students= students;
    
    facultyRollback.push(facultyBST);
    isFacRollback.push(true);
    
    facultyBST.insert(fac);
    
    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addFacultyPrompt                                     addFacultyPrompt
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Database::addFaculty(); //9
{
	//this block of code 
	//1) prompts for student elements to fill in student node
	//2) inserts student node into the tree
	//3) adds student to advisor list
	//4) saves for rollback
	
	cout << "Add faculty to records" << endl;
	
    //generate facultyID
    int facultyID = rand()%1E8; //8 digit random integer

	cout << "Enter faculty's full name: " << endl;
    string facultyName;
	cin >> facultyName;
	string facultyLevel = professorship();
	cout << "Enter falculty's department: " << endl;
    string facultyDept;
    cin >> facultyDept;
    cout << "How many students does this faculty member advise?: " << endl;
    string userInput;
    cin >> userInput;
    int N = stoi(userInput);
    DList<int> facultyStudents;
    int inputStuID;
    for (int i=0; i<N; ++i)
    {
        cout << "Enter advisee's ID#: " << endl;
        cin >> userInput;
        inputStuID = stoi(userInput);
        facultyStudents.insert(inputStuID);
    }
    
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
    
	cout << "Faculty has been added." << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                professorship                              		 professorship 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

string Database::professorship()
{
	//this block of code prompts for professorship level and reprompts if invalid input
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

void Database::deleteFaculty(); //10
{
	cout << "Delete faculty from records" << endl;
	cout << "\tEnter faculty ID: " << endl;
    string userInput;
	cin >> userInput;
	int facultyID = stoi(userInput);
    
    TreeNode<Faculty> *fac;
    fac = facultyBST.search(facultyID)

	if ( fac != NULL )
	{
        facultyRollback.push(facultyBST);
        isFacRollback.push(true);
        
        //move all students
        ListNode<int> *curr;
        curr = fac->data.students.front;
        while (curr != NULL)
        {
            changeAdvisor(curr->data); // need to create this function in D.cpp. should take int studentID argument, prompt for new advisorID and update student
        }
        
		facultyBST.deleteN(facultyID);
        
		cout << "Faculty \"" << facultyID << "\" has been deleted." << endl;
	}
	else
    {
		cout << "Faculty \"" << facultyID << "\" does not exist." << endl;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                changeAdvisor                              		 changeAdvisor 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::changeAdvisor(int stuID); //11
{
	/*
	needs to remove from advisor's list & change new advisor
	*/
	TreeNode<Student> *stu;
    stu = studentBST.search(stuID);
    
    TreeNode<Faculty> *oldFac;
    oldFac = facultyBST.search(stu->data.advisor);
    
    cout << "Enter new advisor's ID for student #" << stuID << endl;
    string userInput;
    cin >> userInput;
    int newFacID = stoi(userInput);
    
    TreeNode<Faculty> *newFac;
    newFac = facultyBST.search(newFacID);
    
    if (newFac==NULL)
    {
        cout << "Try again. Advisor must exist." << endl;
        changeAdvisor(stuID);
    }
    else
    {
        stu->data.advisor = newFacID;
        oldFac->data.students.remove(stu->data.ID);
        newFac->data.students.insert(stu->data.ID);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                removeAdvisee                              		 removeAdvisee 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::removeAdvisee(); //12
{
	cout << "Remove Advisee from faculty record" << endl;
	cout << "\tEnter faculty ID: " << endl;
    string userInput;
	cin >> userInput;
	facultyID = stoi(userInput);
    
    TreeNode<Faculty> *fac;
    fac = facultyBST.search(facultyID);
    
	if (fac!=NULL)
	{
		cout << "\tEnter student ID: " << endl;
		cin >> userInput;
		studentID = stoi(userInput);
        
        TreeNode<Student> *stu;
        stu = studentBST.search(studentID)
        
		if (stu!=NULL)
		{
            changeAdvisor(stu->data.ID);
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
//                rollback                              		 rollback 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::rollback(); //13
{
	if ( isFacRollback.isEmpty() )
    {
        cout << "Cannot undo. No stored changes available." << endl;
    }
    else
    {
        bool wasFac = isFacRollback.pop();
        if (wasFac)
        {
            facultyBST = facultyRollback.pop();
        }
        else
        {
            studentBST = studentRollback.pop();
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                	exit                              		 		exit 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::exit(); //14
{
    cout << "Saving data to file." << endl;
    
    saveFacultyTreeToFile(&facultyBST, "../saved/facultyTable");
    saveStudentTreeToFile(&studentBST, "../saved/studentTable");
    
	cout << "Goodbye" << endl;
    stop = true;
}