#pragma once
#include <stdexcept>
#include <iostream>

template <class T>
class Stack
{
private:
    size_t m_capacity;
    size_t m_size;
    T* m_data;

public:
    Stack() {
        this->m_capacity=0;
        this->m_size=0;
        this->m_data=nullptr;
	}
    Stack(size_t capacity)
    {
        this->m_size=0;
        this->m_capacity=capacity;
        this->m_data=nullptr;
        if (capacity > 0) {
            m_data = new T[capacity]; // Dynamically allocate array of size `capacity`
        }
    }
    ~Stack()
    {
        delete [] m_data;
        m_data=nullptr;
    }

    bool is_empty() const {
        return (m_size==0);
    }

    void clear() {
        delete [] m_data;
        m_data=nullptr;
        this->m_capacity=0;
        this->m_size=0;
    }

    void reserve(size_t new_capacity)
    {

     if (new_capacity > m_capacity) {
            T* new_data = new T[new_capacity];

            // Copy existing elements to the new array
            for (size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }

            // Free the old memory
            delete[] m_data;

            // Update the stack
            m_data = new_data;
            m_capacity = new_capacity;
        }
    }

    void push_back(const T& value)
    {
        if (m_size == m_capacity) {

            size_t new_capacity;
            if (m_capacity == 0) {
                new_capacity = 1;
            } else {
                new_capacity = 2 * m_capacity;
            }
            reserve(new_capacity);
        }
        m_data[m_size++]=value;

    }

    T pop_back()
    {
        if (m_size==0){
            throw std::out_of_range("");
        }else{
            return m_data[--m_size];
        }
    }

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack)
    {
        os << "[ ";
        for (size_t i = 0; i < stack.m_size; ++i) {
            os << stack.m_data[i] << ' ';
        }
        os << ']';
        return os;
    }
};
