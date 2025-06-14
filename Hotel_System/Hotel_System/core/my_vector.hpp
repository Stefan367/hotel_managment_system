#pragma once

#include <stdexcept>

template <typename T>
class my_vector
{
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize();
    void copy_from(const my_vector& other);
    void free();

public:
    my_vector() = default;
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    void push_back(const T& value);
    void remove_at(size_t index);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t get_size() const;
    void clear();

    T* raw_data();
};

template <typename T>
void my_vector<T>::resize()
{
    size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size; ++i)
    {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
void my_vector<T>::copy_from(const my_vector& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
void my_vector<T>::free()
{
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template <typename T>
my_vector<T>::my_vector(const my_vector& other)
{
    copy_from(other);
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector& other)
{
    if (this != &other)
    {
        free();
        copy_from(other);
    }
    return *this;
}

template <typename T>
my_vector<T>::~my_vector()
{
    free();
}

template <typename T>
void my_vector<T>::push_back(const T& value)
{
    if (size >= capacity)
    {
        resize();
    }
    data[size++] = value;
}

template <typename T>
void my_vector<T>::remove_at(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Invalid index! Cannot remove the selected item!");
    }
    for (size_t i = index; i < size - 1; ++i)
    {
        data[i] = data[i + 1];
    }
    --size;
}

template <typename T>
T& my_vector<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Invalid index! Cannot take that item!");
    }
    return data[index];
}

template <typename T>
const T& my_vector<T>::operator[](size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Invalid index! Cannot take that item!");
    }
    return data[index];
}

template <typename T>
size_t my_vector<T>::get_size() const
{
    return size;
}

template <typename T>
void my_vector<T>::clear()
{
    free();
}

template <typename T>
T* my_vector<T>::raw_data()
{
    return data;
}