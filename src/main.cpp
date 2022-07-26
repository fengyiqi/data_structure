#include "linear_list/array_list.h"
#include "linear_list/vector_list.h"
#include "linear_list/chain.h"
#include "linear_list/extended_chain.h"
#include "matrix/matrix.h"
#include "matrix/sparse_matrix.h"

int main() {
    arrayListTest();
    // vectorListTest();
    chainTest();
    // extendedChainTest();
    // matrixTest();
    testSparseMatrix();
    return 0;
}