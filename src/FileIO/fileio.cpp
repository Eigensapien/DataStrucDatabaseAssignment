#include <iostream>
#include <fstream>
#include <string>
#include "../BSTree/bstree.h"
#include "../People/Faculty/List/listnode.h" //to navigate faculty list

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;

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
    ifstream ifs;
    
    ifs.open( filename ); //open the file
    
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
    
    Student stu;
    
    while (currLine=="_STARTSTUDENT_") //ie. until we run out of students
    {
        getline(ifs, currLine); // ID number
        stu.ID = std::stoi(currLine); //convert to int
        
        getline(ifs, stu.name);  //name
        getline(ifs, stu.level); //level
        getline(ifs, stu.major); //major
        
        getline(ifs, currLine); //GPA
        stu.GPA = std::stod(currLine); //convert to double
        
        getline(ifs,currLine); //advisor
        stu.advisor = std::stoi(currLine); //convert to int
        
        tree->insert(stu); //place the student in the tree
        
        getline(ifs, currLine); // "_STARTSTUDENT_" if there is another, blank otherwise
    }
    
    cout << "Student data has been imported." << endl;
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
 * 1: import failed                                                                   *
 **************************************************************************************/

int importFacultyTree(BST<Faculty> *tree, string filename)
{
    ifstream ifs;
    
    ifs.open( filename ); //open the file
    
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
    
    Faculty fac;
    int numStu;
    
    while (currLine=="_STARTFACULTY_") //ie. until we run out of faculty
    {
        getline(ifs, currLine); // ID number
        fac.ID = std::stoi(currLine); //convert to int
        
        getline(ifs, fac.name);  //name
        getline(ifs, fac.level); //level
        getline(ifs, fac.dept);  //dept
        
        getline(ifs, currLine); //number of students
        numStu = std::stoi(currLine); //convert to int
        
        for (int i=0; i<numStu; ++i) //loop over list of students
        {
            getline(ifs, currLine); //student's ID
            fac.students.insert( std::stoi(currLine) ); //convert to int and add to list
        }
        
        tree->insert(fac); //put the faculty in the tree
        
        getline(ifs, currLine); // "_STARTFACULTY_" if there are more, blank otherwise
    }
    cout << "Faculty data has been imported." << endl;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveStudentTreeToFile()                       saveStudentTreeToFile()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void saveStudentTreeToFile(BST<Student> *tree, std::string filename)
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
	ofstream ofs (filename);
    
    if ( tree->isEmpty() )
    {
        ofs << "_EMPTY_";
    }
    else
    {
	    saveStuRecur(tree->root, ofs);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveStudent helpers                               saveStudent helpers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Recursive pre-order traversal
void saveStuRecur(TreeNode<Student> *root, ofstream ofs)
{
	stuToFile(root->data, ofs);
	saveStuRecur(root->left, ofs);
	saveStuRecur(root->right, ofs);
}

//output to file
void stuToFile(Student stu, ofstream ofs);
{
    ofs << "_STARTSTUDENT_" << std::endl;
	ofs << stu.ID << std::endl;
	ofs << stu.name << std::endl;
	ofs << stu.level << std::endl;
	ofs << stu.major << std::endl;
	ofs << stu.GPA << std::endl;
	ofs << stu.advisor << std::endl;
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
	ofstream ofs (filename);
	
    if ( tree->isEmpty() )
    {
        ofs << "_EMPTY_";
    }
    else
    {
	    saveFacRecur(tree->root, ofs);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                saveFaculty helpers                               saveFaculty helpers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Recursive pre-order traversal
void saveFacRecur(TreeNode<Faculty> *root, ofstream ofs)
{
	facToFile(&(root->data), ofs);
	saveFacRecur(root->left, ofs);
	saveFacRecur(root->right, ofs);
}

//output to file
void facToFile(Faculty *fac, ofstream ofs)
{
	ofs << fac->ID          << std::endl;
	ofs << fac->name        << std::endl;
	ofs << fac->level       << std::endl;
	ofs << fac->dept        << std::endl;
	ofs << fac->numStudents << std::endl;
	facStuToFile(fac, ofs);
}

//output list of students
void facStuToFile(Faculty *fac, ofstream ofs)
{
	ListNode<int> *curr = fac->students->front;
	for (int i=0; i<fac->numStudents; ++i)
	{
		ofs << curr->data << std::endl;
		curr = curr->next;
	}
}