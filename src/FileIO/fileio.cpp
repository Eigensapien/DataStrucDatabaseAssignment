















//ABSOLUTELY NONE OF THIS HAS BEEN TESTED

//still need input from file and check for file

//input from fle should check for formatting errors

//if error is found, exit. tell user to fix files or delete them


//need to parse: strings, ints



//this function returns an int error code and modifies its first argument directly by adding stuff from the file to a (hopefully) empty tree
int importStudentTree(BSTree<Student> *tree, string filename)
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
    getline(ifs, currLine); //First line should be "_STARTSTUDENT_". This gives a way to know when to stop.
    
    if (currLine != "_STARTSTUDENT_")
    {                               //output error and exit function without importing.
        if (ifs.is_open()) { ifs.close(); };
        cout << "Error: Student file does not begin with _STARTSTUDENT_ ." << endl;
        return 1;
    }
    
    Student stu;
    
    while (currLine=="_STARTSTUDENT_") //ie. until we run out of students
    {
        getline(ifs, currLine); // ID number
        stu.ID = std::stoi(currLine); //need to make or find this
        
        getline(ifs, stu.name); //name
        getline(ifs, stu.level); //level
        getline(ifs, stu.major); //major
        
        getline(ifs, currLine); //GPA
        stu.GPA = std::stod(currLine); //need to make this or find this
        
        getline(ifs,currLine); //advisor
        stu.advisor = std::stoi(currLine); //need to make or find this
        
        tree->insert(stu); //place them in the tree
        
        getline(ifs, currLine); // "_STARTSTUDENT_" if there is another, blank otherwise
    }
    
    std::cout << "Student data has been imported." << std::endl;
}






//this function returns an int error code and modifies its first argument directly by adding stuff from the file to a (hopefully) empty tree
int importStudentTree(BSTree<Student> *tree, string filename)
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
    getline(ifs, currLine); //First line should be "_STARTFACULTY_". This gives a way to know when to stop.
    
    if (currLine != "_STARTFACULTY_")
    {                               //output error and exit function without importing.
        if (ifs.is_open()) { ifs.close(); };
        cout << "Error: Faculty file does not begin with _STARTFACULTY_ ." << endl;
        return 1;
    }
    
    Faculty fac;
    int numStu;
    
    while (currLine=="_STARTFACULTY_") //ie. until we run out of faculty
    {
        getline(ifs, currLine); // ID number
        fac.ID = std::stoi(currLine); //need to make or find this
        
        getline(ifs, fac.name); //name
        getline(ifs, fac.level); //level
        getline(ifs, fac.dept); //dept
        
        getline(ifs, currLine); //number of students
        numStu = std::stoi(currLine); //need to make this or find this
        
        for (int i=0; i<numStu; ++i) //loop over list of students
        {
            getline(ifs, currLine); //student's ID
            fac.students.insert( std::stoi(currLine) );
        }
        
        tree->insert(fac); //put them in the tree
        
        getline(ifs, currLine); // "_STARTFACULTY_" if there are more, blank otherwise
    }
    std::cout << "Faculty data has been imported." << std::endl;
}


























#include <iostream>
#include <string>

void saveStudentTreeToFile(BSTree<Student> *tree, std::string filename)
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
    ofs << "_STARTSTUDENT_" << std::endl;
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

void facStuToFile(Faculty *fac, ofstream ofs)
{
	ListNode<int> *curr = fac->students->front; //make sure this matches the list implimentation and list has front as protected, not private
	for (int i=0; i<fac->numStudents; ++i)
	{
		ofs << curr->data << std::endl;
		curr = curr->next;
	}
}



