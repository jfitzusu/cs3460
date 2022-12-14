#pragma once

#include <iostream>

namespace usu
{
    // Base case for pack expansion
    template <typename T>
    T max(T x)
    {
        return x;
    }

    // Recursively expands pack
    template <typename T, typename... Ts>
    T max(T x, Ts... ts)
    {
        return (x > max(ts...)) ? x : max(ts...);
    }

    template <typename... Ts>
    unsigned int howManyTypes(Ts... ts)
    {
        return sizeof...(Ts);
    }

} // namespace usu

template <typename T>
T xtoy(T x, unsigned int y)
{
    T result = 1;
    for (decltype(y) i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}

template <typename T>
void report(T data)
{
    std::cout << "There are " << data.size() << " elements in the container" << std::endl;
    for (auto item : data)
    {
        std::cout << " " << item << std::endl;
    }
}

template <typename T, unsigned int R>
void repeat(T value)
{
    for (decltype(R) i = 0; i < R; i++)
    {
        std::cout << value << std::endl;
    }
}
