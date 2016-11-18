#include <iostream>
#include <fstream>
#include <string>
#include "bstree.h"
#include "listnode.h" //to navigate faculty list
#include "userinput.h"

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

string stuPath = "../saved/studentTable";
string facPath = "../saved/facultyTable";

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                importStudentTree()                               importStudentTree()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * int importStudentTree(BST<Student> *tree, string filename)                      *
 *                                                                                    *
 * This function imports the student data stored at filename and adds the students to *
 * the BST stored at tree.                                                            *
 *                                                                                    *
 * Returns an error code                                                              *
 * 0: imported properly                                                               *
 * 1: import failed                                                                   *
 **************************************************************************************/

int importStudentTree(BST<Student> *tree, string filename)
{
    ifstream ifs ( filename.c_str() ); //open the file
    
    if (!ifs)                       //if the given filename doesn't work,
    {                               //output error and exit function without importing.
        if (ifs.is_open()) { ifs.close(); };
        cout << "Error: Student file cannot be opened." << endl;
        return 1;
    }
    
    string currLine;
    getline(ifs, currLine); //First line should be "_STARTSTUDENT_"
    
    // if the first line is "_EMPTY_" we can stop. We already have an empty tree.
    if (currLine == "_EMPTY_")
    {
        return 0;
    }
    
    if (currLine != "_STARTSTUDENT_")
    {                               //output error and exit function without importing.
        if (ifs.is_open()) { ifs.close(); };
        std::cout << "Error: Student file does not begin with _STARTSTUDENT_ ." << std::endl;
        std::cout << "Please repair or delete the file manually." << std::endl;
        return 1;
    }
    
    Student *stu = new Student; //tree insert takes care of this for us
    
    while (currLine=="_STARTSTUDENT_") //ie. until we run out of students
    {
        getline(ifs, currLine); // ID number
        stu->ID = stringToInt(currLine); //convert to int
        
        getline(ifs, stu->name);  //name
        getline(ifs, stu->level); //level
        getline(ifs, stu->major); //major
        
        getline(ifs, currLine); //GPA
        stu->GPA = stringToDouble(currLine); //convert to double
        
        getline(ifs,currLine); //advisor
        stu->advisor = stringToInt(currLine); //convert to int
        
        tree->insert(stu); //place the student in the tree
        
        getline(ifs, currLine); // "_STARTSTUDENT_" if there is another, "_ENDFILE_" otherwise
    }
    cout << "Student data has been imported." << endl;
    stu=NULL;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                importFacultyTree()                               importFacultyTree()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************
 * int importFacultyTree(BST<Faculty> *tree, string filename)                      *
 *                                                                                    *
 * This function imports the faculty data stored at filename and adds the faculty to  *
 * the BST stored at tree.                                                            *
 *                                                                                    *
 * Returns an error code                                                              *
 * 0: imported properly                                                               *
 * 1: import failed
 *
 * If files are not in proper format, segfaults can occur
 **************************************************************************************/

int importFacultyTree(BST<Faculty> *tree, string filename)
{
    ifstream ifs ( filename.c_str() ); //open the file
    
    if (!ifs)                       //if the given filename doesn't work,
    {                               //output error and exit function without importing.
        if (ifs.is_open()) { ifs.close(); };
        cout << "Error: Faculty file cannot be opened." << endl;
        return 1;
    }
    
    string currLine;
    getline(ifs, currLine); //First line should be "_STARTFACULTY_"
    
    // if the first line is "_EMPTY_" we can stop. We already have an empty tree.
    if (currLine == "_EMPTY_")
    {
        return 0;
    }
    
    if (currLine != "_STARTFACULTY_")
    {                               //output error and exit function without importing.
        if (ifs.is_open()) { ifs.close(); };
        cout << "Error: Faculty file does not begin with _STARTFACULTY_ ." << endl;
        cout << "Please repair or delete the file manually." << endl;
        return 1;
    }
    
    Faculty *fac = new Faculty; //this is deleted when inserted into the tree
    int numStu;
    
    while (currLine=="_STARTFACULTY_") //ie. until we run out of faculty
    {
        getline(ifs, currLine); // ID number
        fac->ID = stringToInt(currLine); //convert to int

        getline(ifs, fac->name);  //name
        getline(ifs, fac->level); //level
        getline(ifs, fac->dept);  //dept
        
        getline(ifs, currLine); //number of students
        numStu = stringToInt(currLine); //convert to int
        
        for (int i=0; i<numStu; ++i) //loop over list of students
        {
            getline(ifs, currLine); //student's ID
            fac->students.insertFront( stringToInt(currLine) ); //convert to int and add to list
        }
        
        tree->insert(fac); //put the faculty in the tree
        
        getline(ifs, currLine); // "_STARTFACULTY_" if there are more, "_ENDFILE_" otherwise
    }
    cout << "Faculty data has been imported." << endl;
    fac = NULL;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveStudent helpers                               saveStudent helpers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//output to file
void stuToFile(Student stu, ofstream *ofs)
{
    *ofs << "_STARTSTUDENT_" << endl;
	*ofs << stu.ID           << endl;
	*ofs << stu.name         << endl;
	*ofs << stu.level        << endl;
	*ofs << stu.major        << endl;
	*ofs << stu.GPA          << endl;
	*ofs << stu.advisor      << endl;
}

//Recursive pre-order traversal
void saveStuRecur(TreeNode<Student> *root, ofstream *ofs)
{
    if ( root != NULL )
    {
        stuToFile(root->data, ofs);
	    saveStuRecur(root->left, ofs);
	    saveStuRecur(root->right, ofs);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveStudentTreeToFile()                       saveStudentTreeToFile()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void saveStudentTreeToFile(BST<Student> *tree, string filename)
{
	/*
	We can save to a file using simple text
	If we use pre-order traversal, then everything will
	be written to the file in such a manner that reading
	the file in the order it is written reconstructs the
	tree exactly. We also need an identifier so that the
    import function has information about when to stop.
    Thus, the output file should look like:
	
    _STARTSTUDENT_ //indicator
	01208230981	   //ID#
	Billy Hill	   //name
	Freshman	   //level
	Psychology	   //major
	3.75		   //gpa
	71238924789	   //advisorid
	65154651234	   //next student
	Joe Schmo
	...
    
    Empty tree creates file with just "_EMPTY_"
	*/
	ofstream ofs ( filename.c_str() );
    
    if ( tree->isEmpty() )
    {
        ofs << "_EMPTY_" << endl;
    }
    else
    {
	    saveStuRecur(tree->root, &ofs);
    }
    ofs << "_ENDFILE_" << endl;
    ofs.close();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveFaculty helpers                               saveFaculty helpers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//output list of students
void facStuToFile(Faculty *fac, ofstream *ofs)
{
    if (fac->numStudents==0) {
        return;
    }
	ListNode<int> *curr = fac->students.front;
	for (int i=0; i<fac->numStudents; ++i)
	{
        //print list of students
		*ofs << curr->data << endl;
		curr = curr->next;
	}
}

//formats and prints data from faculty
void facToFile(Faculty *fac, ofstream *ofs)
{
    *ofs << "_STARTFACULTY_" << endl;
	*ofs << fac->ID          << endl;
	*ofs << fac->name        << endl;
	*ofs << fac->level       << endl;
	*ofs << fac->dept        << endl;
	*ofs << fac->numStudents << endl;
	facStuToFile(fac, ofs);
}

//Recursive pre-order traversal
void saveFacRecur(TreeNode<Faculty> *root, ofstream *ofs)
{
    if ( root != NULL )
    {
	    facToFile(&(root->data), ofs);
        saveFacRecur(root->left, ofs);
	    saveFacRecur(root->right, ofs);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveFacultyTreeToFile()                       saveFacultyTreeToFile()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void saveFacultyTreeToFile(BST<Faculty> *tree, std::string filename)
{
	/*
	We can save to a file using simple text
	If we use pre-order traversal, then everything will
	be written to the file in such a manner that reading
	the file in the order it is written reconstructs the
	tree exactly. An indicator helps with file import.
    Thus, the output file should look like:
	
    _STARTFACULTY_ //indicator
	78945312564	   //ID#
	Jeff Dahmer	   //name
	Professor	   //level
	Psychology	   //dept
	2			   //number of students
	45645645665	   //first student
	65154651234	   //next student
	13215484651    //id of next faculty member
	Snoop Dogg
	...
    
    Empty tree creates file with just "_EMPTY_"
	*/
	ofstream ofs ( filename.c_str() );
	
    if ( tree->isEmpty() )
    {
        ofs << "_EMPTY_" << endl;
    }
    else
    {
	    saveFacRecur(tree->root, &ofs);
    }
    ofs << "_ENDFILE_" << endl;
    ofs.close();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                filesExist                                                 filesExist
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool filesExist()
{
    std::ifstream stuFile (stuPath);
    bool stuTest = stuFile.good();
    std::ifstream facFile (facPath);
    bool facTest = facFile.good();
    return (facTest && stuTest);
}