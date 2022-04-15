#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "array_list.h"

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

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex > listSize){
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
    checkIndex(theIndex);
    if (listSize == arrayLength){
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}

void arrayListTest(){
    std::cout << " ---- arrayList test ---- \n";
    arrayList<int> y(10);
    for (int i = 0; i < 20; i++)
        y.insert(i, i);
    std::cout << y << std::endl;
    std::reverse(y.begin(), y.end());
    std::cout << y << std::endl;
    std::cout << std::accumulate(y.begin(), y.end(), 0) << std::endl;
}