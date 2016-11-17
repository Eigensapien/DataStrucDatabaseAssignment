#ifndef _ROLLBACKSTACK_H_
#define _ROLLBACKSTACK_H_

#include <iostream>
#include "rollbacknode.h"

/***************************************************************************************
 * class RollbackStack                                                                 *
 *                                                                                     *
 * A stack designed for rollback purposes. Works as a template for data type T.        *
 * The stack has normal stack functions push(), pop(), and peek(), however the         *
 * stack automatically deletes the bottom element when it exceeds a maximum size.      *
 * This maximum size defaults to 5 but can be changed with the overloaded constructor  *
 * or with the resize() function. This keeps memory from getting clogged.              *
 ***************************************************************************************/
template <class T>
class RollbackStack
{
    public:
        RollbackStack();
        RollbackStack(int max);
        ~RollbackStack();
        T peek();
        T pop();
        void push(T d);
        void resize(int newSize);
        bool isEmpty();
    
    private:
        RollbackNode<T> *bottom;
        RollbackNode<T> *top;
        int maxSize;
        int size;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                default constructor                               default constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
RollbackStack<T>::RollbackStack()
{
    bottom = NULL;
    top = NULL;
    size = 0;
    maxSize = 5;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                overloaded constructor                         overloaded constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
RollbackStack<T>::RollbackStack(int max)
{
    bottom = NULL;
    top = NULL;
    size = 0;
    if (max>0)
    {
        maxSize = max;
    }
    else
    {
        std::cout << "Error: Stack cannot have maxSize<1" << std::endl;
        maxSize = 5;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                destructor                                                 destructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
RollbackStack<T>::~RollbackStack()
{
    while ( !isEmpty() )
    {
        pop();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                peek()                                                         peek()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
T RollbackStack<T>::peek()
{
    //check for empty stack
    if ( isEmpty() )
    {
        std::cout << "Error: Rollback stack is empty. Cannot peek." << std::endl;
        //this should never happen since isEmpty() is checked before each peek(),
        //but a little error message may help with debugging if it comes up.
    }
    else
    {
        return (top->data);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                pop()                                                           pop()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
T RollbackStack<T>::pop()
{
    //check for empty stack
    if ( isEmpty() )
    {
        std::cout << "Error: Rollback stack is empty. Cannot pop." << std::endl;
        //this should never happen since isEmpty() is checked before each pop(),
        //but a little error message may help with debugging if it comes up.
    }
    
    T data = top->data;
    
    //check cases for deleting top
    if (size==1) //top is bottom
    {
        delete top;
        top = NULL;
        bottom = NULL;
    }
    else
    {
        RollbackNode<T> *oldTop = top;
        top = oldTop->below;
        top->above = NULL;
        delete oldTop;
        oldTop = NULL;
    }
    
    size--;
    return data;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                push(T data)                                             push(T data)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
void RollbackStack<T>::push(T data)
{
    //need to check cases
    //case 1: stack is empty
    //case 2: stack is full
    //case 3: stack is neither
    
    RollbackNode<T> *node = new RollbackNode<T>(data);
    
    if (isEmpty())
    {
        //place the new node is as both top and bottom
        top = node;
        bottom = node;
        size++;
    }
    else if (size==maxSize)
    {
        //place new node at the top
        node->below = top;
        top->above = node;
        top = node;
        
        //delete the bottom to keep size from exceeding max
        bottom = bottom->above;
        delete bottom->below;
        bottom->below = NULL;
    }
    else
    {
        //place new node at the top
        node->below = top;
        top->above = node;
        top = node;
        size++;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                resize                                                         resize
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//This function simply changes the maxSize variable

template <class T>
void RollbackStack<T>::resize(int newSize)
{
    if (newSize<size)
    {
        std::cout << "Error: cannot make stack smaller than current size" << std::endl;
        return;
    }
    else
    {
        maxSize = newSize;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                isEmpty                                                       isEmpty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Simply tells you if size is 0

template <class T>
bool RollbackStack<T>::isEmpty()
{
    return size==0;
}








#endif