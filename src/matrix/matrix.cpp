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

void matrixTest() {
    // try
    {
        matrix<int> x(3,2), y, z;
        int i, j;
        for (i = 1; i <= 3; i++)
            for (j = 1; j <= 2; j++)
            x(i,j) = 2*i + j;
        std::cout << "Initialized x(i,j) = 2*i + j" << std::endl;
        std::cout << "x(3,1) = " << x(3,1) << std::endl;
        std::cout << "x is" << std::endl;;
        std::cout << x << std::endl;

        y = x;
        std::cout << "Assigned y = x" << std::endl;
        std::cout << "y is" << std::endl;
        std::cout << y << std::endl;

        x += 2;
        std::cout << "x incremented by 2 is" << std::endl;
        std::cout << x << std::endl;

        z = y + x;
        std::cout << "y + x is" << std::endl;
        std::cout << z << std::endl;

        std::cout << "-(y + x) is" << std::endl;
        std::cout << -z << std::endl;

        matrix<int> w(2,3);
        for (i = 1; i <= 2; i++)
            for (j = 1; j <= 3; j++)
            w(i,j) = i + j;
        std::cout << "Initialized w(i,j) = i + j" << std::endl;
        std::cout << "w is" << std::endl;
        std::cout << w << std::endl;

        z = y * w;
        std::cout << "y * w is" << std::endl;
        std::cout << z << std::endl;
    }
    // catch (...) {
    //     std::cerr << "An exception has occurred" << std::endl;
    // }

}