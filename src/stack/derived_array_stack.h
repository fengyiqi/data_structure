#ifndef DERIVED_ARRAY_STACK_H
#define DERIVED_ARRAY_STACK_H

#include "linear_list/array_list.h"
#include "stack.h"
#include "illegal.h"

template<class T>
class derivedArrayStack : private arrayList<T>, public stack<T> {
public:
    derivedArrayStack(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}
    bool empty() const { return arrayList<T>::empty(); }
    int size() const { return arrayList<T>::size(); }
    T& top() {
        if (empty())
            throw stackEmpty();
        return get(arrayList<T>::size() - 1);
    }
    void pop() {
        if (empty())
            throw stackEmpty();
        erase(arrayList<T>::size() - 1);
    }
    void push(const T& theElement) { insert(arrayList<T>::size(), theElement); }
};

#endif