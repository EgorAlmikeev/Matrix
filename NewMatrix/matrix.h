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

    class MatrixException
    {
    public :

        enum errorflag {add, deduct, multiplication, division, equal, swap};

        static inline void errormsg(const Matrix& first_culprit, const Matrix& second_culprit, errorflag flag)
        {
            string what_happened;

            switch(flag)
            {
            case add : what_happened = " CAN'T ADD "; break;
            case deduct : what_happened = " CAN'T DEDUCT "; break;
            case multiplication : what_happened = " CAN'T MULTIPLICATE "; break;
            case equal : what_happened = " CAN'T EQUAL "; break;
            case swap : what_happened = " CANT'T SWAP "; break;
            }

            STD_ERROR_STREAM << "\n#error :" << what_happened << "\"" << first_culprit.name << "\""
                             << "[" << first_culprit.rows << "][" << first_culprit.columns << "] and "
                             << "\"" << second_culprit.name << "\""
                             << "[" << second_culprit.rows << "][" << second_culprit.columns << "]\n";
            exit(1);
        }
    };

    void Show();

    void SetElements();
    void Transpose();
    void SwapRows(short row_a, short row_b);
    void SwapColumns(short column_a, short column_b);
    void StairStep();
    void Resize(short _rows, short _columns);
    void Reset();

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

    elements = nullptr;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(Matrix<TypeOfMatrixElements>& copying_matrix)
{
    register int i, j;

    *this->Reset();

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
            typeid(TypeOfMatrixElements).name() == typeid(long double).name() ||
            typeid(TypeOfMatrixElements).name() == typeid(double).name() ||
            typeid(TypeOfMatrixElements).name() == typeid(float).name()
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
            typeid(TypeOfMatrixElements).name() == typeid(long double).name() ||
            typeid(TypeOfMatrixElements).name() == typeid(double).name() ||
            typeid(TypeOfMatrixElements).name() == typeid(float).name()
      )
        STD_OUT_STREAM << setiosflags(ios::fixed) << setprecision(1) << setfill(' ');

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
    if(row_a <= rows && row_b <= rows)
        swap(elements[row_a - 1], elements[row_b - 1]);
    else throw MatrixException();
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::SwapColumns(short column_a, short column_b)
{
    register int i, j;

    if(column_a <= columns && column_b <= columns)
    {
        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                if(j == column_a - 1)
                    swap(elements[i][j], elements[i][column_b - 1]);
    }
    else throw MatrixException();
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::Resize(short _rows, short _columns)
{
    TypeOfMatrixElements **old_elements = elements;
    register int i, j;

    try
    {
        elements = new TypeOfMatrixElements* [_rows];

        for(i = 0; i < _rows; ++i)
            elements[i] = new TypeOfMatrixElements[_columns];

        for(i = 0; i < rows; ++i)
            for(j = 0; j < columns; ++j)
                elements[i][j] = old_elements[i][j];

        for(i = 0; i < rows; ++i)
            delete [] old_elements[i];
        delete [] old_elements;

        rows = _rows;
        columns = _columns;
    }
    catch(bad_alloc)
    {
        STD_CRITICAL_STREAM << "\n#error : CAN'T ALLOC MEMORY\n";
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

//functios END

//operators/logic

template <class TypeOfMatrixElements>
bool Matrix<TypeOfMatrixElements>::operator == (const Matrix<TypeOfMatrixElements>& comparable_matrix)
{
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
        throw MatrixException();
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
        throw MatrixException();
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
        throw MatrixException();
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
        throw MatrixException();
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
        throw MatrixException();
    }
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>& Matrix<TypeOfMatrixElements>::operator = (const Matrix<TypeOfMatrixElements>& equalable_matrix)
{
    register int i, j;

    *this->Reset();

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
