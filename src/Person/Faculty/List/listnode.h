#ifndef _LISTNODE_H_
#define _LISTNODE_H_

#include <iostream>

using namespace std;

//--------------------------------------------------------------------
//            THE NODE
//--------------------------------------------------------------------
template <class T>
class ListNode
{
    /*
    This ListNode contains a piece of data with type T
    There are pointers for the next and prev elements of the list
    The overloaded constructor takes a data T as input
    */
    public:
        T data;
        ListNode *next;
        ListNode *prev;
        ListNode();
        ~ListNode();
        ListNode(T d);
};

template <class T>
ListNode<T>::ListNode()
{
    /*
    The constructor initializes pointers as NULL
    */
    next = NULL;
    prev = NULL;
    cout << "Error: ListNode created without data" << endl;
}

template <class T>
ListNode<T>::ListNode(T d)
{
    /*
    Overloaded constructor sets pointers to NULL and data to the input
    */
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode()
{
    /*
    Destructor simply sets all pointers to NULL
    */
    next = NULL;
    prev = NULL;
}

#endif