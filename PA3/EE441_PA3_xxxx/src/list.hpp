#pragma once

#include <stdexcept>
#include "memory.hpp"

template <class T>
class List
{
private:
    struct Node
    {
        T m_data;
        Node* m_prev;
        Node* m_next;

        Node(T data) : m_data(data), m_prev(nullptr), m_next(nullptr) { }
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(0) { }
    ~List() {
    Node* current = m_head;
    while (current != nullptr) {
        Node* next = current->m_next; // Save the next node

        delete current;               // Free the current node
        current = next;               // Move to the next node

    }
    m_head = m_tail = nullptr;        // Reset the head and tail pointers
    m_size = 0;                       // Reset the size
}


    size_t size() const {
        return m_size;
    }


    List(const List& other) : m_head(nullptr), m_tail(nullptr), m_size(0) {
    Node* current = other.m_head;
    while (current != nullptr) {
        push_back(current->m_data); // Reuse push_back to add new nodes

        current = current->m_next;
    }
    }

   List(List&& other) noexcept : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    List& operator=(const List& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }

        // Clear the existing list
        this->~List(); // Explicitly call the destructor to free memory

        // Copy elements from other
        Node* current = other.m_head;
        while (current != nullptr) {
            push_back(current->m_data);

            current = current->m_next;
        }

        return *this;
    }
    List& operator=(List&& other) noexcept {
        if (this == &other) {
            return *this; // Handle self-assignment
        }

        // Clear the existing list
        this->~List();

        // Transfer ownership of resources
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        // Reset the moved-from object
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

        return *this;
    }

private:
    // Helper function for inserting for the first time
    // Should only be called when m_head == nullptr
    inline void initiate(T data) {
        Node* only = new Node(data); // Create a new node
        m_head = m_tail = only;      // Set head and tail to this node
        m_size = 1;                  // Update size
    }

    // Helper function for removing the only element in a list with size 1.
    // Should only be called when m_head == m_tail
    inline T deplete()
    {
        if (m_head != m_tail) {
            throw std::logic_error("deplete should only be called for a single-node list.");
        }
        T data = m_head->m_data; // Store the data
        delete m_head;           // Delete the single node
        m_head = m_tail = nullptr; // Reset head and tail
        m_size = 0;              // Reset size
        return data;             // Return the data

    }

    // Helper function to connect two nodes in a doubly linked list
    static inline void hook(Node* prev, Node* next)
    {
        prev->m_next=next;
        next->m_prev=prev;
    }

public:
    void push_back(T data)
    {
        if (m_size == 0) {
            initiate(data); // Use initiate for an empty list
        }else{
        Node* newNode = new Node(data);
        hook(m_tail, newNode); // Link the current tail to the new node
        m_tail = newNode;      // Update tail
        ++m_size;              // Increment size
        }
    }

    void push_front(T data)
    {
        if (m_size == 0) {
            initiate(data); // Use initiate for an empty list
        } else {
            Node* newNode = new Node(data);
            hook(newNode, m_head); // Link the new node to the current head
            m_head = newNode;      // Update head
            ++m_size;              // Increment size
        }
    }

    T pop_back()
    {
        if (m_size == 0) {
            throw std::logic_error("Cannot pop_back from an empty list.");
        }
        if (m_size == 1) {
            return deplete(); // Use deplete for a single-node list
        }
        T data = m_tail->m_data; // Store the data
        Node* prev = m_tail->m_prev;
        delete m_tail;           // Delete the tail node
        m_tail = prev;           // Update tail
        m_tail->m_next = nullptr;
        --m_size;                // Decrement size
        return data;             // Return the data
    }

    T pop_front()
    {
        if (m_size == 0) {
            throw std::logic_error("Cannot pop_front from an empty list.");
        }
        if (m_size == 1) {
            return deplete(); // Use deplete for a single-node list
        }
        T data = m_head->m_data; // Store the data
        Node* next = m_head->m_next;
        delete m_head;           // Delete the head node
        m_head = next;           // Update head
        m_head->m_prev = nullptr;
        --m_size;                // Decrement size
        return data;             // Return the data
    }

    class Iterator
    {
    private:
        Node* m_node;

        Iterator(Node* node) : m_node(node) { }

        friend class List;

    public:
        bool operator==(Iterator other) const
        {
            return m_node == other.m_node;

        }

        bool operator!=(Iterator other) const
        {
            return m_node != other.m_node;
        }

        T& operator*()
        {
            return m_node->m_data; // Access the node's data
        }

        Iterator next()
        {
        if (!m_node || !m_node->m_next) {
            throw std::range_error("Next iterator cannot be obtained.");
        }
        return Iterator(m_node->m_next); // Return an iterator for the next node
        }

        // prefix increment
        Iterator operator++()
        {
            if (!m_node) {
                throw std::range_error("Iterator cannot be incremented: already at end.");
            }
            if (!m_node->m_next) {
                m_node = nullptr; // Move to end iterator
            } else {
                m_node = m_node->m_next; // Move to the next node
            }
            return *this;
        }

        // postfix increment
        Iterator operator++(int)
        {

        if (!m_node || !m_node->m_next) {
            throw std::range_error("Next iterator cannot be obtained.");
        }
        Iterator temp = *this; // Save the current state
        m_node = m_node->m_next; // Move to the next node
        return temp; // Return the old iterator
        }

    };

    class ConstIterator
    {
    private:
        const Node* m_node;

        ConstIterator(const Node* node) : m_node(node) { }

        friend class List;

    public:
        bool operator==(ConstIterator other) const
        {
            return m_node == other.m_node;
        }

        bool operator!=(ConstIterator other) const
        {
             return m_node != other.m_node;
        }

        const T& operator*() const
        {
            if (!m_node) {
            throw std::range_error("Cannot dereference end iterator.");
        }
        return m_node->m_data; // Access the node's data
        }

        ConstIterator next()
        {
            if (!m_node || !m_node->m_next) {
            throw std::range_error("Next iterator cannot be obtained.");
        }
        return ConstIterator(m_node->m_next); // Return a const iterator for the next node
        }



            // prefix increment
        ConstIterator operator++()
        {
        if (!m_node) {
                throw std::range_error("Iterator cannot be incremented: already at end.");
            }
            if (!m_node->m_next) {
                m_node = nullptr; // Move to end iterator
            } else {
                m_node = m_node->m_next; // Move to the next node
            }
        return *this;
        }

        // postfix increment
        ConstIterator operator++(int)
        {
        if (!m_node || !m_node->m_next) {
            throw std::range_error("Next iterator cannot be obtained.");
        }
        ConstIterator temp = *this; // Save the current state
        m_node = m_node->m_next; // Move to the next node
        return temp; // Return the old iterator
        }
    };

    Iterator begin()
    {
        return Iterator(m_head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    ConstIterator begin() const
    {
        return ConstIterator(m_head);
    }

    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    Iterator insert(Iterator iter, T data)
    {

        Node* newNode = new Node(data);
        Node* current = iter.m_node;  // Node to insert before
        Node* prev = current ? current->m_prev : nullptr; // Safely get prev node

        // Link the new node with adjacent nodes
        newNode->m_prev = prev;
        newNode->m_next = current;

        if (prev) {
            prev->m_next = newNode; // Connect prev to the new node
        } else {
            m_head = newNode; // If prev is nullptr, newNode becomes the head
        }

        if (current) current->m_prev = newNode;
            else m_tail = newNode; // Update tail if inserting at the end

        ++m_size;        // Increment size


    }

    Iterator remove(Iterator iter)
    {
        if (!iter.m_node) {
            throw std::logic_error("Cannot remove end iterator or null node.");
        }

        Node* toDelete = iter.m_node;  // Get the node to delete
        Node* prev = toDelete->m_prev; // Previous node
        Node* next = toDelete->m_next; // Next node


        if (prev) prev->m_next = next;
        else m_head = next; // Update head if no previous node
        if (next) next->m_prev = prev;
        else m_tail = prev; // Update tail if no next node
        delete toDelete; // Free the memory
        --m_size;        // Decrement size

        // Return an iterator to the next node
        return Iterator(next);
    }
};
