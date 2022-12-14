#pragma once

// -- Separate Declaration & Definition Template Style --
template <typename T>
class MyOtherClass
{
  public:
    MyOtherClass(T data);

    T getData();

  private:
    T m_data;
};

template <typename T>
MyOtherClass<T>::MyOtherClass(T data) :
    m_data(data)
{
}

template <typename T>
T MyOtherClass<T>::getData()
{
    return m_data;
}
