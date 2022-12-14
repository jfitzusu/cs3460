#include "stack.hpp"
#include "utilities.hpp"

#include <array>
#include <iostream>
#include <vector>

int main()
{

    // std::cout << "2^4 = " << xtoy(2, 4u) << std::endl;
    // std::cout << "2.2^4 = " << xtoy(2.2, 4u) << std::endl;
    // std::cout << "2^4.2 = " << xtoy(2, 4.2) << std::endl;

    // std::vector<int> primes1 = {1, 2, 3, 5};
    // report(primes1);

    // std::array<int, 4> primes2 = {1, 2, 3, 5};
    // report(primes2);

    //// int primes3[4] = {1, 2, 3, 5};
    //// report(primes3);

    // repeat<std::string, 4>("Hi Mom!");
    // repeat<double, 6>(3.14159);

    // stack<std::string> stack1(10);
    // stack<bool> stack2(20);

    // stack1.push("Paradise");
    // stack1.push("Hyrum");
    // stack1.push("Logan");
    // stack1.push("Hyde Park");
    // stack1.push("Smithfield");

    // while (!stack1.isEmpty())
    //{
    //     std::cout << stack1.pop() << std::endl;
    // }

    using namespace std::string_literals;

    std::cout << usu::max(4, 10) << std::endl;
    std::cout << usu::max("Hi Mom!"s, "Hi Dad!"s) << std::endl;

    std::cout << usu::max(6, 2, 4) << std::endl;

    std::cout << usu::max(6, 10, 4, 2) << std::endl;

    std::cout << usu::max(6, 10.2, 4.8, 6u) << std::endl;

    std::cout << "How many types: " << usu::howManyTypes(1, 2.0, "3", true, false) << std::endl;
    std::cout << "How many types: " << usu::howManyTypes() << std::endl;

    return 0;
}
