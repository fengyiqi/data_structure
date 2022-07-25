#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H

#include <vector>
#include <iterator>
#include <iostream>
#include "linear_list.h"

template<typename T>
class vectorList : public linearList<T> {
public:
    vectorList(int initialCapacity = 10);
    vectorList(const vectorList<T>&);
    ~vectorList() {delete element;}

    bool empty() const {return element->empty();}
    int size() const {return element->size();}
    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;

    int capacity() const {return (int) element->capacity();}

    typedef typename std::vector<T>::iterator iterator;
    iterator begin() {return element->begin();}
    iterator end() {return element->end();}

protected:
    void checkIndex(int theIndex) const;
    std::vector<T>* element;
};

// void vectorListTest();

template<typename T>
std::ostream& operator<<(std::ostream& out, const vectorList<T>& x) {
    x.output(out);
    return out;
}

#endif