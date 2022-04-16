#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

// the index of the matrix starts from 1
template<class T>
class matrix {
    friend std::ostream& operator<<(std::ostream&, const matrix<T>&);
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

#endif