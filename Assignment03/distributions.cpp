#include "distributions.hpp"

#include <fmt/format.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    int binSize = (max - min + 1) / numberBins;
    std::vector<DistributionPair> bins;

    for (int i = 0; i < numberBins; i++)
    {
        bins.push_back(DistributionPair(i * binSize + min, (i + 1) * binSize + min - 1));
    }

    double newNumber(0);
    int binNumber(0);
    std::random_device randomDevice;
    std::default_random_engine engine(randomDevice());
    std::uniform_int_distribution<int> distribution(min, max);

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        newNumber = distribution(engine);
        binNumber = static_cast<int>((newNumber - min) / binSize);
        bins[binNumber].count++;
    }

    return bins;
}

std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    int min = 0;
    int max = numberBins - 1;

    int binSize = (max - min + 1) / numberBins;
    std::vector<DistributionPair> bins;

    for (int i = 0; i < numberBins; i++)
    {
        bins.push_back(DistributionPair(i * binSize + min, (i + 1) * binSize + min - 1));
    }

    double newNumber(0);
    int binNumber(0);
    std::random_device randomDevice;
    std::default_random_engine engine(randomDevice());
    std::poisson_distribution<int> distribution(howOften);

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        newNumber = distribution(engine);
        if (newNumber < min)
        {
            binNumber = 0;
        }

        else if (newNumber > max)
        {
            binNumber = numberBins - 1;
        }

        else
        {
            binNumber = static_cast<int>((newNumber - min) / binSize);
        }

        bins[binNumber].count++;
    }

    return bins;
}

std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    int min = static_cast<int>(mean - 4 * stdev);
    int max = static_cast<int>(mean + 4 * stdev);

    int binSize = (max - min + 1) / numberBins;
    std::vector<DistributionPair> bins;

    for (int i = 0; i < numberBins; i++)
    {
        bins.push_back(DistributionPair(i * binSize + min, (i + 1) * binSize + min - 1));
    }

    double newNumber(0);
    int binNumber(0);
    std::random_device randomDevice;
    std::default_random_engine engine(randomDevice());
    std::normal_distribution<double> distribution(mean, stdev);

    for (std::uint32_t i = 0; i < howMany; i++)
    {
        newNumber = distribution(engine);
        if (newNumber < min)
        {
            binNumber = 0;
        }

        else if (newNumber > max)
        {
            binNumber = numberBins - 1;
        }

        else
        {
            binNumber = static_cast<int>((newNumber - min) / binSize);
        }

        bins[binNumber].count++;
    }

    return bins;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    std::uint32_t maxBinSize(0);
    for (std::uint32_t i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].count > maxBinSize)
        {
            maxBinSize = distribution[i].count;
        }
    }

    float scaleFactor = maxPlotLineSize / static_cast<float>(maxBinSize);

    // There are a Lot of Ways I Can Think of To Get This Programatically But Anything Easy Requires Libraries We Haven't Covered
    std::uint8_t largestLength = 3;

    std::cout << title << std::endl;

    for (DistributionPair bin : distribution)
    {
        std::cout << fmt::format("[{:>{}}, {:>{}}] :", bin.minValue, largestLength, bin.maxValue, largestLength);

        if (bin.count > 0)
        {
            std::cout << fmt::format("{:*<{}}", " ", static_cast<int>(bin.count * scaleFactor) + 1);
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}