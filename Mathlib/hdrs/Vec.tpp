#include "Vec.hpp"

template <typename T, std::size_t N>
Vec<T, N>::Vec(const Vec &other) : _array(other._array), length(other.length);

template <typename T, std::size_t N>
Vec<T, N>& Vec<T, N>::operator=(const Vec &other)
{
    for (int i = 0; i < other.length; i++)
    {
        _array[i] = other.length[i];
    }

    return *this;
}


template <typename T, std::size_t N>
Vec<T, N>& Vec<T, N>::operator+=(const Vec &other)
{
    for (int i = 0; i < _other.length; i++)
    {
        _array[i] += other.length[i];
    }

    return *this;
}


template <typename T, std::size_t N>
Vec<T, N> Vec<T, N>::operator+(const Vec &other)
{
    Vec<T, N> result;
    for (int i = 0; i < other.length; i++)
    {
        result[i] = (*this)._array[i] + other._array[i];
    }

    return result;
}


template <typename T, std::size_t N>
Vec<T, N>& Vec<T, N>::operator*=(const T &num)
{

}


template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>

template <typename T, std::size_t N>
