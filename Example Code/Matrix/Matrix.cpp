#include "Matrix.hpp"

#include <cstring>
#include <iostream>

Matrix::Matrix() :
    Matrix(2, 2) // Delegating to an overloaded constructor
{
}

Matrix::Matrix(std::size_t rows, std::size_t cols)
{
    // TODO: Should validate rows and cols are both non-zero

    buildMemory(rows, cols);
}

Matrix::Matrix(initializer_list<initializer_list<int32_t>> list) :
    Matrix(list.size(), list.begin()->size()) // Delegating to an overloaded constructor
{
    // TODO: should verify the data is rectangular, but that is
    // an exercise for later.

    std::size_t r = 0; // Can only declare one type in a for loop, unfortunately
    for (auto row = list.begin(); row != list.end(); row++, r++)
    {
        std::size_t c = 0; // Same comment as above
        for (auto column = row->begin(); column != row->end(); column++, c++)
        {
            m_data[r][c] = *column;
        }
    }
}

// ------------------------------------------------------------------
//
// Copy constructor, we are making a full copy of everything.
//
// ------------------------------------------------------------------
Matrix::Matrix(const Matrix& matrix)
{
    buildMemory(matrix.m_rows, matrix.m_cols);

    for (std::size_t row = 0; row < m_rows; row++)
    {
        std::memcpy(m_data[row], matrix.m_data[row], sizeof(int32_t) * m_cols);
    }

    std::cout << "copy constructor" << std::endl;
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
    buildMemory(rhs.m_rows, rhs.m_cols);

    for (std::size_t row = 0; row < m_rows; row++)
    {
        std::memcpy(m_data[row], rhs.m_data[row], sizeof(int32_t) * m_cols);
    }

    std::cout << "assignment operator" << std::endl;

    return *this;
}

// ------------------------------------------------------------------
//
// Move constructor...stealing from the source.  Some say to do the
// same thing as move assignment.
//
// ------------------------------------------------------------------
Matrix::Matrix(Matrix&& matrix)
{
    std::cout << "move constructor" << std::endl;
    m_rows = matrix.m_rows;
    m_cols = matrix.m_cols;
    m_data = matrix.m_data;

    matrix.m_rows = 0;
    matrix.m_cols = 0;
    matrix.m_data = nullptr;
}

Matrix::~Matrix()
{
    if (m_data != nullptr)
    {
        for (decltype(m_rows) row = 0; row < m_rows; row++)
        {
            delete[] m_data[row];
        }
        delete[] m_data;
        m_data = nullptr;
    }
}

// ------------------------------------------------------------------
//
// Move assignment operator, swap values.
//
// ------------------------------------------------------------------
Matrix& Matrix::operator=(Matrix&& rhs)
{
    std::cout << "move assignment" << std::endl;
    if (this != &rhs)
    {
        std::swap(m_rows, rhs.m_rows);
        std::swap(m_cols, rhs.m_cols);
        std::swap(m_data, rhs.m_data);
    }

    return *this;
}

// ------------------------------------------------------------------
//
// Array-like access to the data using the () operator
//
// ------------------------------------------------------------------
int32_t& Matrix::operator()(std::size_t row, std::size_t col)
{
    return m_data[row][col];
}

// ------------------------------------------------------------------
//
// We are doing our own memory management, as a means to show how to
// go about implementing the various constructor types and usages.
//
// ------------------------------------------------------------------
void Matrix::buildMemory(std::size_t rows, std::size_t cols)
{
    m_rows = rows;
    m_cols = cols;
    int32_t** data = new int32_t*[rows];
    for (decltype(rows) row = 0; row < rows; row++)
    {
        data[row] = new int32_t[cols];
        std::memset(data[row], 0, sizeof(int32_t) * cols);
    }
    //m_data = std::shared_ptr<int32_t*[]>(data, [rows](int32_t** data) {
    //    for (decltype(rows) row = 0; row < rows; row++)
    //    {
    //        delete[] data[row];
    //    }
    //    delete[] data;
    //});

    m_data = data;
}
