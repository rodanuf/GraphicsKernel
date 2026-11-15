#pragma once

#include "build/_deps/lab3_2ndsem-src/headers/array_sequence.hpp"
#include <cmath>

template <typename T, std::size_t Rows = 4, std::size_t Columns = 4>
class Matrix 
{
private:
    array_sequence<T> _array{Rows * Columns};
    std::size_t _rows;
    std::size_t _columns;
    bool _isSquare;
    bool _isSingular;
    bool _isIdentity;

public:
    Matrix();
    Matrix(std::size_t m, std::size_t n);
    Matrix(const array_sequence<T> &array, std::size_t rows, std::size_t columns);
    Matrix(const Vec<T> &vector);
    Matrix(const Matrix<T> &other);
    Matrix(Matrix<T> &&other);

    void AddElement(int index, const T &num); // rewrite without void
    void SwapRows(int rowOne, int rowTwo);
    void SwapColumns(int colOne, int colTwo);
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
    
    Matrix<T>& operator=(const Matrix<T> &other);
    Matrix<T>& operator+=(const Matrix<T> &other);
    Matrix<T> operator*(const T &value);
    Matrix<T>* operator*(const Matrix<T> &other);
    Matrix<T>* operator+(const Matrix<T> &other);



    Matrix<T>* Add(const Matrix &other);
    Matrix<T>* Multiply(const Matrix &other);
    Matrix<T>* Multiply(const T &value);
    Matrix<T>* GetInverse();
    Matrix<T>* GetTranspose();
    Matrix<T>* GetScaling(const Vec<T> &scale) requires(Rows == 4 && Columns == 4);
    Matrix<T>* GetRotation(const T &angle, const Vec<T> &axis) requires(Rows == 4 && Columns == 4);
    Matrix<T>* GetTranslation(const Vec<T> &vector) requires(Rows == 4 && Columns == 4);
};