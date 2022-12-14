#include "array.hpp"

#include <iostream>

int main()
{
    usu::array<int, 6> myData{1, 2, 3, 5, 7, 11};

    std::cout << "-- counted for --\n";
    for (auto i = myData.begin(); i != myData.end(); ++i)
    {
        std::cout << *i << std::endl;
    }

    std::cout << "-- foreach --\n";
    for (auto&& value : myData)
    {
        std::cout << value << std::endl;
    }

    return 0;
}
