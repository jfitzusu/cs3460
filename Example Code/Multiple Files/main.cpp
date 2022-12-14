#include <iostream>

#include "utilities.hpp"

//
// Demonstration of using separate declaration (header) and implementation files
//
int main(int argc, char* argv[])
{

    std::cout << "Pi estimate: " << PI << std::endl;
    std::cout << "Golden ratio estimate: " << GOLDEN_RATIO << std::endl;

    for (int angle = 0; angle <= 180; angle++)
    {
        std::cout << "sin(" << angle << ") = " << sin(angle) << std::endl;
    }

    return 0;
}
