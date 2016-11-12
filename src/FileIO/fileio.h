/*
Functions for dealing with saving and loading files

need to figure out a good format to store the data so that it can be easily loaded up
i think he mentioned a way to store the actual tree itself as a binary file, so that's probably the way to go
*/


#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "../BSTree/bstree.h"

bool filesExist();

BST<Student> newMasterStudent();

BST<Faculty> newMasterFaculty();

BST<Student> importMasterStudent();

BST<Faculty> importMasterFaculty();

void saveDatabase();

//probably need more stuff too


#endif