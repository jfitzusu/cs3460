#pragma once

// -- Inline Template Style --
template <typename T>
class MyClass
{
  public:
    MyClass(T data) :
        m_data(data)
    {
    }

    T getData() { return m_data; }

  private:
    T m_data;
};
