#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

template <class T>
class binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

public:
    binaryTreeNode() { leftChild = rightChild = nullptr; }
    binaryTreeNode(const T &theElement) : element(theElement) { leftChild = rightChild = nullptr; }
    binaryTreeNode(const T &theElement, binaryTreeNode<T> *theLeftChild, binaryTreeNode<T> *theRightChild) : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

#endif