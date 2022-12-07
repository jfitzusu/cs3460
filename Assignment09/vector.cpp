#include "vector.hpp"

template <typename T>
usu::vector<T>::iterator::iterator(const iterator& oldIter)
{
    this->m_position = oldIter.m_position;
    this->m_pointer = oldIter.m_pointer;
}
template <typename T>
usu::vector<T>::iterator::iterator(iterator&& oldIter) noexcept
{
    this->m_position = oldIter.m_position;
    this->m_pointer = oldIter.m_pointer;
    oldIter.m_position = 0;
    oldIter.m_pointer = nullptr;
}

template <typename T>
usu::vector<T>::iterator usu::vector<T>::iterator::operator++()
{
    m_position++;
    return *this;
}

template <typename T>
usu::vector<T>::iterator usu::vector<T>::iterator::operator++(int)
{
    iterator i = *this;
    m_position++;
    return i;
}

template <typename T>
usu::vector<T>::iterator usu::vector<T>::iterator::operator--()
{
    m_position--;
    return *this;
}

template <typename T>
usu::vector<T>::iterator usu::vector<T>::iterator::operator--(int)
{
    iterator i = *this;
    m_position--;
    return i;
}

template <typename T>
usu::vector<T>::iterator& usu::vector<T>::iterator::operator=(const usu::vector<T>::iterator& oldIter)
{
    this->m_position = oldIter.m_position;
    this->m_pointer = oldIter.m_pointer;

    return *this;
}

template <typename T>
usu::vector<T>::iterator& usu::vector<T>::iterator::operator=(usu::vector<T>::iterator&& oldIter)
{
    if (this != &oldIter)
    {
        std::swap(this->m_position, oldIter.m_position);
        std::swap(this->m_pointer, oldIter.m_pointer);
    }

    return *this;
}
