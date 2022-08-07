#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <class T>
class binaryTree
{
public:
    virtual ~binaryTree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*)(T *)) = 0; // void(*) (T*)是一种函数类型，返回值是void, 它的参数类型是T*
    virtual void postOrder(void (*)(T *)) = 0;
    virtual void inOrder(void (*)(T *)) = 0;
    virtual void levelOrder(void (*)(T *)) = 0;
};

#endif