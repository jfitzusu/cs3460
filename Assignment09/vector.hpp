#pragma once
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <utility>

namespace usu
{

    template <typename T>
    class vector
    {

      public:
        using size_type = std::size_t;
        using reference = T&;
        using pointer = std::shared_ptr<T[]>;
        using value_type = T;
        using resize_type = std::function<size_type(size_type)>;

        class iterator
        {

          public:
            using iterator_category = std::bidirectional_iterator_tag;
            iterator();
            iterator(pointer pointer);
            iterator(size_type position, pointer pointer);
            iterator(const iterator& oldIter);
            iterator(iterator&& oldIter) noexcept;
            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);
            iterator& operator=(const iterator& oldIter);
            iterator& operator=(iterator&& oldIter);
            reference operator*();
            T* operator->();
            bool operator==(const iterator& iter);
            bool operator!=(const iterator& iter);

          private:
            size_type m_position;
            pointer m_pointer;
        };

        vector();
        vector(size_type size);
        vector(resize_type resize);
        vector(size_type size, resize_type resize);
        vector(std::initializer_list<T> list);
        vector(std::initializer_list<T> list, resize_type resize);
        reference operator[](size_type index);
        void add(T value);
        void insert(size_type index, T value);
        void remove(size_type index);
        void clear();
        size_type size();
        size_type capacity();
        iterator begin();
        iterator end();

      private:
        size_type m_size;
        size_type m_capacity;
        pointer m_rawArray;
        resize_type m_resizer;
        static const size_type M_DEFAULT_CAPACITY = 10;
        static inline resize_type M_DEFAULT_RESIZER = [](size_type currentCapacity) -> size_type
        {
            return currentCapacity * 2;
        };
    };

    template <>
    class vector<bool>
    {
      public:
        using size_type = std::size_t;
        using pointer = std::shared_ptr<std::uint8_t[]>;
        using value_type = bool;
        using resize_type = std::function<size_type(size_type)>;

        class reference
        {

          public:
            reference(std::uint8_t* byte, std::uint8_t bit);
            void operator=(const bool& toSet);
            operator bool();
            bool operator*();

          private:
            std::uint8_t* m_location;
            std::uint8_t m_bit;
        };

        class iterator
        {
          public:
            using iterator_category = std::bidirectional_iterator_tag;
            iterator();
            iterator(pointer pointer);
            iterator(size_type position, pointer pointer);
            iterator(const iterator& oldIter);
            iterator(iterator&& oldIter) noexcept;
            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);
            iterator& operator=(const iterator& oldIter);
            iterator& operator=(iterator&& oldIter);
            reference operator*();

            bool operator==(const iterator& iter);
            bool operator!=(const iterator& iter);

          private:
            size_type m_position;
            pointer m_pointer;
        };

        vector<bool>();
        vector<bool>(size_type size);
        vector<bool>(resize_type resize);
        vector<bool>(size_type size, resize_type resize);
        vector<bool>(std::initializer_list<bool> list);
        vector(std::initializer_list<bool> list, resize_type resize);

        reference operator[](size_type index);
        void add(bool value);
        void insert(size_type index, bool value);
        void remove(size_type index);
        size_type size();
        size_type capacity();
        void clear();
        iterator begin();
        iterator end();

      private:
        size_type m_size;
        size_type m_capacity;
        pointer m_rawArray;
        resize_type m_resizer;
        static const size_type M_DEFAULT_CAPACITY = 10;
        static inline resize_type M_DEFAULT_RESIZER = [](size_type currentCapacity) -> size_type
        {
            return currentCapacity * 2;
        };
    };

    template <typename T>
    vector<T>::iterator::iterator() :
        iterator(nullptr){};

    template <typename T>
    vector<T>::iterator::iterator(pointer pointer) :
        iterator(0, pointer){};

    template <typename T>
    vector<T>::iterator::iterator(size_type position, pointer pointer) :
        m_pointer(pointer),
        m_position(position){};

    template <typename T>
    vector<T>::iterator::iterator(const iterator& oldIter)
    {
        this->m_position = oldIter.m_position;
        this->m_pointer = oldIter.m_pointer;
    }

    template <typename T>
    vector<T>::iterator::iterator(iterator&& oldIter) noexcept
    {
        this->m_position = oldIter.m_position;
        this->m_pointer = oldIter.m_pointer;
        oldIter.m_position = 0;
        oldIter.m_pointer = nullptr;
    }

    template <typename T>
    vector<T>::iterator vector<T>::iterator::operator++()
    {
        m_position++;
        return *this;
    }

    template <typename T>
    vector<T>::iterator vector<T>::iterator::operator++(int)
    {
        iterator i = *this;
        m_position++;
        return i;
    }

    template <typename T>
    vector<T>::iterator vector<T>::iterator::operator--()
    {
        m_position--;
        return *this;
    }

    template <typename T>
    vector<T>::iterator vector<T>::iterator::operator--(int)
    {
        iterator i = *this;
        m_position--;
        return i;
    }

    template <typename T>
    vector<T>::iterator& vector<T>::iterator::operator=(iterator&& oldIter)
    {
        if (this != &oldIter)
        {
            std::swap(this->m_position, oldIter.m_position);
            std::swap(this->m_pointer, oldIter.m_pointer);
        }

        return *this;
    }

    template <typename T>
    vector<T>::reference vector<T>::iterator::operator*()
    {
        return m_pointer[m_position];
    };

    template <typename T>
    T* vector<T>::iterator::operator->()
    {
        return &m_pointer[m_position];
    };

    template <typename T>
    bool vector<T>::iterator::operator==(const iterator& iter)
    {
        return m_position == iter.m_position;
    };

    template <typename T>
    bool vector<T>::iterator::operator!=(const iterator& iter)
    {
        return m_position != iter.m_position;
    };

    template <typename T>
    vector<T>::vector() :
        vector(M_DEFAULT_RESIZER)
    {
    }
    template <typename T>
    vector<T>::vector(size_type size) :
        vector(size, M_DEFAULT_RESIZER)
    {
    }
    template <typename T>
    vector<T>::vector(resize_type resize) :
        vector(0, resize){};
    template <typename T>
    vector<T>::vector(size_type size, resize_type resize) :
        m_size(size),
        m_capacity(M_DEFAULT_CAPACITY),
        m_rawArray(nullptr),
        m_resizer(resize)
    {
        if (M_DEFAULT_CAPACITY < size)
        {
            m_capacity = size * 2;
        }
        m_rawArray = std::make_shared<T[]>(m_capacity);
    };
    template <typename T>
    vector<T>::vector(std::initializer_list<T> list) :
        vector(list, M_DEFAULT_RESIZER)
    {
    }
    template <typename T>
    vector<T>::vector(std::initializer_list<T> list, resize_type resize) :
        m_size(0),
        m_capacity(M_DEFAULT_CAPACITY),
        m_rawArray(nullptr),
        m_resizer(resize)
    {
        m_rawArray = std::make_shared<T[]>(m_capacity);
        int current = 0;
        for (auto i = list.begin(); i != list.end(); i++, current++)
        {
            add(*i);
        }
    };

    template <typename T>
    vector<T>::reference vector<T>::operator[](size_type index)
    {
        if (index >= m_size || index < 0)

        {
            throw std::range_error("Index Out of Bounds");
        }
        return m_rawArray[index];
    };

    template <typename T>
    void vector<T>::add(T value)
    {
        if (m_size >= m_capacity)
        {
            m_capacity = m_resizer(m_capacity);
            pointer newArray = std::make_shared<T[]>(m_capacity);
            for (unsigned int i = 0; i < m_size; i++)
            {
                newArray[i] = m_rawArray[i];
            }
            m_rawArray = newArray;
        }

        m_rawArray[m_size] = value;
        m_size++;
    };

    template <typename T>
    void vector<T>::insert(size_type index, T value)
    {
        if (index > m_size || index < 0)
        {
            throw std::range_error("Index Out of Bounds");
        }

        if (m_size + 1 >= m_capacity)
        {
            m_capacity = m_resizer(m_capacity);
            pointer newArray = std::make_shared<T[]>(m_capacity);
            for (unsigned int i = 0; i < m_size; i++)
            {
                newArray[i] = m_rawArray[i];
            }
            m_rawArray = newArray;
        }

        m_size++;
        auto toShift = m_rawArray[index];
        for (size_type i = index + 1; i < (m_size); i++)
        {
            auto nextShift = m_rawArray[i];
            m_rawArray[i] = toShift;
            toShift = nextShift;
        }

        m_rawArray[index] = value;
    };

    template <typename T>
    void vector<T>::remove(size_type index)
    {
        if (index >= m_size || index < 0)
        {
            throw std::range_error("Index Out of Bounds");
        }

        // If this works I STG
        size_type tempMax = size_type(m_size);
        m_size = index;
        for (size_type i = index + 1; i < tempMax; i++)
        {
            add(m_rawArray[i]);
        }
    };

    template <typename T>
    void vector<T>::clear()
    {
        m_size = 0;
    };

    template <typename T>
    vector<T>::size_type vector<T>::size()
    {
        return m_size;
    };

    template <typename T>
    vector<T>::size_type vector<T>::capacity()
    {
        return m_capacity;
    };

    template <typename T>
    vector<T>::iterator vector<T>::begin()
    {
        return iterator(m_rawArray);
    };

    template <typename T>
    vector<T>::iterator vector<T>::end()
    {
        return iterator(m_size, m_rawArray);
    };
} // namespace usu