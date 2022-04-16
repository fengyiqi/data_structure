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

#endif