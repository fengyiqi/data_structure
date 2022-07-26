#include <iostream>
#include "sparse_matrix.h"

void testSparseMatrix()
{
    std::cout << " ---- sparse Matrix ---- \n";
    
    sparseMatrix<int> a, b, c;

    // test input and output
    std::cin >> a;
    std::cout << "Matrix a is" << std::endl << a;
    std::cout << "--------------" << std::endl;
    std::cin >> b;
    std::cout << "Matrix b is" << std::endl << b;
    std::cout << "--------------" << std::endl;
    // test transpose
    a.transpose(c);
    std::cout << "The transpose of a is" << std::endl << c;
    std::cout << "--------------" << std::endl;
//     // test add
    a.add(b, c);
    std::cout << "The sum of a and b is" << std::endl << c;
}