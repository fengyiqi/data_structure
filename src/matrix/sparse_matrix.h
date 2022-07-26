#ifndef SPAREMATRIX_H
#define SPAREMATRIX_H

#include <iostream>
#include "linear_list/array_list.h"

void testSparseMatrix();

template <class T>
struct matrixTerm
{
    int row, col;
    T value;

    operator T() const { return value; }
    // type conversion from matrixTerm to T
};

template <class T>
class sparseMatrix
{
    int rows, cols;
    arrayList<matrixTerm<T>> terms;
    template <class S>
    friend std::ostream &operator<<(std::ostream &, sparseMatrix<S> &);
    template <class S>
    friend std::istream &operator>>(std::istream &, sparseMatrix<S> &);

public:
    void transpose(sparseMatrix<T> &b);
    void add(sparseMatrix<T> &b, sparseMatrix<T> &c);
};

template <class T>
std::ostream &operator<<(std::ostream &out, sparseMatrix<T> &x)
{
    out << "rows = " << x.rows << " columns = " << x.cols << std::endl;
    out << "nonzero terms = " << x.terms.size() << std::endl;
    for (auto i = x.terms.begin(); i != x.terms.end(); i++)
    {
        out << "a(" << (*i).row << ", " << (*i).col << ") = " << (*i).value << std::endl;
    }
    return out;
}

template <class T>
std::istream &operator>>(std::istream &in, sparseMatrix<T> &x)
{ // Input a sparse matrix.

    // input matrix characteristics
    int numberOfTerms;
    std::cout << "Enter number of rows, columns, and number of terms" << std::endl;
    in >> x.rows >> x.cols >> numberOfTerms;

    // set size of x.terms and ensure enough capacity
    x.terms.reSet(numberOfTerms);

    // input terms
    matrixTerm<T> mTerm;
    for (int i = 0; i < numberOfTerms; i++)
    {
        std::cout << "Enter row, column, and value of term " << (i + 1) << std::endl;
        in >> mTerm.row >> mTerm.col >> mTerm.value;
        x.terms.set(i, mTerm);
    }

    return in;
}

template <class T>
void sparseMatrix<T>::transpose(sparseMatrix<T> &b)
{
    b.cols = rows;
    b.rows = cols;
    b.terms.reSet(terms.size());

    int *colSize = new int[cols + 1];
    int *rowNext = new int[cols + 1];

    for (int i = 1; i <= cols; i++)
        colSize[i] = 0;
    for (auto i = terms.begin(); i != terms.end(); i++)
        colSize[(*i).col]++;

    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    matrixTerm<T> mTerm;
    for (auto i = terms.begin(); i != terms.end(); i++)
    {
        int j = rowNext[(*i).col]++;
        mTerm.row = (*i).col;
        mTerm.col = (*i).row;
        mTerm.value = (*i).value;
        b.terms.set(j, mTerm);
    }
}

template <class T>
void sparseMatrix<T>::add(sparseMatrix<T> &b, sparseMatrix<T> &c)
{
    if (rows != b.rows || cols != b.cols)
        throw matrixSizeMismatch();

    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    int cSize = 0;

    auto it = terms.begin();
    auto ib = b.terms.begin();
    auto itEnd = terms.end();
    auto ibEnd = b.terms.end();

    while (it != itEnd && ib != ibEnd)
    {
        int tIndex = (*it).row * cols + (*it).col;
        int bIndex = (*ib).row * cols + (*ib).col;

        if (tIndex < bIndex)
        {
            c.terms.insert(cSize++, *it);
            it++;
        }
        else if (tIndex == bIndex)
        {
            if ((*it).value + (*ib).value != 0)
            {
                matrixTerm<T> mTerm;
                mTerm.row = (*it).row;
                mTerm.col = (*it).col;
                mTerm.value = (*it).value + (*ib).value;
                c.terms.insert(cSize++, mTerm);
            }
            it++;
            ib++;
        }
        else
        {
            c.terms.insert(cSize++, *ib);
            ib++;
        }
    }
    // remaining code may be unnecessary
    // for (; it != itEnd; it++){
    //     std::cout << "In it remaining\n";
    //     c.terms.insert(cSize++, *it);
    // }
    // for (; ib != ibEnd; ib++){
    //     std::cout << "In ib remaining\n";
    //     c.terms.insert(cSize++, *ib);
    // }
}

#endif