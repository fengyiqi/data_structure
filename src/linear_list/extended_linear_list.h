#ifndef EXTENDED_LINEAR_LIST_H
#define EXTENDED_LINEAR_LIST_H

#include "linear_list.h"

template<class T>
class extendedLinearList : linearList<T> {
public:
    virtual ~extendedLinearList() {}
    virtual void clear() = 0;
    virtual void push_back(const T& theElement) = 0;
};

#endif