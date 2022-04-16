#include <sstream>
#include <algorithm>
#include <numeric>
#include "vector_list.h"

template<typename T>
vectorList<T>::vectorList(int initialCapacity){
    if (initialCapacity < 1){
        std::ostringstream ss;
        ss << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    element = new std::vector<T>;
    element->reserve(initialCapacity);
}

template<typename T>
vectorList<T>::vectorList(const vectorList<T>& theList) {
    element = new std::vector<T>(*theList.element);
}

template<typename T>
void vectorList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex > size()){
        std::ostringstream ss;
        ss << "index = " << theIndex << " size = " << element->capacity();
        throw illegalParameterValue(ss.str());
    }
}

template<typename T>
void vectorList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    element->erase(begin() + theIndex);
}

template<typename T>
void vectorList<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > size()){
        std::ostringstream ss;
        ss << "index = " << theIndex << " size = " << size();
        throw illegalIndex(ss.str());
    }
    element->insert(begin() + theIndex, theElement);
}

template<typename T>
T& vectorList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return (*element)[theIndex];
}

template<typename T>
int vectorList<T>::indexOf(const T& theElement) const {
    // std::find returns an iterator. This iterator minus the array pointer, returns the index
    int theIndex = (int) (std::find(element->cbegin(), element->cend(), theElement) - element->cbegin());
    if (theIndex == size())
        return -1;
    else
        return theIndex;
}

void vectorListTest(){
    std::cout << " ---- vectorList test ---- \n";
    vectorList<int> y(10);
    for (int i = 0; i < 20; i++)
        y.insert(i, i);
    y.erase(10);
    std::cout << y << std::endl;
    std::reverse(y.begin(), y.end());
    std::cout << y << std::endl;
    std::cout << std::accumulate(y.begin(), y.end(), 0) << std::endl;
}