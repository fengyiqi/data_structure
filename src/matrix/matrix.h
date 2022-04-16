#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

// prior declaration to make function declaration possible
template<class T>
class matrix;

template<typename T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& m);

// the index of the matrix starts from 1
template<class T>
class matrix {
    // specify function type
    friend std::ostream& operator<<<T>(std::ostream& out, const matrix& m);
private:
    int theRows, theColumns;
    T* element;
public:
    matrix(int theRows = 0, int theColumns = 0);
    matrix(const matrix<T>&);
    ~matrix() {delete[] element;}

    int rows() {return theRows;}
    int columns() {return theColumns;}
    T& operator()(int i, int j) const;
    matrix<T>& operator=(const matrix<T>&);
    matrix<T> operator+() const;
    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-() const;
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const matrix<T>&) const;
    matrix<T>& operator+=(const T&);
};

void matrixTest();

#endif