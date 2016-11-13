















//ABSOLUTELY NONE OF THIS HAS BEEN TESTED

//still need input from file and check for file

//input from fle should check for formatting errors

//if error is found, exit. tell user to fix files or delete them




#include <iostream>
#include <string>

void saveStudentTreeToFile(BSTree<Student> *tree, std::string filename)
{
	/*
	We can save to a file using simple text
	If we use pre-order traversal, then everything will
	be written to the file in such a manner that reading
	the file in the order it is written reconstructs the
	tree exactly. Thus, the output file should look like:
	
	01208230981	//ID#
	Billy Hill	//name
	Freshman	//level
	Psychology	//major
	3.75		//gpa
	71238924789	//advisorid
	65154651234	//next student
	Joe Schmo
	...
	*/
	ofstream ofs (filename);
	
	saveStuRecur(tree->root, ofs);
}

// Helper Functions for saving students

void saveStuRecur(TreeNode<Student> *root, ofstream ofs)
{
	stuToFile(root->data, ofs);
	saveStuRecur(root->left, ofs);
	saveStuRecur(root->right, ofs);
}

void stuToFile(Student stu, ofstream ofs);
{
	ofs << stu.ID << std::endl;
	ofs << stu.name << std::endl;
	ofs << stu.level << std::endl;
	ofs << stu.major << std::endl;
	ofs << stu.GPA << std::endl;
	ofs << stu.advisor << std::endl;
}

//basically the same for faculty

void saveFacultyTreeToFile(BSTree<Faculty> *tree, std::string filename)
{
	/*
	We can save to a file using simple text
	If we use pre-order traversal, then everything will
	be written to the file in such a manner that reading
	the file in the order it is written reconstructs the
	tree exactly. Thus, the output file should look like:
	
	78945312564	//ID#
	Jeff Dahmer	//name
	Professor	//level
	Psychology	//dept
	2			//number of students
	45645645665	//first student
	65154651234	//next student
	13215484651 //id of next faculty member
	Snoop Dogg
	...
	*/
	ofstream ofs (filename);
	
	saveFacRecur(tree->root, ofs);
}

// Helper Functions for saving faculty

void saveFacRecur(TreeNode<Faculty> *root, ofstream ofs)
{
	facToFile(&(root->data), ofs);
	saveFacRecur(root->left, ofs);
	saveFacRecur(root->right, ofs);
}

void facToFile(Faculty *fac, ofstream ofs)
{
	ofs << fac->ID << std::endl;
	ofs << fac->name << std::endl;
	ofs << fac->level << std::endl;
	ofs << fac->dept << std::endl;
	ofs << fac->numStudents << std::endl;
	facStuToFile(fac, ofs); //this function should go through the list and save each students id number
}

facStuToFile(Faculty *fac, ofstream ofs)
{
	ListNode<int> *curr = fac->students->front; //make sure this matches the list implimentation and list has front as protected, not private
	for (int i=0; i<fac->numStudents; ++i)
	{
		ofs << curr->data << std::endl;
		curr = curr->next;
	}
}



