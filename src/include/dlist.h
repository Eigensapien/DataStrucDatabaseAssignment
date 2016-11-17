#ifndef _DLIST_H_
#define _DLIST_H_

#include <iostream>
#include "listnode.h"

using std::cout;
using std::endl;

//--------------------------------------------------------------------
//            THE LIST
//--------------------------------------------------------------------
template <class T>
class DList
{
    /*
    This class is a template class for a doubly linked list
    */
    public:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;
    
        DList();
        ~DList();
    
        void insertFront(T d);
        void insertBack(T d);
        void insertAfter(T key, T d);

        T removeFront();
        T removeBack();
        T deletePos(int pos);
    
        T peekPos(int pos);
    
        void printList();
        int find(T val);
        unsigned int getSize();
        ListNode<T> *remove(T key);
        bool isEmpty();
};

template <class T>
DList<T>::DList()
{
    /*
    Constructor simply sets pointers to NULL and size to 0
    */
    size = 0;
    front = NULL;
    back = NULL;
}

template <class T>
DList<T>::~DList()
{
    /*
    Destructor starts at the front,
    then moves to the next node
    then deletes the node it just left behind
    once it gets to the last node, that node is deleted
    all pointers are set to NULL
    */
    if ( !isEmpty() ) //if the list isn't empty already
    {
        //loop until we get to the last node
        while (front->next != NULL)
        {
            //if prev is there, delete it
            if (front->prev != NULL)
            {
                delete front->prev;
                front->prev = NULL;
            }
            front = front->next;
        }
        //now we need to delete the last node
        delete front;
        front = NULL;
        back = NULL;
    }
}

template <class T>
void DList<T>::insertFront(T d)
{
    /*
    This function inserts some input data to the front of the list
    */
    ListNode<T> *node = new ListNode<T>(d);
    if (size == 0)
    {    //if empty, new node is the back
        back = node;
    }
    else
    {    //if other nodes exist, link them to the new node
        front->prev = node;
        node->next = front;
    }
    //the new node is the front
    front = node;
    ++size;
}

template <class T>
void DList<T>::insertBack(T d)
{
    /*
    This function inserts some input data to the back of the list
    */
    ListNode<T> *node = new ListNode<T>(d);
    node->data = d;
    if (size == 0)
    {    //if empty, new node is the front
        front = node;
    }
    else
    {    //if other nodes exist, link them to the new node
        back->next = node;
        node->prev = back;
    }
    //the new node is the front
    back = node;
    ++size;
}

template <class T>
void DList<T>::insertAfter(T key, T d)
{
    /*
    This function searches the list for data matching the key
    then inserts a new node with input data after the node that was found
    */
    ListNode<T> *current = front;
    while(current->data != key)
    {
        current = current->next;
        if(current==NULL)
        {
            cout << "Error: insertAfter key not found in list" << endl;
            return;
        }
    }
    //found it
    if(current==front)
    {
        insertFront(d);
        return;
    }
    else if(current==back)
    {
        insertBack(d);
        return;
    }
    else //it is somewhere in the middle
    {
        ListNode<T> *node = new ListNode<T>(d);
        current->next->prev = node;
        current->next = node;
        ++size;
        return;
    }
}

template <class T>
T DList<T>::removeFront()
{
    /*
    This function removes the front element of the list
    */
    if(isEmpty())//list is empty
    {
        cout << "Error: cannot remove from empty list" << endl;
        T temp;
        return temp;
    }
    ListNode<T> *oldFront = front;
    if(front==back) //if the front is the back
    {
        back = NULL;
    }
    else
    {
        front->next->prev = NULL;
    }
    front = front->next;
    T temp = oldFront->data;
    delete oldFront;
    size--;
    return temp;
}

template <class T>
T DList<T>::removeBack()
{
    /*
    This function remove the back element of the list
    */
    if(isEmpty())//list is empty
    {
        cout << "Error: cannot remove from empty list" << endl;
        T temp;
        return temp;
    }
    ListNode<T> *oldBack = back;
    if(front==back) //if the front is the back
    {
        front = NULL;
    }
    else
    {
        back->prev->next = NULL;
    }
    back = back->prev;
    T temp = oldBack->data;
    delete oldBack;
    size--;
    return temp;
}

template <class T>
T DList<T>::deletePos(int pos)
{
    /*
    This function moves to position pos in the list then deletes the node at that position
    */
    ListNode<T> *curr = front;
    //loop through the nodes until we get to pos
    for (int i=0; i<pos; ++i)
    {
        if(curr->next==NULL)
        {
            cout << "Error: deletePos index exceeds size of list. Return last element." << endl;
            return curr->data;
        }
        else
        {
            curr = curr->next;
        }
    }
    if(curr==front)
    {
        return removeFront();
    }
    else if(curr==back)
    {
        return removeBack();
    }
    else
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        T temp = curr->data;
        delete curr;
        size--;
        return temp;
    }
}


template <class T>
T DList<T>::peekPos(int pos)
{
    /*
    This function gets the data from a position in the list by jumping pointers starting from the front
    */
    ListNode<T> *curr = front;
    //loop through the nodes until we get to pos
    for (int i=0; i<pos; ++i)
    {
        if(curr->next==NULL)
        {
            cout << "Error: peekPos index exceeds size of list. Return last element." << endl;
            return curr->data;
        }
        else
        {
            curr = curr->next;
        }
    }
    return curr->data;
}



template <class T>
void DList<T>::printList()
{
    /*
    This function simply prints the contents of the list
    */
    ListNode<T> *curr = front;
    while (curr != NULL)
    {
        cout << curr->data << endl;
        curr = curr->next;
    }
}

template <class T>
int DList<T>::find(T val)
{
    /*
    This function searches through the list for some value
    and returns its position in the list
    */
    int pos = 0;
    ListNode<T> *curr = front;
    while(curr->data != val)
    {
        pos++;
        curr = curr->next;
        if(curr==NULL)
        {
            return -1;
        }
    }
    return pos;
}

template <class T>
unsigned int DList<T>::getSize()
{
    /*
    A simple getter function for the size
    */
    return size;
}

template <class T>
ListNode<T>* DList<T>::remove(T key)
{
    /*
    This function removes the first element in the list with data matching the key,
    removes it from the list, and returns a pointer to the node
    Returns NULL if nothing matches
    */
    ListNode<T> *current = front;
    while(current->data != key)
    {
        current = current->next;
        if(current==NULL)
        {
            return NULL;
        }
    }
    //found it
    if(current == front)
    {
        front = current->next;
    }
    else
    {
        current->prev->next = current->next;
    }
    
    if(current==back)
    {
        back = current->next;
    }
    else
    {
        current->next->prev = current->prev;
    }
    current->next = NULL;
    current->prev = NULL;
    size--;
    return current;
}

template <class T>
bool DList<T>::isEmpty()
{
    return (front == NULL);
}

#endif