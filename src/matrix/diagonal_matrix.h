#ifndef DIAGONAL_MATRIX_H
#define DIAGONAL_MATRIX_H

#include "illegal.h"

template<class T>
class diagonalMatrix {
private:
    int n;
    T* element;
public:
    diagonalMatrix(int theN = 10);
    ~diagonalMatrix() {delete[] element;}
    T get(int, int) const;
    void set(int, int, const T&);
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN) {
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n];
}

template<class T>
T diagonalMatrix<T>::get(int i, int j) const {
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i == j)
        return element[i - 1];
    else
        return 0;
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& newValue) {
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i == j)
        element[i - 1] = newValue;
    else {
        //TODO can we only check i != j? because other elements should be 0
        if (newValue != 0)
            throw illegalParameterValue("Nondiagonal elements must be zero.");
    }
}

#endif