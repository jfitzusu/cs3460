#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

class DistributionPair
{
  public:
    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }

    std::uint32_t minValue;
    std::uint32_t maxValue; // Stores the Max as a Non-Inclusive Integer
    std::uint32_t count;
};

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins);
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins);
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins);
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize);
void test();

int main(){
    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(100000, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);
    test();
}

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
    for (int i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].count > maxBinSize)
        {
            maxBinSize = distribution[i].count;
        }
    }

    float scaleFactor = maxPlotLineSize / static_cast<float>(maxBinSize);

    std::cout << title << std::endl;
    int maxIntSize = 3;

    for (DistributionPair bin : distribution)
    {
        std::cout << "[" << std::setfill(' ') << std::setw(maxIntSize) << std::right << bin.minValue;
        std::cout << "," << std::setw(maxIntSize) << std::right << bin.maxValue << "]"
                  << " :";
        if (bin.count > 0)
        {
            std::cout << std::setfill('*') << std::setw(static_cast<int>(bin.count * scaleFactor) + 1) << std::left << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

// ------------------------------------------------------------------
//
// Testing Code
//
// ------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

namespace testing
{
    using namespace std::string_literals;

    using Bins = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
    using DistFunc = std::function<std::vector<DistributionPair>()>;

#define CS3460_ASSERT_EQ(expected, actual, message)                    \
    if (expected != actual)                                            \
    {                                                                  \
        fail(message, "[ Expected", expected, "but got", actual, "]"); \
        return;                                                        \
    }

#define CS3460_CASE(x) \
    [] {               \
        return x;      \
    };                 \
    std::cout << " Case " << #x << "\n";

    template <typename Message>
    void failInternal(const Message& message)
    {
        std::cout << message << " ";
    }

    template <typename Message, typename... Messages>
    void failInternal(const Message& message, const Messages&... messages)
    {
        failInternal(message);
        failInternal(messages...);
    }

    template <typename... Messages>
    void fail(const Messages&... messages)
    {
        std::cout << "  Assertion failed: ";
        failInternal(messages...);
        std::cout << "\n";
    }

    Bins generateBins(const std::uint32_t min, const std::uint32_t max, const std::uint8_t numberBins)
    {
        const auto binRange = (max - min) / numberBins;
        auto minBin = min;
        auto maxBin = min + binRange;

        Bins results(numberBins);
        for (std::uint8_t bin = 0u; bin < numberBins; bin++)
        {
            results[bin] = { minBin, maxBin };
            minBin = maxBin + 1;
            maxBin = minBin + binRange;
        }

        return results;
    }

    void returnsTheExpectedBins(const DistFunc& func, const Bins& bins)
    {
        const auto result = func();
        CS3460_ASSERT_EQ(bins.size(), result.size(), "Wrong number of bins");
        for (auto i = 0u; i < bins.size(); i++)
        {
            CS3460_ASSERT_EQ(bins[i].first, result[i].minValue, "Wrong minimum value for bin "s + std::to_string(i));
            CS3460_ASSERT_EQ(bins[i].second, result[i].maxValue, "Wrong maximum value for bin "s + std::to_string(i));
        }
    }

    void hasTheCorrectTotalAcrossAllBins(const DistFunc& func, const std::uint32_t howMany)
    {
        const auto result = func();
        const auto add_counts = [](std::uint32_t total, const DistributionPair& bin)
        {
            return total + bin.count;
        };
        CS3460_ASSERT_EQ(howMany, std::accumulate(result.cbegin(), result.cend(), 0u, add_counts),
                         "Wrong number of elements across all bins");
    }

    void testUniformDistribution()
    {
        std::cout << "Testing generateUniformDistribution\n";
        auto func = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 40));
        returnsTheExpectedBins(func, generateBins(0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testNormalDistribution()
    {
        std::cout << "Testing generateNormalDistribution\n";
        auto func = CS3460_CASE(generateNormalDistribution(100000, 50, 5, 40));
        returnsTheExpectedBins(func, generateBins(30, 69, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testPoissonDistribution()
    {
        std::cout << "Testing generatePoissonDistribution\n";
        auto func = CS3460_CASE(generatePoissonDistribution(100000, 6, 40));
        returnsTheExpectedBins(func, generateBins(0, 39, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }
} // namespace testing

void test()
{
    using namespace testing;

    testUniformDistribution();
    testNormalDistribution();
    testPoissonDistribution();

    std::cout << "\n\n";
}