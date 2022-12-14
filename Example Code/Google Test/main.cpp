
#include "utilities.hpp"

#include <cmath>
#include <iostream>

int main()
{
    std::cout << "The value of PI is: " << utilities::PI << std::endl;
    std::cout << "The golden ratio is: " << utilities::GOLDEN_RATIO << std::endl;

    for (int angle = 0; angle <= 180; angle++)
    {
        double mySin = utilities::sin(angle);
        double stdSin = std::sin(angle * (utilities::PI / 180.0));

        std::cout << "sin(" << angle << "): " << mySin << " : " << stdSin << std::endl;
    }
}
