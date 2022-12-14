#pragma once

#include <exception>
#include <initializer_list>
#include <iterator>

namespace usu
{
    template <typename T, unsigned int N>
    class array
    {
      public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = T*;
        using reference = T&;

        class iterator
        {
          public:
            using iterator_category = std::forward_iterator_tag;

            iterator() :
                iterator(nullptr) // DefaultConstructable
            {
            }
            iterator(pointer ptr) :
                m_data(ptr),
                m_pos(0)
            {
            }
            iterator(size_type pos, pointer ptr) :
                m_pos(pos),
                m_data(ptr)
            {
            }

            iterator(const iterator& obj);     // CopyConstructable
            iterator(iterator&& obj) noexcept; // MoveConstructable

            iterator operator++();    // incrementable e.g., ++r
            iterator operator++(int); // incrementable e.g., r++

            iterator& operator=(const iterator& rhs); // CopyAssignable
            iterator& operator=(iterator&& rhs);      // MoveAssignable

            reference operator*() // Derefrenceable
            {
                return m_data[m_pos];
            }

            bool operator==(const iterator& rhs)
            {
                return (m_data == rhs.m_data) && (m_pos == rhs.m_pos);
            }

            bool operator!=(const iterator& rhs)
            {
                return !(*this == rhs);
            }

          private:
            size_type m_pos;
            pointer m_data;
        };

        array() = default;
        array(const std::initializer_list<T>& list);

        reference operator[](unsigned int index);

        size_type size() { return N; }

        iterator begin() { return iterator(m_data); }
        iterator end() { return iterator(N, m_data); }

      private:
        T m_data[N];
    };

    template <typename T, unsigned int N>
    array<T, N>::array(const std::initializer_list<T>& list)
    {
        if (list.size() > N)
        {
            throw new std::exception("Initializer list contains too many elements");
        }
        unsigned int pos = 0; // Can only declare one type in the ‘for’ initializer
        for (auto i = list.begin(); i != list.end(); ++i, pos++)
        {
            m_data[pos] = *i;
        }
    }

    template <typename T, unsigned int N>
    typename array<T, N>::reference array<T, N>::operator[](unsigned int index)
    {
        if (index < 0 || index >= N)
        {
            throw new std::exception("Index out of bounds");
        }
        return m_data[index];
    }

    template <typename T, unsigned int N>
    array<T, N>::iterator::iterator(const iterator& obj)
    {
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
    }

    template <typename T, unsigned int N>
    array<T, N>::iterator::iterator(iterator&& obj) noexcept
    {
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
        obj.m_pos = 0;
        obj.m_data = nullptr;
    }

    template <typename T, unsigned int N>
    typename array<T, N>::iterator array<T, N>::iterator::operator++()
    {
        m_pos++;
        return *this;
    }

    template <typename T, unsigned int N>
    typename array<T, N>::iterator array<T, N>::iterator::operator++(int)
    {
        iterator i = *this;
        m_pos++;
        return i;
    }

    template <typename T, unsigned int N>
    typename array<T, N>::iterator& array<T, N>::iterator::operator=(const iterator& rhs)
    {
        this->m_pos = rhs.m_pos;
        this->m_data = rhs.m_data;
        return *this;
    }

    template <typename T, unsigned int N>
    typename array<T, N>::iterator& array<T, N>::iterator::operator=(iterator&& rhs)
    {
        if (this != &rhs)
        {
            std::swap(this->m_pos, rhs.m_pos);
            std::swap(this->m_data, rhs.m_data);
        }
        return *this;
    }
} // namespace usu
