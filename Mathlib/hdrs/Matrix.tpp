#include "../hdrs/Matrix.hpp"

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(const array_sequence<T> &array) : 
_array(array), _rows(Rows), _columns(Columns), _isSquare(Rows == Columns && Rows > 0), _isSingular(false), _isIdentity(false) 
{
    if (array.get_length() != Rows*Columns)
    {
        throw std::length_error("Array length bigger than count of matrix elements");
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(const Vec<T> &vector) : _array(vector.get_length()), _rows(vector.get_length()), _columns(1), _isSquare(m == n), isSingular(false), _isIndentity(false) {}
{
    for (int i = 0; i < vector.get_length(); i++)
    {
        array[i] = vector[i];
    }
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>::Matrix(const Matrix<T, Rows, Columns> &other) : _array(other.GetSize()), _rows(other.GetNumRows()), _Columns(other.GetNumCol()), _isSquare(other.IsSquare()), _isSingular(other.IsSingular()), _isIdentity(other.IsIdentity()) 
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
    
    LUDecompose(A, P);
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
    return _array[i + j*_rows];
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

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator=(const Matrix<T, Rows, Columns> &other)
{
    if (this != &other)
    {
        _array = other._array;
        _isSingular = other._isSingular;
        _isIdentity = other._isIdentity;
    }
    return *this;
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::operator+=(const Matrix<T, Rows, Columns> &other)
{
    for (int i = 0; i < _array.get_length(); i++)
    {
        _array[i] += other._array[i];
    }

    return *this;
}

template <typename T, std::size_t Rows, std::size_t Columns>
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::operator*(const T &value)
{
    Matrix<T, Rows, Columns> *result = new Matrix(*this);

    for (int i = 0; i < _array.get_length(); i++)
    {
        result->_array[i] = _array[i];
    }

    return  uniq_ptr matrixPtr(result);
} 

template <typename T, size_t Rows, std::size_t Columns>
template <size_t OtherColumns> 
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::operator*(const Matrix<T, Rows, Columns> &other)
{
    Matrix<T, Rows, Column> *result = new Matrix();
    int numRow = 1;
    T p = 0;

    for (int j = 0; j < _columns; j++)
    {
        for (int k = 0; k < _columns; k++)
        {
           p += (*this).GetElement(numRow, k) * other.GetElement(k, j + numRow);
        }

        (*result)[j*_rows + numRow - 1] = p;
        p = 0;

        if (j == _columns - 1 && numRow < _rows)
        {
            j = -1;
            numRow++;
            continue;
        }
    }

    return uniq_ptr<Matrix<T, Rows, Columns>> (result);
}

template <typename T, size_t Rows, size_t Columns>
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::operator+(const Matrix &other)
{
    Matrix<T, Rows, Columns> *result = new Matrix();

    for (int i = 0; i < _array.get_length(); i++)
    {
        result->SetElement(i) = _array[i] + other.GetIndexEl(i);
    }

    return uniq_ptr(result);
}

template <typename T, size_t Rows, size_t Columns>
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::Add(const Matrix<T, Rows, Columns> &other) const
{
    auto result = *this + other;
    return result;
}

template <typename T, size_t Rows, size_t Columns>
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::Multiply(const Matrix &other) const 
{
    auto result = *this * other;
    return result;
}

template <typename T, size_t Rows, size_t Columns>
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::Multiply(const T &value) const
{
    auto result = *this * value;
    return result;
}

template <typename T, size_t Rows, size_t Columns>
uniq_ptr<Matrix<T, Rows, Columns>> Matrix<T, Rows, Columns>::GetInverse()
{

}

template <typename T, size_t Rows, size_t Columns>
int Matrix<T, Rows, Columns>::LUDecompose(Matrix<T, Rows, Columns> &A, array_sequence<T> &P)
{
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
            _isIdentity = true;
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
}