#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "illegal.h"

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

template<class T>
matrix<T>::matrix(int theRows, int theColumns) {
    if(theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if((theRows < 0 || theColumns < 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];
}

template<class T>
matrix<T>::matrix(const matrix<T>& m) {
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T[theRows * theColumns];
    std::copy(m.element, m.element + theRows * theColumns, element);
}

template<class T>
T& matrix<T>::operator()(int i, int j) const {
    if (i < 1 || i > theRows || j < 1 || j > theColumns)
        throw matrixIndexOutOfBounds();
    return element[(i - 1) * theColumns + j - 1];
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m) {
    if (this != &m) {
        delete[] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T[theRows * theColumns];
        std::copy(m.element, m.element + theRows * theColumns, element);
    }
    return *this;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const {
    if (theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMismatch();
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] + m.element[i];
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{// Return (*this) - m.
   if (theRows != m.theRows 
       || theColumns != m.theColumns)
      throw matrixSizeMismatch();

   // create result matrix w
   matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = element[i] - m.element[i];

   return w;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const {
    if (theColumns != m.theRows)
        throw matrixSizeMismatch();
    matrix<T> w(theRows, m.theColumns);

    int ct = 0, cm = 0, cw = 0;
    for(int i = 1; i <= theRows; i++) {
        for (int j = 1; j <= m.theColumns; j++) {
            T sum = element[ct] * m.element[cm];
            for (int k = 2; k <=  theColumns; k++) {
                ct++;
                cm += m.theColumns;
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum;

            ct -= theColumns - 1;
            cm = j;
        }
        ct += theColumns;
        cm = 0;
    }
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-() const
{// Return w = -(*this).

   // create result matrix w
   matrix<T> w(theRows, theColumns);
   for (int i = 0; i < theRows * theColumns; i++)
      w.element[i] = -element[i];
   return w;

}

template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{// Increment all elements of *this by x.
   for (int i = 0; i < theRows * theColumns; i++)
       element[i] += x;
   return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& m)
{// Put matrix m into the stream out.
 // One row per line.
   int k = 0;  // index into element array
   for (int i = 0; i < m.theRows; i++)
   {// do row i
      for (int j = 0; j < m.theColumns; j++)
         out << m.element[k++] << "  ";

      // row i finished
      out << std::endl;
   }

   return out;
}

#endif