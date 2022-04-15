#ifndef CHAIN_NODE_H
#define CHAIN_NODE_H

#include "linear_list.h"

template<class T>
struct chainNode
{
    T element;
    chainNode<T>* next;

    chainNode() {}
    chainNode(const T& element) {this->element = element;}
    chainNode(const T& element, chainNode<T>* next) {this->element = element; this->next = next;}
};

template<class T>
class chain : public linearList<T> {
protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode;
    int listSize;
public:
    chain(int initialCapacity = 10);
    chain(const chain<T>& theList);
    ~chain();

    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;
};

#endif