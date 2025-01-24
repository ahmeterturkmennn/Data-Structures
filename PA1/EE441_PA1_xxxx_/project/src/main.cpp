#include <iostream>
#include <stdexcept> // for exceptions

// maximum size of the sorted list
#define SORTEDLIST_MAX_SIZE 20

class SortedList
{
    private:
    float elements[SORTEDLIST_MAX_SIZE]; //hold the elements
    size_t size;

    public:
    SortedList() : size(0) { }

    void copy(const SortedList& other) {//copy the list
        size = other.size;
        for (size_t i = 0; i<other.size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    float index(size_t ind)//return spesific index from list
{
    if (ind >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return elements[ind];
}

size_t insert(float number)
{//insert number to list
    if (size >= SORTEDLIST_MAX_SIZE)
    {
        throw std::length_error("Insertion will exceed maximum array size");
    }

    size_t index = 0;
    while (index < size && elements[index] < number)
    {
        ++index;
    }

    for (size_t i = size; i > index; --i)
    {
        elements[i] = elements[i - 1];
    }

    elements[index] = number;
    ++size;

    return index;
}

float remove(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    float removedValue = elements[index];

    for (size_t i = index; i < size - 1; ++i)
    {
        elements[i] = elements[i + 1];
    }

    --size;

    return removedValue;
}

size_t find(float number)
{
    size_t left = 0;
    size_t right = size;

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;

        if (elements[mid] == number)
        {
            return mid;
        }
        else if (elements[mid] < number)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    throw std::domain_error("Number not found in the list");
}

void printList() const {
    if (size == 0) {
    std::cout << "The list is empty" << std::endl;
} else
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << elements[i];
        if (i < size - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
        }
    };

int main()
{
    SortedList list;

    try
    {
        // Demonstrate insertion
        list.insert(10);
        list.insert(5);
        list.insert(7);
        list.insert(15);
        list.printList(); // Output: 5 7 10 15

        // Demonstrate finding an element
        size_t index = list.find(10);
        std::cout << "Found 10 at index: " << index << std::endl; // Output: Found 10 at index: 2

        // Try to find an element not in the list
        try
        {
            list.find(20); // Should throw an exception
        }
        catch (const std::exception&e) {
    std::cerr << e.what() << std::endl; // Output: Number not found in the list
}

// Demonstrate removal
float removedValue = list.remove(2);
std::cout << "Removed value: " << removedValue << std::endl; // Output: Removed value: 10
list.printList(); // Output: 5 7 15

// Try to remove from an out-of-range index
try
{
    list.remove(10); // Should throw an exception
}
catch (const std::exception&e) {
    std::cerr << e.what() << std::endl; // Output: Index out of range
}

// Empty the list
list.remove(0);
list.remove(0);
list.remove(0);
list.printList(); // Output: The list is empty

}
catch (const std::exception&e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

return 0;
}
