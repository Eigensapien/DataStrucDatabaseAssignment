#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "bstree.h"
#include "student.h"
#include "faculty.h"
#include <fstream>

using std::ofstream;

int importStudentTree(BST<Student> *tree, std::string filename);

int importFacultyTree(BST<Faculty> *tree, std::string filename);

void saveStudentTreeToFile(BST<Student> *tree, std::string filename);

void saveStuRecur(TreeNode<Student> *root, ofstream *ofs);

void stuToFile(Student stu, ofstream *ofs);

void saveFacultyTreeToFile(BST<Faculty> *tree, std::string filename);

void saveFacRecur(TreeNode<Faculty> *root, ofstream *ofs);

void facToFile(Faculty *fac, ofstream *ofs);

void facStuToFile(Faculty *fac, ofstream *ofs);

#endif