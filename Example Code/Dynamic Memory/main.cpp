#include <array>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <vector>

class Rectangle
{
  public:
    Rectangle(double width, double height) :
        m_width(width),
        m_height(height)
    {
    }
    double getArea() { return m_width * m_height; }
    double getPerimeter() { return m_width * 2 + m_height * 2; }
    double getWidth() { return m_width; }
    double getHeight() { return m_height; }

  private:
    double m_width;
    double m_height;
};

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

void demoSharedPtr()
{
    std::shared_ptr<int> a = std::make_shared<int>(1);
    std::shared_ptr<double> b = std::make_shared<double>(3.14159);

    std::cout << "The value stored in a is " << *a << std::endl;
    std::cout << "The value stored in b is " << *b << std::endl;

    std::shared_ptr<std::array<int, 4>> dontDoThis = std::make_shared<std::array<int, 4>>();

    (*dontDoThis)[0] = 1;
}

std::uint64_t arraySum(const std::shared_ptr<const int[]>& data, std::uint8_t length)
{
    std::uint64_t total = 0;
    for (std::uint8_t i = 0; i < length; i++)
    {
        total += data[i];
    }

    return total;
}

std::uint64_t arraySum(int* data, std::uint8_t length)
{
    std::uint64_t total = 0;
    for (std::uint8_t i = 0; i < length; i++)
    {
        total += data[i];
    }

    return total;
}

void demoPreventCopyPenalty()
{
    std::shared_ptr<int[]> primes = std::make_shared<int[]>(4);
    primes[0] = 1;
    primes[1] = 2;
    primes[2] = 3;
    primes[3] = 4;

    std::cout << "sum is: " << arraySum(primes, 4) << std::endl;
    std::cout << "sum is: " << arraySum(primes.get(), 4) << std::endl;
}

std::unique_ptr<int[]> reportPrimes(std::unique_ptr<int[]> data, std::uint8_t length)
{
    std::cout << "--- Report ---\n";
    for (decltype(length) i = 0; i < length; i++)
    {
        std::cout << data[i] << std::endl;
    }
    std::cout << std::endl;

    return std::move(data);
}

void demoUniquePointer()
{
    std::unique_ptr<int[]> primes = std::make_unique<int[]>(4);
    primes[0] = 1;
    primes[1] = 2;
    primes[2] = 3;
    primes[3] = 5;

    primes = reportPrimes(std::move(primes), 4);

    std::cout << primes[0] << std::endl;
}

int main()
{
    // int a = 10;
    // int* ptrA = &a;

    // std::cout << *ptrA << " : " << ptrA << std::endl;
    //*ptrA = 20;
    // std::cout << *ptrA << " : " << a << std::endl;

    // demoArrayPointers();

    /*int a = 10;
    int b = 20;
    swap(&a, &b);

    std::cout << a << ", " << b << std::endl;*/

    // demoSharedPtr();

    // demoPreventCopyPenalty();

    // demoUniquePointer();

    Rectangle r1(10, 12);

    std::cout << "width  : " << r1.getWidth() << std::endl;
    std::cout << "height : " << r1.getHeight() << std::endl;

    Rectangle* r2 = new Rectangle(14, 16);
    std::cout << "width  : " << r2->getWidth() << std::endl;
    std::cout << "height : " << r2->getHeight() << std::endl;
    delete r2;

    //std::cout << "width  :" << (*r2).getWidth() << std::endl;

    std::shared_ptr<Rectangle> r3 = std::make_shared<Rectangle>(18, 20);
    std::cout << "width  : " << r3->getWidth() << std::endl;
    std::cout << "height : " << r3->getHeight() << std::endl;

    return 0;
}