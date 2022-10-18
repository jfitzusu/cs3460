#include "sortutils.hpp"

#include <algorithm>
#include <random>

const std::int32_t MIN = -10000000;
const std::int32_t MAX = 10000000;

int main()
{

    std::random_device randomDevice;
    std::default_random_engine engine(randomDevice());
    std::uniform_int_distribution<int> distribution(MIN, MAX);

    SourceArray original;
    for (std::uint32_t i = 0; i < original.size(); i++)
    {
        original[i] = distribution(engine);
    }

    SourceArray sorted = original;
    std::sort(sorted.begin(), sorted.end());

    SourceArray reversed = sorted;
    std::reverse(reversed.begin(), reversed.end());

    SourceArray organPipe = sorted;
    organPipeStdArray(organPipe);

    SourceArray rotated = sorted;
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());

    evaluateRawArray(original, sorted, reversed, organPipe, rotated);
    evaluateStdArray(original, sorted, reversed, organPipe, rotated);
    evaluateStdVector(original, sorted, reversed, organPipe, rotated);
}