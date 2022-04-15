#ifndef CHAIN_H
#define CHAIN_H

#include "chain_node.h"

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
