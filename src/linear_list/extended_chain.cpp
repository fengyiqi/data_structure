#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "extended_chain.h"

void extendedChainTest() {
    std::cout << " ---- extendedChain test ---- \n";
    extendedChain<int> chain;
    for (int i = 0; i < 20; i++)
        chain.insert(i, i);
    chain.erase(10);
    std::cout << chain << std::endl;
    std::cout << std::accumulate(chain.begin(), chain.end(), 0) << std::endl;
}