#pragma once

#include <cmath>

namespace utilities
{

    const double PI = 3.1415926;
    const double GOLDEN_RATIO = (1.0 + std::sqrt(5.0)) / 2.0;

    double sin(double value);
    void swap(int& x, int& y);
} // namespace utilities