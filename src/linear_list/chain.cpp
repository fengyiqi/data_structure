#include <algorithm>
#include "chain.h"

void chainTest() {
    std::cout << " ---- chain test ---- \n";
    chain<int> chain;
    for (int i = 0; i < 20; i++)
        chain.insert(i, i);
    chain.erase(10);
    std::cout << chain << std::endl;
    std::cout << std::accumulate(chain.begin(), chain.end(), 0) << std::endl;
}