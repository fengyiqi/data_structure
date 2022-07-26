#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <sstream>
#include "stack.h"
#include "illegal.h"
#include "linear_list/linear_list.h"

template<class T>
class arrayStack : public stack<T> {
private:
    int stackTop;
    int arrayLength;
    T* stack;
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() { delete[] stack; }

    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T& top() {
        if (empty())
            throw stackEmpty();
        return stack[stackTop];
    }
    void pop() {
        if (empty())
            throw stackEmpty();
        stack[stackTop--].~T();
    }
    void push(const T& theElement);
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << ". Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T& theElement) {
    if (stackTop == arrayLength - 1){
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement;
}


#endif