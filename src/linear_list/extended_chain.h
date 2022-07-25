#ifndef EXTENDED_CHAIN_H
#define EXTENDED_CHAIN_H

// linked implementation of an extended linear list
// derives from abstract class extendedLinearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for extendedChain included

#include <iostream>
#include <sstream>
#include <string>
#include "extended_linear_list.h"
#include "chain.h"
#include "illegal.h"

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


void extendedChainTest();

#endif