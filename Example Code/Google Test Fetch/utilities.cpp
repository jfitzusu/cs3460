
#include "utilities.hpp"

namespace utilities
{

    double sin(double angle)
    {
        return (4 * angle * (180 - angle)) / (40500 - angle * (180 - angle));
    }
    void swap(int& x, int& y)
    {
        int temp = x;
        x = y;
        y = temp;
    }

} // namespace utilities