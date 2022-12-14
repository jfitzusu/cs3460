#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>

using std::initializer_list;
using std::int32_t;

class Matrix
{
  public:
    Matrix();                                                 // Default, and delegating
    Matrix(std::size_t cols, std::size_t rows);               // Overloaded
    Matrix(initializer_list<initializer_list<int32_t>> list); // std::initializer_list
    Matrix(const Matrix& matrix);                             // Copy
    Matrix(Matrix&& matrix);                                  // Move
    ~Matrix();

    Matrix& operator=(const Matrix& rhs);                  // Regular assignment operator
    Matrix& operator=(Matrix&& rhs);                       // Move assignment
    int32_t& operator()(std::size_t row, std::size_t col); // Array-like access, but using () operator

    std::size_t getColumns() const { return m_cols; }
    std::size_t getRows() const { return m_rows; }

  private:
    std::size_t m_rows; // std::size_t because std::initializer_list uses it for the size.
    std::size_t m_cols;
    //std::shared_ptr<int32_t*[]> m_data; // we'll manage the memory ourselves
    int32_t** m_data;

    void buildMemory(std::size_t rows, std::size_t cols);
};
