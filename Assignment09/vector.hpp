#include <iostream>
#include <memory>
#include <utility>
#include <functional>
#include <exception>
#include <stdexcept>
#include <typeinfo>

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

        resize_type DEFAULT_RESIZE = [](size_type currentCapacity) -> size_type
        {
            return currentCapacity * 2;
        };

        const size_type DEFAULT_CAPACITY = 10;

         class iterator
        {

          public:
            using iterator_category = std::bidirectional_iterator_tag;
            iterator() : iterator(nullptr)
            {
            };
            iterator(pointer pointer) : iterator(0, pointer)
            {
            };
            iterator(size_type position, pointer pointer) :
                m_pointer(pointer),
                m_position(position)
            {
            };

            iterator(const iterator& oldIter);
            iterator(iterator&& oldIter) noexcept;
            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);
            iterator& operator=(const iterator& oldIter);
            iterator& operator=(iterator&& oldIter);

            reference operator*()
            {
                return m_pointer[m_position];
            };

            T* operator->()
            {
                return &m_pointer[m_position];
            };

            bool operator==(const iterator& iter) 
            { 
                return m_position == iter.m_position; 
            };
            bool operator!=(const iterator& iter) 
            { 
                return m_position != iter.m_position; 
            };

          private:
            size_type m_position;
            pointer m_pointer;
        };

        vector() :
            vector([](size_type currentCapacity) -> size_type
                   {
                       return currentCapacity * 2;
                   })
        {
        }

        vector(size_type size) :
            vector(size, [](size_type currentCapacity) -> size_type
                   {
                       return currentCapacity * 2;
                   })
        {
        }

        vector(resize_type resize) :
            vector(0, resize)
        {
        };

        vector(size_type size, resize_type resize) :
            m_size(size),
            m_capacity(DEFAULT_CAPACITY),
            m_rawArray(nullptr),
            m_resizer(resize)
        {
            if (DEFAULT_CAPACITY < size)
            {
                m_capacity = size * 2;
            }
            m_rawArray = std::make_shared<T[]>(m_capacity);
        };

        vector(std::initializer_list<T> list) :
            vector(list, [](size_type currentCapacity) -> size_type
                   { return currentCapacity * 2; })
        {
        }

        vector(std::initializer_list<T> list, resize_type resize) :
            m_size(0),
            m_capacity(DEFAULT_CAPACITY),
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

        reference operator[](size_type index)
        {
            if (index >= m_size || index < 0)

            {
                throw new std::range_error("Index Out of Bounds");
            }
            return m_rawArray[index];
        };

        void add(T value)
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

        void insert(size_type index, T value)
        {
            if (index > m_size || index < 0)
            {
                throw new std::range_error("Index Out of Bounds");
            }


            if (m_size + 1>= m_capacity)
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
            for (size_type i = index + 1; i < (m_size); i++) {
                auto nextShift = m_rawArray[i];
                m_rawArray[i] = toShift;
                toShift = nextShift;
            }
           
            m_rawArray[index] = value;

        };

        void remove(size_type index)
        {
            if (index >= m_size || index < 0)
            {
                throw new std::range_error("Index Out of Bounds");
            }

            // If this works I STG
            size_type tempMax = size_type(m_size);
            m_size = index;
            for (size_type i = index + 1; i < tempMax; i++)
            {
                add(m_rawArray[i]);
            }
        };

        void clear()
        {
            m_size = 0;
        };

        size_type size()
        {
            return m_size;
        };

        size_type capacity()
        {
            return m_capacity;
        };

        iterator begin()
        {
            return iterator(m_rawArray);
        };

        iterator end()
        {
            return iterator(m_size, m_rawArray);
        };

       

      private:
        size_type m_size;
        size_type m_capacity;
        pointer m_rawArray;
        resize_type m_resizer;
    };

     template <typename bool>
    class vector
    {

      public:
        class container
        {
        };

        using size_type = std::size_t;
        using reference = container&;
        using pointer = std::shared_ptr<container[]>;
        using value_type = T;
        using resize_type = std::function<size_type(size_type)>;

        resize_type DEFAULT_RESIZE = [](size_type currentCapacity) -> size_type
        {
            return currentCapacity * 2;
        };

        const size_type DEFAULT_CAPACITY = 10;


         class iterator
        {

          public:
            using iterator_category = std::bidirectional_iterator_tag;
            iterator() : iterator(nullptr)
            {
            };
            iterator(pointer pointer) : iterator(0, pointer)
            {
            };
            iterator(size_type position, pointer pointer) :
                m_pointer(pointer),
                m_position(position)
            {
            };

            iterator(const iterator& oldIter);
            iterator(iterator&& oldIter) noexcept;
            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);
            iterator& operator=(const iterator& oldIter);
            iterator& operator=(iterator&& oldIter);

            reference operator*()
            {
                return m_pointer[m_position];
            };

            T* operator->()
            {
                return &m_pointer[m_position];
            };

            bool operator==(const iterator& iter) 
            { 
                return m_position == iter.m_position; 
            };
            bool operator!=(const iterator& iter) 
            { 
                return m_position != iter.m_position; 
            };

          private:
            size_type m_position;
            pointer m_pointer;
        };

        vector() :
            vector([](size_type currentCapacity) -> size_type
                   {
                       return currentCapacity * 2;
                   })
        {
        }

        vector(size_type size) :
            vector(size, [](size_type currentCapacity) -> size_type
                   {
                       return currentCapacity * 2;
                   })
        {
        }

        vector(resize_type resize) :
            vector(0, resize)
        {
        };

        vector(size_type size, resize_type resize) :
            m_size(size),
            m_capacity(DEFAULT_CAPACITY),
            m_rawArray(nullptr),
            m_resizer(resize)
        {
            if (DEFAULT_CAPACITY < size)
            {
                m_capacity = size * 2;
            }
            m_rawArray = std::make_shared<T[]>(m_capacity);
        };

        vector(std::initializer_list<T> list) :
            vector(list, [](size_type currentCapacity) -> size_type
                   { return currentCapacity * 2; })
        {
        }

        vector(std::initializer_list<T> list, resize_type resize) :
            m_size(0),
            m_capacity(DEFAULT_CAPACITY),
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

        reference operator[](size_type index)
        {
            if (index >= m_size || index < 0)

            {
                throw new std::range_error("Index Out of Bounds");
            }
            return m_rawArray[index];
        };

        void add(T value)
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

        void insert(size_type index, T value)
        {
            if (index > m_size || index < 0)
            {
                throw new std::range_error("Index Out of Bounds");
            }


            if (m_size + 1>= m_capacity)
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
            for (size_type i = index + 1; i < (m_size); i++) {
                auto nextShift = m_rawArray[i];
                m_rawArray[i] = toShift;
                toShift = nextShift;
            }
           
            m_rawArray[index] = value;

        };

        void remove(size_type index)
        {
            if (index >= m_size || index < 0)
            {
                throw new std::range_error("Index Out of Bounds");
            }

            // If this works I STG
            size_type tempMax = size_type(m_size);
            m_size = index;
            for (size_type i = index + 1; i < tempMax; i++)
            {
                add(m_rawArray[i]);
            }
        };

        void clear()
        {
            m_size = 0;
        };

        size_type size()
        {
            return m_size;
        };

        size_type capacity()
        {
            return m_capacity;
        };

        iterator begin()
        {
            return iterator(m_rawArray);
        };

        iterator end()
        {
            return iterator(m_size, m_rawArray);
        };

       

      private:
        size_type m_size;
        size_type m_capacity;
        pointer m_rawArray;
        resize_type m_resizer;
    };

} // namespace usu