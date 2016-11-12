#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <iostream>

using namespace std;

//--------------------------------------------------------------------
//            THE NODE
//--------------------------------------------------------------------
template <class T>
class TreeNode
{
    /*
    This TreeNode contains a piece of data with type T
    There are pointers for the left and right subtrees
    The overloaded constructor takes a data T as input
    */
    public:
        T data;
        TreeNode *left;
        TreeNode *right;
        TreeNode();
        ~TreeNode();
        TreeNode(int k, T d);
};

template <class T>
TreeNode<T>::TreeNode()
{
    /*
    The constructor initializes pointers as NULL
    */
    left = NULL;
    right = NULL;
    cout << "Warning: TreeNode created without data or key." << endl;
}

template <class T>
TreeNode<T>:TreeNode(T d)
{
    /*
    Overloaded constructor sets pointers to NULL and data+key to the input
    */
    data = d;
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode()
{
    /*
    Destructor simply sets all pointers to NULL
    */
    left = NULL;
    right = NULL;
}

#endif