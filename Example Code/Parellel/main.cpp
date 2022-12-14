#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric> // std::accumulate is in there for some reason
#include <vector>

auto generateData()
{
    std::vector<int> data(100'000'000);

    for (auto i = data.size(); i > 0; i--)
    {
        data[i - 1] = static_cast<int>(i);
    }

    return data;
}

int main()
{

    std::cout << "generating..." << std::endl;
    auto sequential1 = generateData();
    auto sequential2 = generateData();
    auto sequential3 = generateData();
    auto parallel1 = generateData();
    auto parallel2 = generateData();

    std::cout << "sorting..." << std::endl;

    auto start = std::chrono::steady_clock::now();
    std::sort(sequential1.begin(), sequential1.end());
    auto end = std::chrono::steady_clock::now();
    std::cout << "sequential 1: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    std::sort(std::execution::seq, sequential2.begin(), sequential2.end());
    end = std::chrono::steady_clock::now();
    std::cout << "sequential 2: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    std::sort(std::execution::unseq, sequential3.begin(), sequential3.end());
    end = std::chrono::steady_clock::now();
    std::cout << "sequential 3: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    std::sort(std::execution::par, parallel1.begin(), parallel1.end());
    end = std::chrono::steady_clock::now();
    std::cout << "parallel 1  : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    std::sort(std::execution::par_unseq, parallel2.begin(), parallel2.end());
    end = std::chrono::steady_clock::now();
    std::cout << "parallel 2  : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    std::cout << std::endl;

    //
    // std::accumulate summation
    start = std::chrono::steady_clock::now();
    auto sumSequential1 = std::accumulate(sequential1.begin(), sequential1.end(), 0);
    auto sumSequential2 = std::accumulate(sequential2.begin(), sequential2.end(), 0);
    auto sumSequential3 = std::accumulate(sequential3.begin(), sequential3.end(), 0);
    auto sumParallel1 = std::accumulate(parallel1.begin(), parallel1.end(), 0);
    auto sumParallel2 = std::accumulate(parallel2.begin(), parallel2.end(), 0);
    end = std::chrono::steady_clock::now();
    std::cout << "summation   : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    std::cout << sumSequential1 << "\n"
              << sumSequential2 << "\n"
              << sumSequential3 << "\n"
              << sumParallel1 << "\n"
              << sumParallel2 << "\n";
    std::cout << std::endl;

    //
    // std::reduce summation
    start = std::chrono::steady_clock::now();
    auto sumSequential4 = std::reduce(std::execution::par_unseq, sequential1.begin(), sequential1.end());
    auto sumSequential5 = std::reduce(std::execution::par_unseq, sequential2.begin(), sequential2.end());
    auto sumSequential6 = std::reduce(std::execution::par_unseq, sequential3.begin(), sequential3.end());
    auto sumParallel3 = std::reduce(std::execution::par_unseq, parallel1.begin(), parallel1.end());
    auto sumParallel4 = std::reduce(std::execution::par_unseq, parallel2.begin(), parallel2.end());
    end = std::chrono::steady_clock::now();
    std::cout << "summation   : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    std::cout << sumSequential4 << "\n"
              << sumSequential5 << "\n"
              << sumSequential6 << "\n"
              << sumParallel3 << "\n"
              << sumParallel4 << "\n";

    return 0;
}
