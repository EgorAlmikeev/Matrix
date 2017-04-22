#include <iostream>
#include <iomanip>
#include "stream_defines.h"
#include "functions_headers.h"
#include "get_from_std_istream.h"

using namespace STD_NAMESPACE;

#ifndef MATRIX_H
#define MATRIX_H

template <class TypeOfMatrixElements>
class Matrix
{

public :

    Matrix();
    Matrix(Matrix& copying_matrix);
    Matrix(string _name, int _rows, int _columns);

    ~Matrix();

    class MatrixArithmeticException
    {
    public :

        enum errorflag {add, deduct, multiplication, division, equal, unknown};

        static inline void errormsg(const Matrix& first_culprit, const Matrix& second_culprit, errorflag flag)
        {
            string what_happened;

            switch(flag)
            {
            case add : what_happened = " CAN'T ADD "; break;
            case deduct : what_happened = " CAN'T DEDUCT "; break;
            case multiplication : what_happened = " CAN'T MULTIPLICATE "; break;
            case equal : what_happened = " CAN'T EQUAL "; break;
            case unknown : what_happened = " CAN'T CONCRETIZE ERROR "; break;
            }

            STD_ERROR_STREAM << "\n#error [arithmetic] : " << what_happened << "\"" << first_culprit.name << "\""
                             << "[" << first_culprit.rows << "][" << first_culprit.columns << "] and "
                             << "\"" << second_culprit.name << "\""
                             << "[" << second_culprit.rows << "][" << second_culprit.columns << "]\n";
            exit(1);
        }
    };
    class MatrixAccessException {};
    class MatrixTypeException {};

    void Show();

    void SetElements();
    void Transpose();

    void SwapRows(short row_a, short row_b);
    void SwapColumns(short column_a, short column_b);

    void StairStep();

    void Resize(const short _rows, const short _columns);
    void Reset();

    bool HasSameRows();
    bool HasSameColumns();

    Matrix GetMinor(short row, short column);
    TypeOfMatrixElements GetDeterminant();
    TypeOfMatrixElements& EditElement(const short _row, const short _column);

    Matrix operator + (const Matrix& addable_matrix);
    Matrix operator - (const Matrix& deductible_matrix);
    Matrix operator * (const Matrix& multiplier_matrix);
    Matrix operator / (const Matrix& divisor_matrix);
    Matrix operator % (const Matrix& divisor_matrix);

    bool operator == (const Matrix& comparable_matrix);

    Matrix& operator = (const Matrix& equalable_matrix);
    Matrix& operator = (const TypeOfMatrixElements& equalable_element);

    Matrix& operator += (const Matrix& addable_matrix);
    Matrix& operator += (const TypeOfMatrixElements& addable_element);
    Matrix& operator -= (const Matrix& deductible_matrix);
    Matrix& operator -= (const TypeOfMatrixElements& deductible_element);
    Matrix& operator *= (const Matrix& multiplier_matrix);
    Matrix& operator *= (const TypeOfMatrixElements& multiplier_element);
    Matrix& operator /= (const Matrix& divisor_matrix);
    Matrix& operator /= (const TypeOfMatrixElements& divisor_element);
    Matrix& operator %= (const Matrix& divisor_matrix);
    Matrix& operator %= (const TypeOfMatrixElements& divisor_element);

    template <class Type>
    friend Matrix<Type> operator + (const Matrix<Type>& base_matrix, const Type& addable_element);

    template <class Type>
    friend Matrix<Type> operator + (const Type& addable_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator - (const Matrix<Type>& base_matrix, const Type& deductible_element);

    template <class Type>
    friend Matrix<Type> operator - (const Type& deductible_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator * (const Matrix<Type>& base_matrix, const Type& multiplier_element);

    template <class Type>
    friend Matrix<Type> operator * (const Type& multiplier_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator / (const Matrix<Type>& base_matrix, const Type& divisor_element);

    template <class Type>
    friend Matrix<Type> operator / (const Type& divisor_element, const Matrix<Type>& base_matrix);

    template <class Type>
    friend Matrix<Type> operator % (const Matrix<Type>& base_matrix, const Type& divisor_element);

    template <class Type>
    friend Matrix<Type> operator % (const Type& divisor_element, const Matrix<Type>& base_matrix);

private :

    string name;
    short rows;
    short columns;

    TypeOfMatrixElements **elements;

    short GetLongestElementSize();
};

//constructors & destructors

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix()
{
    rows = 0;
    columns = 0;
    name = "EMPTY";

    elements = nullptr;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(Matrix<TypeOfMatrixElements>& copying_matrix)
{
    register int i, j;

    this->Reset();

    try
    {
        rows = copying_matrix.rows;
        columns = copying_matrix.columns;

        elements = new TypeOfMatrixElements* [rows];

        for(i = 0; i < rows; ++i)
            elements[i] = new TypeOfMatrixElements[columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = copying_matrix.elements[i][j];
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(string _name, int _rows, int _columns) : name(_name), rows(_rows), columns(_columns)
{
    register int i, j;

    try
    {
        elements = new TypeOfMatrixElements* [rows];

        for(i = 0; i < rows; ++i)
            elements[i] = new TypeOfMatrixElements[columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = static_cast<TypeOfMatrixElements>(0);
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::~Matrix()
{
    register int i;

    for(i = 0; i < rows; ++i)
        delete [] elements[i];

    delete [] elements;
}

//constructors & destructors END

//functions

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::GetLongestElementSize()
{
    short longest_element_size = 2;
    bool sign = false;
    bool integer = true;

    register int i, j;

    if(
            typeid(TypeOfMatrixElements) == typeid(long double) ||
            typeid(TypeOfMatrixElements) == typeid(double) ||
            typeid(TypeOfMatrixElements) == typeid(float)
      )
        integer = false;

    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
        {
            short current_element_size = 1;
            TypeOfMatrixElements current_element;
            int current_integer_element;

            if(integer)
            {
                current_element = elements[i][j];

                while(current_element /= 10)
                    ++current_element_size;

                sign = (current_element < 0) ? true : sign;
            }
            else
            {
                current_integer_element = elements[i][j];

                while(current_integer_element /= 10)
                    ++current_element_size;

                sign = (current_integer_element < 0) ? true : sign;
            }

            longest_element_size = (current_element_size > longest_element_size) ? current_element_size : longest_element_size;
        }

    longest_element_size += (sign) ? 1 : 0;
    longest_element_size += (integer) ? 0 : 2;

    return longest_element_size + 1;
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::Show()
{
    STD_OUT_STREAM << "\n\nMatrix \"" << name << "\" [" << rows << "][" << columns << "] : ";

    if(
            typeid(TypeOfMatrixElements) == typeid(long double) ||
            typeid(TypeOfMatrixElements) == typeid(double) ||
            typeid(TypeOfMatrixElements) == typeid(float)
      )
        STD_OUT_STREAM << setiosflags(ios::fixed) << setprecision(1);

    register int i, j;
    short printable_size = this->GetLongestElementSize();

    for(i = 0; i < rows; ++i)
    {
        STD_OUT_STREAM << endl;
        for(j = 0; j < columns; ++j)
            STD_OUT_STREAM << setw(printable_size) << elements[i][j];
    }
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::SetElements()
{
    STD_OUT_STREAM << "\nMatrix \"" << name << "\" [" << rows << "][" << columns << "] elements setup : ";

    register int i = 0, j = 0;

    while(i < rows)
    {
        STD_OUT_STREAM << endl;
        while(j < columns)
        {
            try
            {
                STD_OUT_STREAM << "\t" << name << "[" << i + 1 << "][" << j + 1 << "] : ";
                elements[i][j] = GetFormStdIstream<TypeOfMatrixElements>::get();
                ++j;
            }
            catch(GetFormStdIstream<int>::GetFromStdIstreamException)
            {
                STD_ERROR_STREAM << "\n#error : Incorrect input\n";
            }
        }
        ++i;
        j = 0;
    }
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::Transpose()
{
    Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = elements[j][i];
    *this = temp;
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::SwapRows(short row_a, short row_b)
{
    --row_a;
    --row_b;

    if(row_a < rows && row_b < rows && row_a >= 0 && row_b >= 0)
        swap(elements[row_a], elements[row_b]);
    else throw MatrixAccessException();
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::SwapColumns(short column_a, short column_b)
{
    register int i, j;

    --column_a;
    --column_b;

    if(column_a < columns && column_b < columns && column_a >= 0 && column_b >= 0)
    {
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                if(j == column_a)
                    swap(elements[i][j], elements[i][column_b]);
    }
    else throw MatrixAccessException();
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::Resize(const short _rows, const short _columns)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", _rows, _columns);
    register int i, j;

    if(_rows > 0 && _columns > 0)
    {
        if(rows < _rows && columns < _columns)
        {
            for(i = 0; i < rows; ++i)
                for(j = 0; j < columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }
        else if(rows > _rows && columns > _columns)
        {
            for(i = 0; i < _rows; ++i)
                for(j = 0; j < _columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }
        else if(rows >= _rows && columns <= _columns)
        {
            for(i = 0; i < _rows; ++i)
                for(j = 0; j < columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }
        else if(rows <= _rows && columns >= _columns)
        {
            for(i = 0; i < rows; ++i)
                for(j = 0; j < _columns; ++j)
                    temp.elements[i][j] = elements[i][j];
        }

        *this = temp;
    }
    else
    {
        throw MatrixAccessException();
    }

}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::Reset()
{
    if(rows != 0 && columns != 0 && elements != nullptr)
    {
        register int i, j;
        for(i = 0; i < rows; ++i)
            delete [] elements[i];
        delete [] elements;
        rows = columns = 0;
    }
}

template <class TypeOfMatrixElements>
TypeOfMatrixElements Matrix<TypeOfMatrixElements>::GetDeterminant()
{
    if(rows != 2 && columns != 2)
    {
//        if(HasSameRows() || HasSameColumns())
//            return 0;

        TypeOfMatrixElements determinant = 0;

        for(int j = 0; j < columns; ++j)
            determinant += elements[0][j] * pow(-1, 1 + j + 1) * GetMinor(1, j + 1).GetDeterminant();
        return determinant;
    }
    else
        return elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::GetMinor(short excluded_row, short excluded_column)
{
    Matrix<TypeOfMatrixElements> minor("MINOR", rows - 1, columns - 1);
    register int i = 0, j = 0, minor_row = 0, minor_column = 0;

    --excluded_row;
    --excluded_column;


    if(excluded_row < rows && excluded_column < columns && excluded_row >= 0 && excluded_column >= 0 && rows == columns)
    {
        for(i = 0; i < rows; ++i)
            if(i != excluded_row)
                for(j = 0; j < columns; ++j)
                    if(j != excluded_column)
                    {
                        minor.elements[minor_row][minor_column] = elements[i][j];
                        if(minor_column + 1 == minor.columns)
                        {
                            ++minor_row;
                            minor_column = 0;
                        }
                        else
                            ++minor_column;
                    }
        return minor;
    }
    else
    {
        throw MatrixAccessException();
    }
}

template <class TypeOfMatrixElements>
TypeOfMatrixElements& Matrix<TypeOfMatrixElements>::EditElement(const short _row, const short _column)
{
    if(_row <= rows && _row > 0 && _column <= columns && _column > 0)
    {
        return elements[_row - 1][_column - 1];
    }
    else
    {
        throw MatrixArithmeticException();
    }
}

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::HasSameRows()
{
    register int i, j, k;
    bool find_same = true;

    for(i = 0, find_same = true; i < rows; ++i)
        for(j = i + 1, find_same = true; j < rows; ++j)
            for(k = 0; k < columns; ++k)
            {
                find_same *= (elements[i][k] == elements[j][k]) ? true : false;
                if(find_same)
                    return true;
            }

    return false;
}

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::HasSameColumns()
{
    register int i, j, k;
    bool find_same = true;

    for(i = 0, find_same = true; i < columns; ++i)
        for(j = i + 1, find_same = true; j < columns; ++j)
            for(k = 0; k < rows; ++k)
            {
                find_same *= (elements[k][i] == elements[k][j]) ? true : false;
                if(find_same)
                    return true;
            }

    return false;
}

//functios END

//operators/logic

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::operator == (const Matrix<TypeOfMatrixElements>& comparable_matrix)
{
    if(
            typeid(TypeOfMatrixElements) != typeid(float) ||
            typeid(TypeOfMatrixElements) != typeid(double) ||
            typeid(TypeOfMatrixElements) != typeid(long double)
      )
        if(rows == comparable_matrix.rows && columns == comparable_matrix.columns)
        {
            bool iscompare = true;
            register int i, j;
            for(i = 0; i < rows; ++i)
                for(j = 0; j < columns; ++j)
                    iscompare = (elements[i][j] == comparable_matrix.elements[i][j]) ? iscompare : false;
            return iscompare;
        }
        else
        {
            return false;
        }
    else
    {
        throw MatrixTypeException();
    }
}

//operators/logic END

//operators/arithmetic

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator + (const Matrix<TypeOfMatrixElements>& addable_matrix)
{
    if(rows == addable_matrix.rows && columns == addable_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
        register int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] + addable_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException();
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator - (const Matrix<TypeOfMatrixElements>& deductible_matrix)
{
    if(rows == deductible_matrix.rows && columns == deductible_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
        register int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] - deductible_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException();
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator * (const Matrix<TypeOfMatrixElements>& multiplier_matrix)
{
    if(columns == multiplier_matrix.rows)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, multiplier_matrix.columns);
        register int i, j, k;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < multiplier_matrix.columns; ++j)
            {
                TypeOfMatrixElements sum = static_cast<TypeOfMatrixElements>(0);
                for(k = 0; k < rows; ++k)
                    sum += elements[i][k] * multiplier_matrix.elements[k][i];
                temp.elements[i][j] = sum;
            }
        return temp;
    }
    else
    {
        throw MatrixArithmeticException();
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator / (const Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    if(rows == divisor_matrix.rows && columns == divisor_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
        register int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] / divisor_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException();
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> Matrix<TypeOfMatrixElements>::operator % (const Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    if(rows == divisor_matrix.rows && columns == divisor_matrix.columns)
    {
        Matrix<TypeOfMatrixElements> temp("TEMP", rows, columns);
        register int i, j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                temp.elements[i][j] = elements[i][j] % divisor_matrix.elements[i][j];
        return temp;
    }
    else
    {
        throw MatrixArithmeticException();
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator = (const Matrix<TypeOfMatrixElements>& equalable_matrix)
{
    register int i, j;

    this->Reset();

    try
    {
        rows = equalable_matrix.rows;
        columns = equalable_matrix.columns;

        elements = new TypeOfMatrixElements* [rows];

        for(i = 0; i < rows; ++i)
            elements[i] = new TypeOfMatrixElements[columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = equalable_matrix.elements[i][j];
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
    }
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator = (const TypeOfMatrixElements& equalable_element)
{
    register int i, j;
    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
            elements[i][j] = equalable_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator += (const Matrix& addable_matrix)
{
    *this = *this + addable_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator += (const TypeOfMatrixElements& addable_element)
{
    *this = *this + addable_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator -= (const Matrix& deductible_matrix)
{
    *this = *this - deductible_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator -= (const TypeOfMatrixElements& deductible_element)
{
    *this = *this - deductible_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator *= (const Matrix& multiplier_matrix)
{
    *this = *this * multiplier_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator *= (const TypeOfMatrixElements& multiplier_element)
{
    *this = *this * multiplier_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator /= (const Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    *this = *this / divisor_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator /= (const TypeOfMatrixElements& divisor_element)
{
    *this = *this / divisor_element;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator %= (const Matrix<TypeOfMatrixElements>& divisor_matrix)
{
    *this = *this % divisor_matrix;
    return *this;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator %= (const TypeOfMatrixElements& divisor_element)
{
    *this = *this % divisor_element;
    return *this;
}

//operators/arithmetic/friend

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator + (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& addable_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] + addable_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator + (const TypeOfMatrixElements& addable_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] + addable_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator - (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& deductible_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] - deductible_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator - (const TypeOfMatrixElements& deductible_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = deductible_element - base_matrix.elements[i][j];
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator * (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& multiplier_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] * multiplier_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator * (const TypeOfMatrixElements& multiplier_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] * multiplier_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator / (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& divisor_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] / divisor_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator / (const TypeOfMatrixElements& divisor_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = divisor_element / base_matrix.elements[i][j];
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator % (const Matrix<TypeOfMatrixElements>& base_matrix, const TypeOfMatrixElements& divisor_element)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = base_matrix.elements[i][j] % divisor_element;
    return temp;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements> operator % (const TypeOfMatrixElements& divisor_element, const Matrix<TypeOfMatrixElements>& base_matrix)
{
    Matrix<TypeOfMatrixElements> temp("TEMP", base_matrix.rows, base_matrix.columns);
    register int i, j;
    for(i = 0; i < temp.rows; ++i)
        for(j = 0; j < temp.columns; ++j)
            temp.elements[i][j] = divisor_element % base_matrix.elements[i][j];
    return temp;
}

//operators/arithmetic/friend END

//operatorsarithmetic/ END

#endif // MATRIX_H
