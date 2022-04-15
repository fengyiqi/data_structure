#include <sstream>
#include "chain.h"

template<class T>
chain<T>::chain(int initialCapacity = 10) {
    if (initialCapacity < 1){
        std::ostringstream ss;
        ss << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList) {
    listSize = theList.listSize;
    if (listSize == 0){
        firstNode = nullptr;
        return;
    }
    chainNode<T> sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);

    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;
    while (sourceNode != nullptr)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        sourceNode = sourceNode->next;
        targetNode = targetNode->next;
    }
    targetNode->next = nullptr;
}

template<class T>
chain<T>::~chain() {
    while (firstNode != nullptr)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void chain<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex > listSize){
        std::ostringstream ss;
        ss << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(ss.str());
    }
}

template<class T>
T& chain<T>::get(int theIndex) const {
    checkIndex(theIndex);
    chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const {
    chainNode<T>* currenNode = firstNode;
    int index = 0;
    while (currenNode != nullptr && currenNode->element != theElement){
        currenNode = currenNode->next;
        index++;
    }
    if (currenNode == nullptr)
        return -1;
    else
        return index;    
}

template<class T>
void chain<T>::erase(int theIndex) {
    checkIndex(theIndex);
    chainNode<T>* deleteNode;
    if (theIndex == 0){
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else{
        chainNode<T>* lastNode = get(theIndex - 1);
        deleteNode = get(theIndex);
        lastNode->next = deleteNode->next;
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize){
        std::ostringstream ss;
        ss << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(ss.str());
    }
    if (theIndex == 0)
        firstNode = new chainNode<T>(theElement, firstNode);
    else {
        chainNode<T>* lastNode = get(theIndex - 1);
        lastNode = new chainNode<T>(theElement, lastNode->next);
    }
    listSize++;
}

template<class T>
void chain<T>::output(std::ostream& out) const{
    for(const chainNode<T>* currenNode = firstNode; currenNode != nullptr; currenNode = currenNode->next)
        out << currenNode->element << ", ";
}