#include <iostream>
#include "bstree.h"
#include "treenode.h"

using namespace std;

// NOTE: For this to work, printTree() needs to be modified since int does not have a print() function.
// Remember to change it back when done testing.

int main(int argc, char** argv)
{
    BST<int> tree;
    
    cout << "Inserting 3,1,5" << endl;
    tree.insert(3);
    tree.insert(1);
    tree.insert(5);
    
    tree.printTree();
    
    cout << "Searching for 3" << endl;
    
    TreeNode<int> *result;
    result = tree.search(3);
    cout << result->data << endl;
    
    
    cout << "Getmin" << endl;
    
    result = tree.getMin();
    cout << result->data << endl;
    
    cout << "Getmax" << endl;
    
    result = tree.getMax();
    cout << result->data << endl;
    
    cout << "deleting 5" << endl;
    
    tree.deleteN(5);
    tree.printTree();
    
}