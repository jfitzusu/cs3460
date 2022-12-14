#pragma once

#include <cstdint>
#include <exception>
#include <memory>

template <typename T>
class stack
{
  public:
    stack(std::uint16_t size);

    void push(T value);
    T pop();

    bool isFull() { return m_top == m_size; }
    bool isEmpty() { return m_top == 0; }

  private:
    std::uint16_t m_size;
    std::uint16_t m_top;
    std::unique_ptr<T[]> m_data;
};

template <typename T>
stack<T>::stack(std::uint16_t size) :
    m_size(size),
    m_top(0)
{
    m_data = std::make_unique<T[]>(size);
}

template <typename T>
void stack<T>::push(T value)
{
    if (isFull())
    {
        throw new std::exception("Stack is full");
    }

    m_data[m_top++] = value;
}

template <typename T>
T stack<T>::pop()
{
    if (isEmpty())
    {
        throw new std::exception("Stack is empty");
    }

    return m_data[--m_top];
}
