#include "BST.cpp"
#include <iostream>
#include <string>

using namespace std;

class Database
{
	public:
		Database();
		Database(int maxSize);
		~Database();

		BST studentBST;
		BST facultyBST;

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
		int exit(); //14
	
		BST studentBST;
		BST facultyBST;
	

};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printStudents                              		 printStudents 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::printAllStudents() {
	cout << "Students by ascending ID: " << endl;
	studentBST.printTree(); 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printFaculty                              		 printFaculty 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::printAllFaculty() {
	//Option 1, in order traversal, prints beginning with minimum faculty ID
	cout << "Faculty: " << endl;
	facultyBST.printTree(); 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findStudent                              		 findStudent 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::findStudent(); //3
{
	cout << "Search by student ID number" << endl;
	cout << "\tEnter student ID number: ";
	cin >> studentID;
	studentID = stoi(studentID);
    TreeNode<Student> *stu = studentBST.search(studentID);
	if ( stu != NULL) // search returns pointer to node
		stu->print(); // prints all data on student
	else
		cout << "Student \"" << studentID << "\"  does not exist." << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findFaculty                             	 		 findFaculty 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::findFaculty(); //4
{
	cout << "Search by faculty ID number" << endl;
	cout << "\tEnter faculty ID number: ";
	cin >> facultyID;
	facultyID = stoi(facultyID);
    TreeNode<Faulty> *fac = facultyBST.search(facultyID);
	if ( fac != NULL ) // search returns pointer to node
		fac->print(); // all data on the faculty
	else
		cout << "Faculty member \"" << facultyID << "\"  does not exist." << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                findMyAdvisor                              		 findMyAdvisor 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::myAdvisorIs(); //5 
{
	cout << "Search student's faculty advisor" << endl;
	cout << "\tEnter student ID number: ";
	cin >> studentID;
	int studentID = stoi(studentID);
    TreeNode<Student> *stu = studentBST.search(studentID);
	if ( stu != NULL )
	{
		TreeNode<Faculty> *fac = facultyBST.search(stu->advisor);
        fac->print;
	}
	else
    {
		cout << "Student \"" << studentID << "\" does not exist." << endl;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                printAdvisees                              		 printAdvisees 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::myAdviseesAre(); //6
{
	cout << "Search for advisees" << endl;
	cout << "\tEnter faculty ID number: ";
	cin >> facultyID;
	int facultyID = stoi(facultyID);
    TreeNode<Faculty> *fac = facultyBST.search(facultyID);
	if ( fac != NULL )
	{
		//GET ALL STUDENTS USE FOR LOOP TO PRINT ALL
		fac->students.printList();
	}
	else
		cout << "Faculty member does not exist." << endl;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                classStanding                              		 classStanding 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

string Database::promptForClass()
{
	//this block of code prompts for student's class standing level and reprompts if invalid input
	cout << "Enter student's class standing: \n\t(1) Freshman \n\t(2) Sophomore \n\t (3) Junior \n\t(4) Senior \n\t(5) Graduate student" << endl;
	cin >> classLevel;
	classLevel = stoi(classLevel);
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
		promptForClass();
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addStudent                              		 addStudent 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::addStudent(); //7
{
	/*this block of code 
	1) prompts for student elements to fill in student node 
	2) inserts student node into the tree
	3) adds student to advisor list
	4) saves for rollback*/
	
	cout << "Add student to records" << endl;
	//studentID=NEEDS RANDOM GENERATOR OR OTHER TO GENERATE ID NUMBER
	//facultyID=NEEDS RANDOM GENERATOR OR OTHER TO GENERATE FACULTY ADVISOR
	cout << "Enter student's full name: " << endl;
	cin >> studentName;
	classStanding = promptForClass();
	cout << "Enter student's major: " << endl;
	cin >> studentMajor;
	cout << "Enter student GPA: " << endl;
	cin >> studentGPA;
	studentGPA = stod(studentGPA);
	
	new <studentnode>(studentID, studentName, classStanding, studentMajor, studentGPA, facultyID);
	cout << "Student has been added." << endl;
	studentBST.print(studentID);	//prints student info
	//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                deleteStudent                              		 deleteStudent 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::deleteStudent(); {
	//option 8
	//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK
	cout << "Delete student from records" << endl;
	cout << "\tEnter student ID: " << endl;
	cin >> studentID;
	studentID = stoi(studentID);

	if studentBST.search(studentID)
	{
		studentBST.delete(int studentID);
		//NEED TO DELETE STUDENT FROM ADVISORS LIST
		cout << "Student \"" << studentID << "\" has been deleted." << endl;
	}
	else
		cout << "Student \"" << studentID << "\" does not exist." << endl;
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
		professorship();
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                addFaculty                              		 addFaculty 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::addFaculty(); //9
{
	/*this block of code 
	1) prompts for faculty elements to fill in faculty node 
	2) inserts faculty node into the tree
	3) saves for rollback*/

	//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK
	cout << "Add falculty advisor to records" << endl;
	//studentID=NEEDS RANDOM GENERATOR OR OTHER TO GENERATE ID NUMBER
	//facultyID=NEEDS RANDOM GENERATOR OR OTHER TO GENERATE FACULTY ADVISOR
	cout << "Enter falculty advisor's full name: " << endl;
	cin >> facultyName;
	
	cout << "Enter professor level: " << endl;
	cin >> professorship;
	
	cout << "Enter falculty advisor's department: " << endl;
	cin >> department;
	
	new <facultynode>(facultyID, facultyname, professorship, department);
	cout << "Faculty advisor has been added." << endl;
	studentBST.print(studentID);	//prints student info
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                deleteFaculty                              		 deleteFaculty 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::deleteFaculty(); //10
{
	/*This block of code 
	1) deletes faculty from records
	2) reassigns students to a new faculty member
	3) saves tree for rollback
	*/

	cout << "Delete faculty from records" << endl;
	cout << "\tEnter faculty ID: " << endl;
	cin >> facultyID;
	facultyID = stoi(facultyID);
	if facultyBST.search(facultyID) {
		facultyBST.delete(int facultyID);
		//NEED TO REASSIGN all STUDENTS TO A NEW ADVISOR
		cout << "Faculty \"" << facultyID << "\" has been deleted." << endl;
	}
	else
		cout << "Faculty \"" << facultyID << "\" does not exist." << endl;
		//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                changeAdvisor                              		 changeAdvisor 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::changeAdvisor(); //11
{
	/*
	needs to remove from advisor's list & change new advisor
	*/
	
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                removeAdvisee                              		 removeAdvisee 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::removeAdvisee(); //12
{
	cout << "Remove Advisee from faculty record" << endl;
	cout << "\tEnter faculty ID: " << endl;
	cin >> facultyID;
	facultyID = stoi(facultyID);

	if (facultyBST.search(facultyID) 
	{
		cout << "\tEnter student ID: " << endl;
		cin >> studentID;
		studentID = stoi(studentID);
		if (studentBST.search(studentID) 
		{
			x = FACULTY.find(studentID); //need help on how to use facultynode .find()
			if (x==-1)
				cout << "Student #" << studentID << " is not an advisee of Faculty #" << facultyID << "." << endl;
			else
			{
				FACULTY.remove(studentID); //again, how to use facultynode .remove()
				//call function to reassign 
				//remove from student record, and assign a new faculty advisor
			}	
		}
		else
			cout << "Student not found." << endl;
	}
	else
		cout << "Faculty member not found." << endl;

/*
faculty must exist
student must exist
faculty must have student as advisor
if all true:
	delete advisee
	reassign advisee
*/
}
			
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                rollback                              		 rollback 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Database::rollback(); //13
{
	//USES STACK TO GET LAST TREE "UNDO BUTTON"
	//ERIC THATS ALL YOU LOL
	

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                	exit                              		 		exit 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int Database::exit(); //14
{
	//NEEDS TO SAVE TREE TO HARD DRIVE SO THAT IT CAN REOPEN
	cout << "Goodbye" << endl;
	return 0;
}
 
