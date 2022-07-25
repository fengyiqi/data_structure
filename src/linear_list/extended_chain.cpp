#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "extended_chain.h"

template <class T>
void extendedChain<T>::erase(int theIndex)
{ // Delete the element whose index is theIndex.
  // Throw illegalIndex exception if no such element.
    chain<T>::checkIndex(theIndex);

    // valid index, locate node with element to delete
    chainNode<T> *deleteNode;
    if (theIndex == 0)
    { // remove first node from chain
        deleteNode = chain<T>::firstNode;
        chain<T>::firstNode = chain<T>::firstNode->next;
    }
    else
    { // use p to get to predecessor of desired node
        chainNode<T> *p = chain<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next; // remove deleteNode from chain
        if (deleteNode == lastNode)
            lastNode = p;
    }
    chain<T>::listSize--;
    delete deleteNode;
}

template <class T>
void extendedChain<T>::insert(int theIndex, const T &theElement)
{ // Insert theElement so that its index is theIndex.
    if (theIndex < 0 || theIndex > chain<T>::listSize)
    { // invalid index
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << chain<T>::listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
    { // insert at front
        chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
        if (chain<T>::listSize == 0)
            lastNode = chain<T>::firstNode;
    }
    else
    { // find predecessor of new element
        chainNode<T> *p = chain<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        // insert after p
        p->next = new chainNode<T>(theElement, p->next);
        if (chain<T>::listSize == theIndex)
            lastNode = p->next;
    }
    chain<T>::listSize++;
}

template <class T>
void extendedChain<T>::clear()
{
    while (chain<T>::firstNode != NULL)
    { // delete firstNode
        chainNode<T> *nextNode = chain<T>::firstNode->next;
        delete chain<T>::firstNode;
        chain<T>::firstNode = nextNode;
    }
    chain<T>::listSize = 0;
}

template <class T>
void extendedChain<T>::push_back(const T &theElement)
{ // Insert theElement at the end of the chain.
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);
    if (chain<T>::firstNode == NULL)
        // chain is empty
        chain<T>::firstNode = lastNode = newNode;
    else
    { // attach next to lastNode
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chain<T>::listSize++;
}

void extendedChainTest()
{
    std::cout << " ---- extendedChain test ---- \n";
    extendedChain<int> chain;
    for (int i = 0; i < 20; i++)
        chain.insert(i, i);
    chain.erase(10);
    std::cout << chain << std::endl;
    std::cout << std::accumulate(chain.begin(), chain.end(), 0) << std::endl;
}