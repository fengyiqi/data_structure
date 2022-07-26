#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "stack.h"
#include "linear_list/chain_node.h"

template<class T>
class linkedStack : public stack<T> {

private:
    chainNode<T>* stackTop;
    int stackSize;

public:
    linkedStack(int initialCapacity = 10) { stackSize = initialCapacity; stackTop = nullptr; }
    ~linkedStack();  /////////////
    bool empty() { return stack == 0; }
    int size() { return stackSize; }
    T& top() {
        if (stackSize == 0)
            throw stackEmpty();
        return stackTop->element;
    }
    void pop(); ////////////////
    void push(const T& theElement) {
        stackTop = new chainNode<T>(theElement, stackTop);
        stackSize++;
    }

};

template<class T>
linkedStack<T>::~linkedStack() {
    while (stackTop != nullptr)
    {
        chainNode<T>* nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template<class T>
void linkedStack<T>::pop() {
    if (stackSize == 0)
        throw stackEmpty();
    chainNode<T>* nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

#endif