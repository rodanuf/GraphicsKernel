#pragma once

#include "build/_deps/lab3_2ndsem-src/headers/fixed_array.hpp"

template <typename T, std::size_t Rows, std::size_t Columns>
class Matrix;

template <typename T, std::size_t N>
class Vec
{
private:
    fixed_array<T, N> _array{};
    std::size_t length{N};

public:
    Vec() = default;
    Vec(const Vec &other);

    Vec& operator=(const Vec &other);
    Vec& operator+=(const Vec &other);
    Vec operator+(const Vec &other);
    Vec& operator*=(const T &num);
    Vec operator*(const Vec &other);
    Vec operator*=(const Matrix &other);
    T& operator[](int i);

};

#include "Matrix.hpp"
#include "Vec.tpp"