#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iterator>
#include <iostream>
#include "linear_list.h"


template<typename T>
class arrayList : public linearList<T>
{
protected:
    void checkIndex(int theIndex) const;
    T* element;
    int arrayLength;
    int listSize;
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() {delete[] element;}

    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const {
        std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, ", "));
    }

    int capacity() const {return arrayLength;}

    class iterator {
        protected:
            T* position;
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef T* pointer;
            typedef T& reference;

            iterator(T* thePositon = 0) {position = thePositon;}

            T& operator*() const {return *position;}
            T* operator->() const {return &*position;}

            iterator& operator++() {++position; return *this;}
            iterator operator++(int) {iterator old = *this; ++position; return old;}
            iterator& operator--() {--position; return *this;}
            iterator operator--(int) {iterator old = *this; --position; return old;}

            bool operator!=(const iterator right) const {return position != right.position;}
            bool operator==(const iterator right) const {return position == right.position;}
    };
    
    iterator begin() {return iterator(element);}
    iterator end() {return iterator(element + listSize);}
    
};

void arrayListTest();

template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x) {
    x.output(out);
    return out;
}

#endif