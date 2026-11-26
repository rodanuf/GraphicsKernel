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
void Matrix<T, Rows, Columns>::SetElement(int i, int j, const T &num)
{
    i -= 1;
    j -= 1;
    _array[i + j*_rows] = num;
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
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator*(const T &value)
{
    Matrix<T, Rows, Columns> result = *this;

    for (int i = 0; i < _array.get_length(); i++)
    {
        result[i] = (*this)[i] * value;
    }

    return  result;
} 

template <typename T, std::size_t Rows, std::size_t Columns>
template <size_t OtherColumns> 
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator*(const Matrix<T, Rows, Columns> &other)
{
    Matrix<T, Rows, Column> result;
    int numRow = 1;
    T p = 0;

    for (int j = 0; j < _columns; j++)
    {
        for (int k = 0; k < _columns; k++)
        {
           p += (*this).GetElement(numRow, k) * other.GetElement(k, j + numRow);
        }

        result[j*_rows + numRow - 1] = p;
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
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator+(const Matrix &other)
{
    Matrix<T, Rows, Columns> result;

    for (int i = 0; i < _array.get_length(); i++)
    {
        result.SetElement(i) = _array[i] + other.GetIndexEl(i);
    }

    return uniq_ptr(result);
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::Add(const Matrix<T, Rows, Columns> &other) const
{
    auto result = *this + other;
    return result;
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::Multiply(const Matrix &other) const 
{
    auto result = *this * other;
    return result;
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::Multiply(const T &value) const
{
    auto result = *this * value;
    return result;
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::GetInverse() const
{
    if (_isSingular)
    {
        throw std::runtime_error("Matrix is singular, cannot compute inverse.");
    }

    array_sequence<int> P;
    Matrix<T, Rows, Columns> *A  = new Martrix(*this);
    int s = LUDecompose(*A, P);
    return InverseLU(*A, P);
}

template <typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::GetTranspose() const
{
    Matrix<T, Rows, Columns> result = *this;
    result.Transpose();
    return result;
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::GetIdentity()
{
    Matrix<T, Rows, Columns> result;

    for (int i = 1; i < _array.get_length() + 1; i++)
    {
        result.SetElement(i, i, 1);
    }

    return result;
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::GetScaling(const Vec<T> &scale) 
requires (Rows == 4 && Columns == 4)
{
    Matrix<T, Rows, Columns> result;
    for (int i = 1; i < 5; i ++)
    {
        result.SetElement(i, i, scale[i]);
    }
    result.SetElement(4, 4, 1);
    return result;
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::GetRotation(const T &angle, const Vec<T> &axis)
requires (Rows == 4 && Columns == 4)
{
    Matrix<T, Rows, Columns> result;
    T c = std::cos(angle);
    T s = std::sin(angle);
    T t = 1 - c;
    T x = axis[0];
    T y = axis[1];
    T z = axis[2];

    result.SetElement(1, 1, t*x*x + c);
    result.SetElement(1, 2, t*x*y - s*z);
    result.SetElement(1, 3, t*x*z + s*y);
    result.SetElement(2, 1, t*x*y + s*z);
    result.SetElement(2, 2, t*y*y + c);
    result.SetElement(2, 3, t*y*z - s*x);
    result.SetElement(3, 1, t*x*z - s*y);
    result.SetElement(3, 2, t*y*z + s*x);
    result.SetElement(3, 3, t*z*z + c);
    result.SetElement(4, 4, 1);

    return result;
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::GetTranslation(const Vec<T> &vector)
requires(Rows == 4 && Columns == 4)
{
    Martix<T, Rows, Columns> result;
    for (int i = 1; i < 5; i ++)
    {
        result.SetElement(i, i, 1);
    }
    for (int i = 1; i < 4; i++)
    {
        result.SetElement(i, 4, scale[i - 1]);
    }

    return result;
}

template <typename T, std::size_t Rows, std::size_t Columns>
int Matrix<T, Rows, Columns>::LUDecompose(Matrix<T, Rows, Columns> &A, array_sequence<int> &P)
{
    P.clear();
    P = array_sequence<int>(_rows);
    for (int i = 0; i < _rows; i++)
    {
        P[i] = i;
    }
    int s = 0;
    int target_line;
    int buffer = 0;
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
            buffer = P[k];
            P[k] = P[target_line];
            P[target_line] = buffer;
            A.SwapRows(k, target_line);
            s += 1; 
        }

        for (int i = k + 1; i < _rows; i++)
        {
            T factor = A[k*_rows + i]/A[k*_columns + k];
            A[k*_rows + i] = factor;
            for (int j = k + 1; j < _columns; j++)
            {
                A[j*_rows + i] -= facor * A[j*_rows + k];
            }
        }
    }

    return s;
}

template <typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::InverseLU(const Matrix<T, Rows, Columns> &LU, const array_sequence<int> &P)
{
    Matrix<T, Rows, Columns> *result = new Matrix();
    for (int k = 1; k < _rows + 1; k++)
    {
        for (int i = 1; i < _rows + 1; i++)
        {
            if (P[i - 1] + 1 == k)
            {
                result->SetElement(i, k, 1);
            }
            else
            {
                result->SetElement(i, k, 0);
            }
        }

        for (int i = 1; i < _rows + 1; i++)
        {
            T sum = result->GetElement(i, k);
            for (int j = 1; j < i; j++)
            {
                sum -= LU.GetElement(i, j) * result->GetElement(j, k);
            }
            result->SetElement(i, k, sum);
        }

        for (int i = _rows; i >= 0; i--)
        {
            T sum = result->GetElement(i, k);
            for (int j = i + 1; j < _rows + 1; j++)
            {
                sum -= LU.GetElement(i, j) * result->GetElement(j, k);
            }
            result->SetElement(i, k, sum / LU.GetElement(i, i));
        }
    }

    return Matrix<T, Rows, Columns>>(result);
}