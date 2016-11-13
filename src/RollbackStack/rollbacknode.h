#ifndef _ROLLBACKNODE_H_
#define _ROLLBACKNODE_H_

#include <iostream>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                class RollbackNode                                 class RollbackNode
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
class RollbackNode
{
    /*
    This ListNode contains a piece of data with type T
    There are pointers for the next and prev elements of the list
    The overloaded constructor takes a data T as input
    */
    public:
        T data;
        RollbackNode *above;
        RollbackNode *below;
        RollbackNode();
        ~RollbackNode();
        RollbackNode(T d);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                constructor                                               constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
RollbackNode<T>::RollbackNode()
{
    /*
    The constructor initializes pointers as NULL
    */
    above = NULL;
    below = NULL;
    std::cout << "Warning: RollbackNode created without data" << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                overloaded constructor                          overloaded construcor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
RollbackNode<T>::RollbackNode(T d)
{
    /*
    Overloaded constructor sets pointers to NULL and data to the input
    */
    data = d;
    above = NULL;
    below = NULL;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                destructor                                                 destructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
ListNode<T>::~ListNode()
{
    /*
    Destructor simply sets all pointers to NULL
    */
    above = NULL;
    below = NULL;
}

#endif