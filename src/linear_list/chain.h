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
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;

    class iterator
    {
        protected:
            chainNode<T>* node;
        public:
            iterator(chainNode<T>* theNode = nullptr) : node(theNode) {}

            T& operator*() const {return node->element;}
            T* operator->() const {return &(node->element);}
            iterator& operator++() {node = node->next; return *this; }
            iterator operator++(int) {iterator old = *this; node = node->next; return old;}

            bool operator!=(const iterator right) const {return node != right.node;}
            bool operator==(const iterator right) const {return node == right.node;}
    };
    
    iterator begin() {return iterator(firstNode);}
    iterator end() {return iterator(nullptr);}
};

void chainTest();

template<typename T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x) {
    x.output(out);
    return out;
}

#endif
