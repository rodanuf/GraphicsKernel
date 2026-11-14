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


template<typename T, std::size_t Rows, std::size_t Columns>
void Matrix<T, Rows, Columns>::AddElement(int index, const T &num)
{
    _array[i] += num;
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
    Matrix<T, _rows, _columns> A = (&this);
    int target_line;

    for (int k = 0; k < _rows; k++)
    {
        T max_el = 0;
        if (max_el < A[k])
        {
            max_el = A[k];
            target_line = k;
            if (k == _rows - 1)
            {
                target_line
            }
        }
    }
}