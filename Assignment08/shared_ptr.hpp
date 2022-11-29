#include <iostream>
#include <utility>

namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr(T* pointer)
        {
            m_pointer = pointer;
            m_count = new int(1);
        }

        shared_ptr(const shared_ptr& shared)
        {
            m_pointer = shared.m_pointer;
            m_count = shared.m_count;
            *m_count += 1;
        }

        shared_ptr(shared_ptr&& shared)
        {
            m_pointer = shared.m_pointer;
            m_count = shared.m_count;
            shared.m_pointer = nullptr;
            shared.m_count = nullptr;
        }

        ~shared_ptr()
        {
            if (m_pointer != nullptr)
            {
                if (*m_count > 1)
                {
                    *m_count -= 1;
                    m_pointer = nullptr;
                    m_count = nullptr;
                }
                else
                {
                    delete m_pointer;
                    delete m_count;
                    m_pointer = nullptr;
                    m_count = nullptr;
                }
            }
        }

        shared_ptr& operator=(const shared_ptr& shared)
        {
            *m_count -= 1;
            m_pointer = shared.m_pointer;
            m_count = shared.m_count;
            *m_count += 1;
            return *this;
        }

        shared_ptr& operator=(shared_ptr&& shared)
        {
            if (this != &shared)
            {
                T* tempPointer = std::move(m_pointer);
                int* tempCount = std::move(m_count);

                m_pointer = std::move(shared.m_pointer);
                m_count = std::move(shared.m_count);

                shared.m_count = std::move(tempCount);
                shared.m_pointer = std::move(tempPointer);
            }
            return *this;
        }

        T* operator->()
        {
            return m_pointer;
        }

        T operator*()
        {
            return *m_pointer;
        }

        T* get()
        {
            return m_pointer;
        }

        int use_count()
        {
            return *m_count;
        }

      private:
        T* m_pointer;
        int* m_count;
    };

    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        shared_ptr(T* pointer, int size)
        {
            m_pointer = pointer;
            m_size = new int(size);
            m_count = new int(1);
        }

        shared_ptr(const shared_ptr& shared)
        {
            m_pointer = shared.m_pointer;
            m_size = shared.m_size;
            m_count = shared.m_count;
            *m_count += 1;
        }

        shared_ptr(const shared_ptr&& shared)
        {
            m_pointer = shared.m_pointer;
            m_size = shared.m_size;
            m_count = shared.m_count;
            shared.m_pointer = nullptr;
            shared.m_size = nullptr;
            shared.m_count = nullptr;
        }

        ~shared_ptr()
        {
            if (m_pointer != nullptr)
            {
                if (*m_count > 1)
                {
                    *m_count -= 1;
                    m_pointer = nullptr;
                    m_size = nullptr;
                    m_count = nullptr;
                }
                else
                {
                    delete[] m_pointer;
                    delete m_size;
                    delete m_count;
                    m_size = nullptr;
                    m_pointer = nullptr;
                    m_count = nullptr;
                }
            }
        }

        shared_ptr& operator=(const shared_ptr& shared)
        {
            *m_count -= 1;
            m_pointer = shared.m_pointer;
            m_count = shared.m_count;
            m_size = shared.m_size;
            *m_count += 1;
            return *this;
        }

        shared_ptr& operator=(shared_ptr&& shared)
        {
            if (this != &shared)
            {
                T* tempPointer = std::move(m_pointer);
                int* tempCount = std::move(m_count);
                int* tempSize = std::move(m_size);

                m_pointer = std::move(shared.m_pointer);
                m_count = std::move(shared.m_count);
                m_size = std::move(shared.m_size);

                shared.m_count = std::move(tempCount);
                shared.m_pointer = std::move(tempPointer);
                shared.m_size = std::move(tempSize);
            }
            return *this;
        }

        T& operator[](int value)
        {
            return m_pointer[value];
        }

        int use_count()
        {
            return *m_count;
        }

        int size()
        {
            return *m_size;
        }

      private:
        T* m_pointer;
        int* m_count;
        int* m_size;
    };

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }

} // namespace usu