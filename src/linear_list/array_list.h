#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include "illegal.h"
#include "linear_list.h"

// for testing arrayList
void arrayListTest();

template <typename T>
class arrayList : public linearList<T>
{
protected:
    void checkIndex(int theIndex) const; // if invalid, throw an exception
    T *element;
    int arrayLength;
    int listSize;

public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T> &);
    ~arrayList() { delete[] element; }
    
    // --- linear_list pure virtual methods ---
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int index) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const
    {
        std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, ", "));
    }
    // --------- end -------------------------
    // --------- additional function ---------
    void reSet(int);
    void set(int, const T &);
    void clear() { listSize = 0; }
    int capacity() const { return arrayLength; }
    // --------- end -------------------------

    class iterator
    {
    protected:
        T *position;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        iterator(T *thePositon = 0) { position = thePositon; }

        T &operator*() const { return *position; }
        T *operator->() const { return &*position; }

        iterator &operator++()
        {
            ++position;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            ++position;
            return old;
        }
        iterator &operator--()
        {
            --position;
            return *this;
        }
        iterator operator--(int)
        {
            iterator old = *this;
            --position;
            return old;
        }

        bool operator!=(const iterator right) const { return position != right.position; }
        bool operator==(const iterator right) const { return position == right.position; }
    };

    iterator begin() { return iterator(element); }
    iterator end() { return iterator(element + listSize); }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}


template<typename T>
arrayList<T>::arrayList(int initialCapacity){
    if (initialCapacity < 1){
        std::ostringstream ss;
        ss << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    arrayLength = initialCapacity;
    element = new T[initialCapacity];
    listSize = 0;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList){
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

// --------- additional function ---------
template<typename T>
void arrayList<T>::reSet(int newSize) {
    if (newSize < 0) {
        std::ostringstream ss;
        ss << "Requested size = " << newSize << "must be >= 0";
        throw illegalParameterValue(ss.str());
    }
    if (newSize > arrayLength) {
        delete element;
        element = new T[newSize];
        arrayLength = newSize;
    }
    listSize = newSize;
}

template<typename T>
void arrayList<T>::set(int theIndex, const T& newValue) {
    checkIndex(theIndex);
    element[theIndex] = newValue;
}

// --- linear_list pure virtual methods ---
template<typename T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize){ 
        std::ostringstream ss;
        ss << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(ss.str());
    }
}

template<typename T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template<typename T>
int arrayList<T>::indexOf(const T& theElement) const {
    // std::find returns an iterator. This iterator minus the array pointer, returns the index
    int theIndex = (int) (std::find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
        return -1;
    else
        return theIndex;
}

template<typename T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);
    // deconstructe the last element
    element[--listSize].~T();
}

template<typename T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize){ // pay attention to the difference betwenn this ">" and ">=" in checkIndex(int)
        std::ostringstream ss;
        ss << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(ss.str());
    }
    if (listSize == arrayLength){
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}

#endif