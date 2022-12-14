#include <fmt/format.h>
#include <iostream>
#include <vector>

int getNextPrime(int value)
{
    if (value < 2)
    {
        return 2;
    }
    else if (value < 3)
    {
        return 3;
    }
    else if (value < 5)
    {
        return 5;
    }
    else if (value < 7)
    {
        return 7;
    }

    return 11;
}

int* generatePrimes(int howMany)
{
    int* primes = new int[howMany];

    int currentPrime = getNextPrime(0);
    for (int i = 0; i < howMany; i++)
    {
        primes[i] = currentPrime;
        currentPrime = getNextPrime(currentPrime);
    }

    return primes;
}

int* generate4Primes()
{
    int primes[4];

    int currentPrime = getNextPrime(0);
    for (int i = 0; i < 4; i++)
    {
        primes[i] = currentPrime;
        currentPrime = getNextPrime(currentPrime);
    }

    return primes;
}

std::vector<int> generatePrimesForVector(int howMany)
{
    std::vector<int> primes;

    int currentPrime = getNextPrime(0);
    for (int i = 0; i < 4; i++)
    {
        primes.push_back(currentPrime);
        currentPrime = getNextPrime(currentPrime);
    }

    return primes;
}

void demoDynamicMemory()
{
    // auto primes = generatePrimes(4);
    auto primes = generate4Primes();
    auto primesGood = generatePrimes(4);
    auto primesVector = generatePrimesForVector(4);

    for (int i = 0; i < 4; i++)
    {
        // std::cout << primes[i] << std::endl;
        std::cout << primesVector[i] << std::endl;
    }

    delete[] primesGood;
}

void demoArrayPointers()
{
    int primes[] = {2, 3, 5, 7};
    int* primes2 = new int[]{11, 13, 17, 23};

    std::cout << (primes + 0) << " : " << *(primes + 0) << " : " << primes[0] << std::endl;
    std::cout << (primes + 1) << " : " << *(primes + 1) << " : " << primes[1] << std::endl;
    std::cout << (primes + 2) << " : " << *(primes + 2) << " : " << primes[2] << std::endl;
    std::cout << (primes + 3) << " : " << *(primes + 3) << " : " << primes[3] << std::endl;

    std::cout << (primes2 + 0) << " : " << *(primes2 + 0) << " : " << primes2[0] << std::endl;
    std::cout << (primes2 + 1) << " : " << *(primes2 + 1) << " : " << primes2[1] << std::endl;
    std::cout << (primes2 + 2) << " : " << *(primes2 + 2) << " : " << primes2[2] << std::endl;
    std::cout << (primes2 + 3) << " : " << *(primes2 + 3) << " : " << primes2[3] << std::endl;

    int** ptrPrimes2 = &primes2;
    *ptrPrimes2 = new int[]{29, 31, 37, 43};

    std::cout << (primes2 + 0) << " : " << *(primes2 + 0) << " : " << primes2[0] << std::endl;
    std::cout << (primes2 + 1) << " : " << *(primes2 + 1) << " : " << primes2[1] << std::endl;
    std::cout << (primes2 + 2) << " : " << *(primes2 + 2) << " : " << primes2[2] << std::endl;
    std::cout << (primes2 + 3) << " : " << *(primes2 + 3) << " : " << primes2[3] << std::endl;
}

void swap(int* x, int* y)
{
    int temp = *y;
    *y = *x;
    *x = temp;
}

int main()
{
    // int a = 10;
    // int* ptrA = &a;

    // std::cout << *ptrA << " : " << ptrA << std::endl;
    //*ptrA = 20;
    // std::cout << *ptrA << " : " << a << std::endl;

    // demoArrayPointers();

    int a = 10;
    int b = 20;
    swap(&a, &b);

    std::cout << a << ", " << b << std::endl;

    return 0;
}