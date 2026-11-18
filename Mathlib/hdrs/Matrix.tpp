#include "../hdrs/Matrix.hpp"

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix() : _array(Rows * Columns), _rows(Rows), _columns(Columns), _isSquare(Rows == Columns), _isSingular(false), _isIdentity(false) {}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(std::size_t m, std::size_t n) : _array(m * n), _rows(m), _columns(n), _isSquare(m == n), _isSingular(false), _isIdentity(false) {}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(const array_sequence<T> &array, std::size_t rows, std::size_t columns) : _array(array), _rows(rows), _columns(columns), _isSquare(rows == columns), _isSingular(false), _isIdentity(false) {}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(const Vec<T> &vector) : _array(vector.get_length()), _rows(vector.get_length()), _columns(1), _isSquare(m == n), isSingular(false), _isIndentity(false) {}
{
    for (int i = 0; i < vector.get_length(); i++)
    {
        array[i] = vector[i];
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(const Matrix<T> &other) : _array(other.GetSize()), _rows(other.GetNumRows()), _Columns(other.GetNumCol()), _isSquare(other.IsSquare()), _isSingular(other.IsSingular()), _isIdentity(other.IsIdentity()) 
{
    for (int i = 0; i < other.GetSize(); i++)
    {
        _array[i] = other[i];
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(Matrix<T> &&other) : 


template <typename T, std::size_t Rows, std::size_t Columns>
void Matrix<T, Rows, Columns>::AddElement(int index, const T &num)
{
    _array[i] += num;
}

template <typename T, std::size_t Rows, std::size_t Columns>
void Matrix<T, Rows, Columns>::SwapRows(int rowOne, int rowTwo)
{
    T elem;
    for (int k = 0; k < _columns; k++)
    {
        elem = _array[k + rowTwo];
        _array[k + rowTwo] = _array[k + rowOne];
        _array[k + rowOne] = elem;
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
void Matrix<T, Rows, Columns>::SwapColumns(int colOne, int colTwo)
{
    T elem;
    for (int k = 0; k < _rows; k++)
    {
        elem = _array[k + colTwo];
        _array[k + colTwo] = _array[k + colOne];
        _array[k + colOne] = elem;
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
void Matrix<T, Rows, Columns>::Transpose()
{
    if (_isSquare)
    {
        T a;
        size_t lshift = _rows - 1;
        size_t rshift = _rows + 1;
        for(int i = 0; i <= _array.get_length() - 2; i++)
        {
            if (i % rshift == 0)
            {
                continue;
            }
            if (i < (i / _rows)*rshift)
            {
                continue;
            }
            a = _array[i + (i % rshift)*lshift];
            _array[i + (i % rshift)*lshift] = _array[i];
            _array[i] = a;
        }
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
bool Matrix<T, Rows, Columns>::IsSquare()
{
    return _isSquare;
}

template <typename T, std::size_t Rows, std::size_t Columns>
bool Matrix<T, Rows, Columns>::IsSingular()
{
    return _isSingular;
}

template <typename T, std::size_t Rows, std::size_t Columns>
bool Matrix<T, Rows, Columns>::IsIdentity()
{
    return _isIdentity;
}

template <typename T, std::size_t Rows, std::size_t Columns>
int Matrix<T, Rows, Columns>::GetSize()
{
    return _array.get_length();
}

template <typename T, std::size_t Rows, std::size_t Columns>
int Matrix<T, Rows, Columns>::GetNumRows()
{
    return _rows;
}

template <typename T, std::size_t Rows, std::size_t Columns>
int Matrix<T, Rows, Columns>::GetNumCol()
{
    return _columns;
}

template <typename T, std::size_t Rows, std::size_t Columns>
T Matrix<T, Rows, Columns>::CalculateDet()
{
    Matrix<T, _rows, _columns> A = (*this);
    int s = 0;
    int target_line;
    T max_el = 0;
    T det = 0;

    for (int k = 0; k < _columns; k++)
    {
        target_line = k;
        max_el = std::abs(A[k*_columns + k]);
        for (int g = k; g < _rows; g++)
        {
            if (max_el < std::abs(A[k*_columns + g]))
            {
                max_el = std::abs(A[k*_columns + g]);
                target_line = g;
            }         
        }
        if (max_el < std::pow(10, -12))
        {
            return det;
        }
        if (k != target_line)
        {
            A.SwapRows(k, target_line);
            s += 1; 
        }

        for (int i = k + 1; i < _rows; i++)
        {
            T factor = A[k*_rows + i]/A[k*_columns + k];
            for (int j = k + 1; j < _columns; j++)
            {
                A[j*_rows + i] -= facor * A[j*_rows + k];
            }
        }
    }
    det = 1;
    for (int k = 0; k < _columns; k++)
    {
        det = det * A[k*_columns + k];
    }
    if (s % 2 != 0)
    {
        return -det;
    }
    return det;
}

template <typename T, std::size_t Rows, std::size_t Columns>
T Matrix<T, Rows, Columns>::GetElement(int i, int j)
{
    i -= 1;
    j -= 1; 
    return _array[(i + j) + j*_rows];
}

template <typename T, std::size_t Rows, std::size_t Columns>
T Matrix<T, Rows, Columns>::GetIndexEl(int index)
{
    return _array[index];
}

template <typename T, std::size_t Rows, std::size_t Columns>
T Matrix<T, Rows, Columns>::operator[](int index)
{
    return _array[index];
}

