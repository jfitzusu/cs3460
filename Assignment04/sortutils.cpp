#include "sortutils.hpp"

#include <algorithm>
#include <chrono>
#include <execution>
#include <fmt/format.h>
#include <iostream>

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[])
{
    for (std::uint32_t i = 0; i < source.size(); i++)
    {
        dest[i] = source[i];
    }
}

void organPipeStdArray(SourceArray& data)
{
    std::int32_t start = 0;
    std::int32_t end = static_cast<std::int32_t>(data.size()) - 1;
    for (start; start < static_cast<std::int32_t>(data.size() / 2); start++, end--)
    {
        data[end] = data[start];
    }
}

void evaluateOneRawArraySeq(const SourceArray& array, std::string name, std::int8_t maxLength)
{
    std::chrono::nanoseconds accumulatedTime(0);
    for (std::uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        int copyArray[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(array, copyArray);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, std::begin(copyArray), std::end(copyArray));
        auto end = std::chrono::high_resolution_clock::now();
        accumulatedTime += (end - start);
    }
    std::cout << "        " << fmt::format("{:<{}} : {} ms", name + " time", maxLength, std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedTime).count()) << std::endl;
}

void evaluateOneRawArrayPar(const SourceArray& array, std::string name, std::int8_t maxLength)
{
    std::chrono::nanoseconds accumulatedTime(0);
    for (std::uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        int copyArray[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(array, copyArray);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, std::begin(copyArray), std::end(copyArray));
        auto end = std::chrono::high_resolution_clock::now();
        accumulatedTime += (end - start);
    }
    std::cout << "        " << fmt::format("{:<{}} : {} ms", name + " Time", maxLength, std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedTime).count()) << std::endl;
}

void evaluateOneStdArraySeq(const SourceArray& array, std::string name, std::int8_t maxLength)
{
    std::chrono::nanoseconds accumulatedTime(0);
    for (std::uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        auto copyArray = array;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, copyArray.begin(), copyArray.end());
        auto end = std::chrono::high_resolution_clock::now();
        accumulatedTime += (end - start);
    }
    std::cout << "        " << fmt::format("{:<{}} : {} ms", name + " Time", maxLength, std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedTime).count()) << std::endl;
}

void evaluateOneStdArrayPar(const SourceArray& array, std::string name, std::int8_t maxLength)
{
    std::chrono::nanoseconds accumulatedTime(0);
    for (std::uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        auto copyArray = array;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, copyArray.begin(), copyArray.end());
        auto end = std::chrono::high_resolution_clock::now();
        accumulatedTime += (end - start);
    }
    std::cout << "        " << fmt::format("{:<{}} : {} ms", name + " Time", maxLength, std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedTime).count()) << std::endl;
}

void evaluateOneStdVectorSeq(const SourceArray& array, std::string name, std::int8_t maxLength)
{
    std::chrono::nanoseconds accumulatedTime(0);
    for (std::uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector copyArray(array.begin(), array.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, copyArray.begin(), copyArray.end());
        auto end = std::chrono::high_resolution_clock::now();
        accumulatedTime += (end - start);
    }
    std::cout << "        " << fmt::format("{:<{}} : {} ms", name + " Time", maxLength, std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedTime).count()) << std::endl;
}

void evaluateOneStdVectorPar(const SourceArray& array, std::string name, std::int8_t maxLength)
{
    std::chrono::nanoseconds accumulatedTime(0);
    for (std::uint32_t i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector copyArray(array.begin(), array.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, copyArray.begin(), copyArray.end());
        auto end = std::chrono::high_resolution_clock::now();
        accumulatedTime += (end - start);
    }
    std::cout << "        " << fmt::format("{:<{}} : {} ms", name + " Time", maxLength, std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedTime).count()) << std::endl;
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    std::int8_t maxLength = 15;
    std::cout << " --- Raw Array Performance ---" << std::endl
              << std::endl;
    std::cout << "Sequential" << std::endl;
    evaluateOneRawArraySeq(random, "Random", maxLength);
    evaluateOneRawArraySeq(sorted, "Sorted", maxLength);
    evaluateOneRawArraySeq(reversed, "Reversed", maxLength);
    evaluateOneRawArraySeq(organPipe, "Organ Pipe", maxLength);
    evaluateOneRawArraySeq(rotated, "Rotated", maxLength);
    std::cout << "Parallel" << std::endl;
    evaluateOneRawArrayPar(random, "Random", maxLength);
    evaluateOneRawArrayPar(sorted, "Sorted", maxLength);
    evaluateOneRawArrayPar(reversed, "Reversed", maxLength);
    evaluateOneRawArrayPar(organPipe, "Organ Pipe", maxLength);
    evaluateOneRawArrayPar(rotated, "Rotated", maxLength);
    std::cout << std::endl;
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    std::int8_t maxLength = 15;
    std::cout << " --- std::array Performance ---" << std::endl
              << std::endl;
    std::cout << "Sequential" << std::endl;
    evaluateOneStdArraySeq(random, "Random", maxLength);
    evaluateOneStdArraySeq(sorted, "Sorted", maxLength);
    evaluateOneStdArraySeq(reversed, "Reversed", maxLength);
    evaluateOneStdArraySeq(organPipe, "Organ Pipe", maxLength);
    evaluateOneStdArraySeq(rotated, "Rotated", maxLength);
    std::cout << "Parallel" << std::endl;
    evaluateOneStdArrayPar(random, "Random", maxLength);
    evaluateOneStdArrayPar(sorted, "Sorted", maxLength);
    evaluateOneStdArrayPar(reversed, "Reversed", maxLength);
    evaluateOneStdArrayPar(organPipe, "Organ Pipe", maxLength);
    evaluateOneStdArrayPar(rotated, "Rotated", maxLength);
    std::cout << std::endl;
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    std::int8_t maxLength = 15;
    std::cout << " --- std::vector Performance ---" << std::endl
              << std::endl;
    std::cout << "Sequential" << std::endl;
    evaluateOneStdVectorSeq(random, "Random", maxLength);
    evaluateOneStdVectorSeq(sorted, "Sorted", maxLength);
    evaluateOneStdVectorSeq(reversed, "Reversed", maxLength);
    evaluateOneStdVectorSeq(organPipe, "Organ Pipe", maxLength);
    evaluateOneStdVectorSeq(rotated, "Rotated", maxLength);
    std::cout << "Parallel" << std::endl;
    evaluateOneStdVectorPar(random, "Random", maxLength);
    evaluateOneStdVectorPar(sorted, "Sorted", maxLength);
    evaluateOneStdVectorPar(reversed, "Reversed", maxLength);
    evaluateOneStdVectorPar(organPipe, "Organ Pipe", maxLength);
    evaluateOneStdVectorPar(rotated, "Rotated", maxLength);
    std::cout << std::endl;
}