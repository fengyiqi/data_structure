#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include <iostream>
#include "illegal.h"

template<typename T>
class linearList
{
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int index) const = 0;
    virtual int indexOf(const T& theElement) const = 0; // return the index of the fist show up
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(std::ostream& out) const = 0;
};

// can not change the arrayList length since std::copy receive array address
template<typename T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if(newLength < 0)
        throw illegalParameterValue("new length must be >= 0");

    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a+number, temp);
    delete[] a;
    a = temp;  
}

#endif