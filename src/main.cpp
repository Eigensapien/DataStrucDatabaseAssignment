#include <iostream>
#include "./include/bstree.h"
#include "./include/student.h"
#include "./include/faculty.cpp"
#include "./include/fileio.cpp"
#include "./include/dbfuncs.cpp"
#include "./include/rollbackstack.h"

// main is very simple, since the Database class handles everything

int main(int argc, char** argv)
{
    // invoking the constructor imports or creates files
    Database *db = new Database;
    
    // a bool tells us when the user has exited
    while (!db->stop)
    {
        // showMenu presents options to the user and executes other functions as needed
        db->showMenu();
    }
    
    // when finished, free the memory
    delete db;
    return 0;
}