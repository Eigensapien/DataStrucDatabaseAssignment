/*
I still haven't actually tested this ting to see if it works properly.
If it does it will be the basis of the database.
The names of functions and whatnot shouldnt change, so other stuff can be developed under
the assumption that this thing either works or will work eventually.
*/




#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include "treenode.h"

using namespace std;



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                class BST                                                 class BST
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/********************************************
 * Template class for a binary search tree  *
 * Each node holds an int key and a T value *
 * T must have a print() function           *
 ********************************************/
template <class T>
class BST {
    public:
        BST();
        ~BST();
        int insert(T data);
        TreeNode<T>* search(int key);
        bool isEmpty();
        TreeNode<T>* getMin();
        TreeNode<T>* getMax();
        void print(TreeNode<T>* node);
        void printTree();
        bool deleteN(int k);
    private:
        TreeNode<T>* root;
        void deleteTree(TreeNode<T>* node);
        TreeNode<T>* getSuccessor(TreeNode<T>* d);
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       constructor                                     constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
BST<T>::BST()
{
    root = NULL;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      destructor                                        destructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
BST<T>::~BST()
{
    deleteTree(root);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       deleteTree                                       deleteTree
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A helper function for the destructor
template <class T>
void BST<T>::deleteTree(TreeNode<T>* node)
{
    if (node != NULL) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       insert                                                 insert
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
 * insert(data) takes data and place it in the tree
 * returns an error code:
 *    0: worked normally
 *    1: position full
 */
template <class T>
int BST<T>::insert(T data)
{
    TreeNode<T>* node = new TreeNode<T>(data);
    if (isEmpty())
    { // single-element tree
        root=node;
    }
    else
    { // search the tree for key
        TreeNode<T>* curr = root;
        TreeNode<T>* parent;
        while (true)
        {
            parent = curr;
            if (data < curr->data) //go left
            {
                curr = curr->left;
                if (curr==NULL) //found leaf
                {
                    parent->left = node;
                    return 0;
                }
            }
            else if (data > curr->data) //go right
            {
                curr = curr->right;
                if (curr==NULL) //found leaf
                {
                    parent->right = node;
                    return 0;
                }
            }
            else
            {
                // No error message since this will occur naturally
                // due to students randomly assigned the same id number.
                // The return code allows this to be handled by generating
                // a new id number inside main.cpp and trying until an
                // unused number is found
                return 1;
            }
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       search                                                 search
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
 * search(data) takes a key as input and returns a pointer to
 * the node at that position if it exists.
 * Returns NULL pointer if not found.
 * Code is largely copied from insert.
 */
template <class T>
TreeNode<T>* BST<T>::search(int key)
{
    if (isEmpty())
    {
        return NULL;
    }
    else
    { // search the tree for key
        TreeNode<T>* curr = root;
        while (true)
        {
            if (key < curr->data) //go left
            {
                curr = curr->left;
                if (curr==NULL) //end of branch, not found
                {
                    return NULL;
                }
            }
            else if (key > curr->data) //go right
            {
                curr = curr->right;
                if (curr==NULL) //end of branch, not found
                {
                    return NULL;
                }
            }
            else // found it
            {
                return curr;
            }
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       isEmpty                                                isEmpty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
bool BST<T>::isEmpty()
{
    return root==NULL;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       getMin                                                  getMin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// returns a pointer to the element with lowest key (leftmost)
template <class T>
TreeNode<T>* BST<T>::getMin()
{
    if (isEmpty())
    {
        return NULL;
    }
    else
    {
        TreeNode<T>* curr = root;
        while (curr->left != NULL)
        {
            curr = curr->left;
        }
        return curr;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       getMin                                                  getMax
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// returns a pointer to the element with highest key (rightmost)
template <class T>
TreeNode<T>* BST<T>::getMax()
{
    if (isEmpty())
    {
        return NULL;
    }
    else
    {
        TreeNode<T>* curr = root;
        while (curr->right != NULL)
        {
            curr = curr->right;
        }
        return curr;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       print                                                    print
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
void BST<T>::print(TreeNode<T>* node)
{
    if (node==NULL)
    {
        return;
    }
    print(node->left);
    //cout << node->data << endl; //uncomment this line and comment out the next for test with ints
    node->data.print(); // Requires data type to have defined print() function
    print(node->right);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       printTree                                            printTree
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
void BST<T>::printTree()
{
    print(root);
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       getSuccessor                                      getSuccessor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//helper function for delete case with two children
template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d)
{
    TreeNode<T>* sp = d;
    TreeNode<T>* successor = d;
    TreeNode<T>* current = d->right;
    
    while(current != NULL)
    {
        sp = successor;
        successor = current;
        current = current->left;
    }
    
    if (successor != d->right)
    {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                       deleteN                                      deleteN
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// deletes node with key k and returns true if sucessful, false if unsucessful
template <class T>
bool BST<T>::deleteN(int k)
{
    //if leaf, easy
    //if 1 child, sorta easy
    //if 2 child, need to find successor=leftmost child of right child of node being deleted
    //note: that node must have no left children (as that would be the successor)
    
    //standard sanity checks
    if(isEmpty()) {
        return false;
    }
    
    TreeNode<T>* parent = root;
    TreeNode<T>* current = root;
    bool isLeft = true;
    
    while (current->data != k) //look for node to delete
    {
        parent = current;
        if(k < current->data) //go left
        {
            isLeft = true;
            current = current->left;
        }
        else //go right
        {
            isLeft = false;
            current = current->right;
        }
        
        if(current==NULL) { //not in tree
            return false;
        }
    }
    //if we get here, we have found the node to be deleted
    
    //now we check our cases
    
    //leaf, easy
    if (current->left==NULL && current->right==NULL)//no children
    {
        if(current==root) {
            root = NULL;//deleted the root
        }
        else if(isLeft)
        {
            parent->left = NULL;
        }
        else//isRight
        {
            parent->right = NULL;
        }
    }
    else if(current->right==NULL ) //one child, left child
    {
        if (current==root)
        {
            root = current->left;
        }
        else if(isLeft)
        {
            parent->left = current->left;
        }
        else //is right child
        {
            parent->right = current->left;
        }
    }
    else if(current->left==NULL ) //one child, right child
    {
        if (current==root)
        {
            root = current->right;
        }
        else if(isLeft)
        {
            parent->right = current->right;
        }
        else //is right child
        {
            parent->right = current->right;
        }
    }
    else //two children
    {
        TreeNode<T> *successor = getSuccessor(current);
        
        if(current==root)
        {
            root = successor;
        }
        else if(isLeft)
        {
            parent->left = successor;
        }
        else
        {
            parent->right = successor;
        }
        successor->left = current->left;
    }
    delete current;
    return true;
}









#endif