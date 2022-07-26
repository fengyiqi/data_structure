#include "array_list.h"

void arrayListTest()
{
    std::cout << " ---- arrayList test ---- \n";
    arrayList<int> y(10);
    for (int i = 0; i < 20; i++)
        y.insert(i, i);
    y.erase(10);
    std::cout << y << std::endl;
    std::reverse(y.begin(), y.end());
    std::cout << y << std::endl;
    std::cout << std::accumulate(y.begin(), y.end(), 0) << std::endl;
}