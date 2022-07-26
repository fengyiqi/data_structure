#ifndef EXTENDED_CHAIN_H
#define EXTENDED_CHAIN_H

// linked implementation of an extended linear list
// derives from abstract class extendedLinearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for extendedChain included

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "extended_linear_list.h"
#include "chain.h"
#include "illegal.h"

void extendedChainTest();

template <class T>
class extendedChain : public extendedLinearList<T>, public chain<T>
{
public:
   // constructor and copy constructor
   extendedChain(int initialCapacity = 10) : chain<T>(initialCapacity) {}
   extendedChain(const extendedChain<T> &c) : chain<T>(c) {}

   // ADT methods
   bool empty() const { return chain<T>::listSize == 0; }
   int size() const { return chain<T>::listSize; }
   T &get(int theIndex) const {
      return chain<T>::get(theIndex);
   }
   int indexOf(const T &theElement) const {
      return chain<T>::indexOf(theElement);
   }
   void erase(int theIndex);
   void insert(int theIndex, const T &theElement);
   void output(std::ostream &out) const {
      chain<T>::output(out);
   }

   // additional method
   void zero() {
      chain<T>::firstNode = NULL;
      chain<T>::listSize = 0;
   }
   // new methods
   void clear();
   void push_back(const T &theElement);
protected:
   chainNode<T> *lastNode; // pointer to last node in chain
};




template <class T>
void extendedChain<T>::erase(int theIndex)
{ // Delete the element whose index is theIndex.
  // Throw illegalIndex exception if no such element.
    chain<T>::checkIndex(theIndex);

    // valid index, locate node with element to delete
    chainNode<T> *deleteNode;
    if (theIndex == 0)
    { // remove first node from chain
        deleteNode = chain<T>::firstNode;
        chain<T>::firstNode = chain<T>::firstNode->next;
    }
    else
    { // use p to get to predecessor of desired node
        chainNode<T> *p = chain<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next; // remove deleteNode from chain
        if (deleteNode == lastNode)
            lastNode = p;
    }
    chain<T>::listSize--;
    delete deleteNode;
}

template <class T>
void extendedChain<T>::insert(int theIndex, const T &theElement)
{ // Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > chain<T>::listSize)
    { // invalid index
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << chain<T>::listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
    { // insert at front
        chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
        if (chain<T>::listSize == 0)
            lastNode = chain<T>::firstNode;
    }
    else
    { // find predecessor of new element
        chainNode<T> *p = chain<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        // insert after p
        p->next = new chainNode<T>(theElement, p->next);
        if (chain<T>::listSize == theIndex)
            lastNode = p->next;
    }
    chain<T>::listSize++;
}

template <class T>
void extendedChain<T>::clear()
{
    while (chain<T>::firstNode != NULL)
    { // delete firstNode
        chainNode<T> *nextNode = chain<T>::firstNode->next;
        delete chain<T>::firstNode;
        chain<T>::firstNode = nextNode;
    }
    chain<T>::listSize = 0;
}

template <class T>
void extendedChain<T>::push_back(const T &theElement)
{ // Insert theElement at the end of the chain.
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);
    if (chain<T>::firstNode == NULL)
        // chain is empty
        chain<T>::firstNode = lastNode = newNode;
    else
    { // attach next to lastNode
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chain<T>::listSize++;
}


#endif