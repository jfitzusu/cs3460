#include "vector.hpp"

usu::vector<bool>::reference::reference(std::uint8_t* byte, std::uint8_t bit)
{
    if (bit > 7)
    {
        throw std::range_error("Bit Not Within Byte");
    }
    m_location = byte;
    m_bit = bit;
}

void usu::vector<bool>::reference::operator=(const bool& toSet)
{
    if (toSet)
    {
        *m_location |= 1 << m_bit;
    }
    else
    {
        *m_location &= ~(1 << m_bit);
    }
}

usu::vector<bool>::reference::operator bool()
{
    return bool(*m_location >> m_bit & std::uint8_t(1));
}

bool usu::vector<bool>::reference::operator*()
{
    return bool(*m_location >> m_bit & std::uint8_t(1));
}

usu::vector<bool>::iterator::iterator() :
    iterator(nullptr)
{
}

usu::vector<bool>::iterator::iterator(pointer pointer) :
    iterator(0, pointer){};

usu::vector<bool>::iterator::iterator(size_type position, pointer pointer) :
    m_position(position),
    m_pointer(pointer){};

usu::vector<bool>::iterator::iterator(const iterator& oldIter)
{
    this->m_position = oldIter.m_position;
    this->m_pointer = oldIter.m_pointer;
}

usu::vector<bool>::iterator::iterator(iterator&& oldIter) noexcept
{
    this->m_position = oldIter.m_position;
    this->m_pointer = oldIter.m_pointer;
    oldIter.m_position = 0;
    oldIter.m_pointer = nullptr;
}

usu::vector<bool>::iterator usu::vector<bool>::iterator::operator++()
{
    m_position++;
    return *this;
}

usu::vector<bool>::iterator usu::vector<bool>::iterator::operator++(int)
{
    iterator i = *this;
    m_position++;
    return i;
}

usu::vector<bool>::iterator usu::vector<bool>::iterator::operator--()
{
    m_position--;
    return *this;
}

usu::vector<bool>::iterator usu::vector<bool>::iterator::operator--(int)
{
    iterator i = *this;
    m_position--;
    return i;
}

usu::vector<bool>::iterator& usu::vector<bool>::iterator::operator=(const iterator& oldIter)
{
    this->m_position = oldIter.m_position;
    this->m_pointer = oldIter.m_pointer;

    return *this;
}

usu::vector<bool>::iterator& usu::vector<bool>::iterator::operator=(iterator&& oldIter)
{
    if (this != &oldIter)
    {
        std::swap(this->m_position, oldIter.m_position);
        std::swap(this->m_pointer, oldIter.m_pointer);
    }

    return *this;
}

usu::vector<bool>::reference usu::vector<bool>::iterator::operator*()
{
    return reference(&m_pointer[m_position / 8], m_position % 8);
}

bool usu::vector<bool>::iterator::operator==(const iterator& iter)
{
    return m_position == iter.m_position;
}

bool usu::vector<bool>::iterator::operator!=(const iterator& iter)
{
    return m_position != iter.m_position;
}

usu::vector<bool>::vector() :
    vector(M_DEFAULT_RESIZER)
{
}

usu::vector<bool>::vector(size_type size) :
    vector(size, M_DEFAULT_RESIZER)
{
}

usu::vector<bool>::vector(resize_type resize) :
    vector(0, resize){};

usu::vector<bool>::vector(size_type size, resize_type resize) :
    m_size(size),
    m_capacity(M_DEFAULT_CAPACITY),
    m_rawArray(nullptr),
    m_resizer(resize)
{
    if (M_DEFAULT_CAPACITY < size)
    {
        m_capacity = size * 2;
    }
    m_rawArray = std::make_shared<std::uint8_t[]>((m_capacity - 1) / 8 + 1);
};

usu::vector<bool>::vector(std::initializer_list<bool> list) :
    vector(list, M_DEFAULT_RESIZER)
{
}

usu::vector<bool>::vector(std::initializer_list<bool> list, resize_type resize) :
    m_size(0),
    m_capacity(M_DEFAULT_CAPACITY),
    m_rawArray(nullptr),
    m_resizer(resize)
{
    m_rawArray = std::make_shared<std::uint8_t[]>((m_capacity - 1) / 8 + 1);
    int current = 0;
    for (auto i = list.begin(); i != list.end(); i++, current++)
    {
        add(*i);
    }
};

usu::vector<bool>::reference usu::vector<bool>::operator[](size_type index)
{
    if (index >= m_size)
    {
        throw std::range_error("Index Out of Bounds");
    }
    return reference(&m_rawArray[index / 8], index % 8);
}

void usu::vector<bool>::add(bool value)
{
    if (m_size >= m_capacity)
    {
        m_capacity = m_resizer(m_capacity);
        pointer newArray = std::make_shared<std::uint8_t[]>((m_capacity - 1) / 8 + 1);
        for (unsigned int i = 0; i < m_size / 8 + 1; i++)
        {
            newArray[i] = m_rawArray[i];
        }
        m_rawArray = newArray;
    }

    usu::vector<bool>::reference(&m_rawArray[m_size / 8], m_size % 8) = value;
    m_size++;
}

void usu::vector<bool>::insert(size_type index, bool value)
{
    if (index > m_size)
    {
        throw std::range_error("Index Out of Bounds");
    }

    if (m_size + 1 >= m_capacity)
    {
        m_capacity = m_resizer(m_capacity);
        pointer newArray = std::make_shared<std::uint8_t[]>((m_capacity - 1) / 8 + 1);
        for (unsigned int i = 0; i < m_size / 8 + 1; i++)
        {
            newArray[i] = m_rawArray[i];
        }
        m_rawArray = newArray;
    }

    m_size++;
    bool toShift = *reference(&m_rawArray[index / 8], index % 8);
    for (size_type i = index + 1; i < (m_size); i++)
    {
        bool nextShift = *reference(&m_rawArray[i / 8], i % 8);
        reference(&m_rawArray[i / 8], i % 8) = toShift;
        toShift = nextShift;
    }

    reference(&m_rawArray[index / 8], index % 8) = value;
}

void usu::vector<bool>::remove(size_type index)
{
    {
        if (index >= m_size)
        {
            throw std::range_error("Index Out of Bounds");
        }

        // If this works I STG
        size_type tempMax = size_type(m_size);
        m_size = index;
        for (size_type i = index + 1; i < tempMax; i++)
        {
            add(reference(&m_rawArray[i / 8], i % 8));
        }
    };
}

usu::vector<bool>::size_type usu::vector<bool>::size()
{
    return m_size;
}
usu::vector<bool>::size_type usu::vector<bool>::capacity()
{
    return m_capacity;
}

void usu::vector<bool>::clear()
{
    m_size = 0;
}

usu::vector<bool>::iterator usu::vector<bool>::begin()
{
    return iterator(m_rawArray);
}

usu::vector<bool>::iterator usu::vector<bool>::end()
{
    return iterator(m_size, m_rawArray);
}
