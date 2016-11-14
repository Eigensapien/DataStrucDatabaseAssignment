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

};

#include <string>

int promptForStudentID() 
{
	cout << "\tEnter student ID number: ";
	cin >> studentID;
	studentID = stoi(studentID); //from your
	if (!studentBST.search(studentID)) {
		cout << "Student \"" << studentID << "\"  does not exist." << endl;
		promptForStudentID();
	}
	else 
		return studentID:
}

int promptForFacultyID() 
{
	cout << "\tEnter faculty ID number: ";
	cin >> facultyID;
	facultyID = stoi(facultyID); //from your
	if (!studentBST.search(facultyID)) {
		cout << "Student \"" << facultyID << "\"  does not exist." << endl;
		promptForID();
	}
	else 
		return facultyID:
}







void Database::printAllStudents() {
	//Option 1, in order traversal, prints beginning with minimum student ID
	cout << "Students: " << endl;
	studentBST.inOrderPrint(masterStudent.minBST()); 
}

void Database::printAllFaculty() {
	//Option 1, in order traversal, prints beginning with minimum faculty ID
	cout << "Faculty: " << endl;
	facultyBST.inOrderPrint(masterFaculty.minBST()); 
}

void Database::findStudent(); //3
{
	cout << "Search by student ID number" << endl;
	cout << "\tEnter student ID number: ";
	cin >> studentID;
	studentID = stoi(studentID);
	if studentBST.search(studentID)
		cout << studentBST.print(studentID);
	else
		cout << "Student \"" << studentID << "\"  does not exist." << endl;
}


void Database::findFaculty(); //4
{
	cout << "Search by faculty ID number" << endl;
	cout << "\tEnter faculty ID number: ";
	cin >> facultyID;
	facultyID = stringToInt(facultyID);
	if facultyBST.search(facultyID)
		cout << facultyBST.print(facultyID);
	else
		cout << "Faculty member \"" << facultyID << "\"  does not exist." << endl;
}

void Database::myAdvisorIs(); //5 
{
	cout << "Search student's faculty advisor" << endl;
	cout << "\tEnter student ID number: ";
	cin >> studentID;
	studentID = stringToInt(studentID);
	if studentBST.search(studentID)
	{
		//GET FACULTY ID NUMBER
		cout << facultyBST.print(facultyID);
	}
	else
		cout << "Student \"" << studentID << "\" does not exist." << endl;
}

void Database::myAdviseesAre(); //6
{
	cout << "Search for advisees" << endl;
	cout << "\tEnter faculty ID number: ";
	cin >> facultyID;
	facultyID = stringToInt(facultyID);
	if facultyBST.search(facultyID)
	{
		//GET ALL STUDENTS USE FOR LOOP TO PRINT ALL
		cout << facultyBST.print(facultyID);
	}
	else
		cout << "Faculty member does not exist." << endl;
}


string Database::promptForClass()
{
	//this block of code prompts for student's class standing level and reprompts if invalid input
	cout << "Enter student's class standing: \n\t(1) Freshman \n\t(2) Sophomore \n\t (3) Junior \n\t(4) Senior \n\t(5) Graduate student" << endl;
	cin >> classLevel;
	classLevel = stringToInt(classLevel);
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

void Database::deleteStudent(); {
	//option 8
	//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK
	cout << "Delete student from records" << endl;
	cout << "\tEnter student ID: " << endl;
	cin >> studentID;
	studentID = stringToInt(studentID);

	if studentBST.search(studentID)
	{
		studentBST.delete(int studentID);
		//NEED TO DELETE STUDENT FROM ADVISORS LIST
		cout << "Student \"" << studentID << "\" has been deleted." << endl;
	}
	else
		cout << "Student \"" << studentID << "\" does not exist." << endl;
}

string Database::professorship()
{
	//this block of code prompts for professorship level and reprompts if invalid input
	cout << "Enter faculty member's level of professorship: \n\t(1) Full Professor \n\t(2) Assistant Professor \n\t (3) Associate Professor \n\t(4) Adjunct Professor \n\t(5) Lecturer" << endl;
	cin >> profLevel;
	profLevel = stringToInt(classLevel);
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


void Database::deleteFaculty(int facultyID); //10
{
	/*This block of code 
	1) deletes faculty from records
	2) reassigns students to a new faculty member
	3) saves tree for rollback
	*/

	cout << "Delete faculty from records" << endl;
	cout << "\tEnter faculty ID: " << endl;
	cin >> facultyID;
	facultyID = stringToInt(facultyID);
	if facultyBST.search(facultyID) {
		facultyBST.delete(int facultyID);
		//NEED TO REASSIGN all STUDENTS TO A NEW ADVISOR
		cout << "Faculty \"" << facultyID << "\" has been deleted." << endl;
	}
	else
		cout << "Faculty \"" << facultyID << "\" does not exist." << endl;
		//NEEDS TO HAVE A SAVE TREE FUNCTION SO WE CAN DO ROLLBACK

}

void Database::changeAdvisor(int studentID); //11
{

}


void Database::removeAdvisee(int facultyID); //12
{
	cout << "Remove Advisee from faculty record" << endl;
	cout << "\tEnter faculty ID: " << endl;
	cin >> facultyID;
	facultyID = stringToInt(facultyID);

	if (facultyBST.search(facultyID)
		cout << "\tEnter student ID: " << endl;
		cin >> studentID;
		studentID = stringToInt(studentID);
		if (studentBST.search(studentID) {
			//SEARCH IF 
		}
		

	}
}
/*
faculty must exist
student must exist
faculty must have student as advisor
if all true:
	delete advisee
	reassign advisee
*/

void Database::rollback(); //13
{
	//USES STACK TO GET LAST TREE "UNDO BUTTON"
	//ERIC THATS ALL YOU LOL

}

int Database::exit(); //14
{
	//NEEDS TO SAVE TREE TO HARD DRIVE SO THAT IT CAN REOPEN
	cout << "Goodbye" << endl;
	return 0;
}
