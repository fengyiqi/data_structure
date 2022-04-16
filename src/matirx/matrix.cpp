#include "matrix.h"
#include "illegal.h"

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
}