#pragma once

#include "build/_deps/lab3_2ndsem-src/headers/array_sequence.hpp"
#include "build/_deps/pointers-src/uniq_ptr.hpp"
#include <cmath>
#include <stdexcept>

template <typename T, std::size_t Rows = 4, std::size_t Columns = 4>
class Matrix 
{
private:
    fixed_array<T, Rows * Columns> _array{};
    std::size_t _rows{Rows};
    std::size_t _columns{Columns};
    bool _isSquare{Rows == Columns && Rows > 0};
    bool _isSingular{true};
    bool _isIdentity{false};

public:
    Matrix() = default;
    explicit Matrix(const array_sequence<T> &array);
    Matrix(const Vec<T> &vector);
    Matrix(const Matrix &other);

    void AddElement(int index, const T &num); // rewrite without void
    void SwapRows(int rowOne, int rowTwo);
    void SwapColumns(int colOne, int colTwo);
    void SetElement(int i, int j, const T &num);
    void Transpose();

    bool IsSquare();
    bool IsSingular();
    bool IsIdentity();

    int GetSize();
    int GetNumRows();
    int GetNumCol();

    T CalculateDet();
    T GetElement(int i, int j);
    T GetIndexEl(int index);

    T operator[](int index);
    
    Matrix& operator=(const Matrix &other);
    Matrix& operator+=(const Matrix &other);
    Matrix operator*(const T &value);
    template <size_t OtherColumns>
    Matrix operator*(const Matrix &other);
    Matrix operator+(const Matrix &other);



    Matrix Add(const Matrix &other) const;
    Matrix Multiply(const Matrix &other) const;
    Matrix Multiply(const T &value) const;
    Matrix GetInverse() const;
    Matrix GetTranspose() const;
    static Matrix GetIdentity();
    static Matrix GetScaling(const Vec<T> &scale) requires(Rows == 4 && Columns == 4);
    static Matrix GetRotation(const T &angle, const Vec<T> &axis) requires(Rows == 4 && Columns == 4);
    static Matrix GetTranslation(const Vec<T> &vector) requires(Rows == 4 && Columns == 4);

private:
    int LUDecompose(Matrix &A, array_sequence<int> &P);
    Matrix InverseLU(const Matrix &A, const array_sequence<int> &P);
};

#include "Matrix.tpp"