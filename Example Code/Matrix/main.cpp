#include "Matrix.hpp"

#include <iostream>
#include <string>

Matrix makeMatrix(std::size_t cols, std::size_t rows);
void reportMatrix(std::string name, Matrix& m);

//
// Demonstration almost all constructor types, only inheriting of constructors is not demonstrated
//
int main(int argc, char* argv[])
{
    Matrix m1;            // Default constructor
    Matrix m2(4, 4);      // Overloaded constructor
    Matrix m3({{0, 1, 2}, // Initializer list constructor
               {3, 4, 5},
               {6, 7, 8}});
    Matrix m4 = m3;               // Copy constructor invoked
    Matrix m5 = makeMatrix(3, 2); // Move constructor invoked

    reportMatrix("m3", m3);
    reportMatrix("m4", m4);
    reportMatrix("m5", m5);

    m5 = Matrix(2, 3); // Move assignment invoked

    reportMatrix("m5 v2", m5);

    m5 = m1; // Assignment operator invoked

    return 0;
}

// ------------------------------------------------------------------
//
// Demonstrate move constructor
//
// ------------------------------------------------------------------
Matrix makeMatrix(std::size_t rows, std::size_t cols)
{
    std::cout << "--- makeMatrix ---" << std::endl;
    Matrix m(rows, cols);

    int32_t value = 0;
    for (std::size_t row = 0; row < rows; row++)
    {
        for (std::size_t col = 0; col < cols; col++)
        {
            m(row, col) = value;
            value++;
        }
    }

    return m; // Move constructor invoked
}

void reportMatrix(std::string name, Matrix& m)
{
    std::cout << "--- " << name << " ---" << std::endl;
    for (std::size_t row = 0; row < m.getRows(); row++)
    {
        for (std::size_t col = 0; col < m.getColumns(); col++)
        {
            std::cout << m(row, col) << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
