#include <fmt/format.h>
#include <format>
#include <iostream>
#include <numbers>
#include <string>

std::string getFormat()
{
    return "{1:{0}}";
}

int main()
{

    std::string name = "Important Person";
    int age = 26;
    std::cout << fmt::format("Hi {}, from fmt::format!\n", name);

    std::cout << fmt::format("My name is '{0}', my age is {1}\n", name, age);

    std::cout << fmt::format("{0}, the value of Pi is {1:6.4f}\n", name, std::numbers::pi_v<float>);

    std::cout << fmt::vformat(getFormat(), fmt::make_format_args(10, std::string("This is a test\n")));

    // ---

    std::cout << std::format("Hi {}, from std::format!\n", name);

    std::cout << std::format("My name is '{0}', my age is {1}\n", name, age);

    std::cout << std::format("{0}, the value of Pi is {1:6.4f}\n", name, std::numbers::pi_v<float>);

    std::cout << std::vformat(getFormat(), std::make_format_args(10, "This is a test\n"));

    return 0;
}
