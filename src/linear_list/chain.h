#ifndef CHAIN_H
#define CHAIN_H

#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "chain_node.h"

template <class T>
class chain : public linearList<T>
{
protected:
    void checkIndex(int theIndex) const;
    chainNode<T> *firstNode;
    int listSize;

public:
    chain(int initialCapacity = 10);
    chain(const chain<T> &theList);
    ~chain();

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const;

    class iterator
    {
    protected:
        chainNode<T> *node;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        iterator(chainNode<T> *theNode = nullptr) : node(theNode) {}

        T &operator*() const { return node->element; }
        T *operator->() const { return &(node->element); }
        iterator &operator++() {
            node = node->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            node = node->next;
            return old;
        }

        bool operator!=(const iterator right) const { return node != right.node; }
        bool operator==(const iterator right) const { return node == right.node; }
    };

    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(nullptr); }
};

void chainTest();

template <typename T>
std::ostream &operator<<(std::ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}

// definition

template<class T>
chain<T>::chain(int initialCapacity) {
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
    if (theIndex < 0 || theIndex >= listSize){
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
    return currentNode->element;
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
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
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
        chainNode<T>* p = firstNode;
        for(int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template<class T>
void chain<T>::output(std::ostream& out) const{
    for(const chainNode<T>* currenNode = firstNode; currenNode != nullptr; currenNode = currenNode->next)
        out << currenNode->element << ", ";
}

#endif
