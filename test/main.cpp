#include <array>
#include <iostream>

int main() {

    std::array<int, 5> array = {1, 2, 3, 4, 5};
    for (const auto& value : array){
        std::cout << value << std::endl;
    }
    return 0;
}