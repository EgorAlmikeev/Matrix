#include <iostream>
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
    Matrix(string _name, int _rows, int _columns);

    ~Matrix();

    void Show();

    void SetElements();

private :

    string name;
    int rows;
    int columns;

    TypeOfMatrixElements **elements;

    short GetLongestElementSize();
};

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix()
{
    name = "Empty";
    rows = 0;
    columns = 0;

    elements = NULL;
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::Matrix(string _name, int _rows, int _columns) : name(_name), rows(_rows), columns(_columns)
{
    elements = new TypeOfMatrixElements* [rows];

    register int i, j;

    for(i = 0; i < rows; ++i)
        elements[i] = new TypeOfMatrixElements[columns];

    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
            elements[i][j] = static_cast<TypeOfMatrixElements>(0);
}

template <class TypeOfMatrixElements>
Matrix<TypeOfMatrixElements>::~Matrix()
{
    register int i;

    for(i = 0; i < rows; ++i)
        delete [] elements[i];

    delete [] elements;
}

template <class TypeOfMatrixElements>
short Matrix<TypeOfMatrixElements>::GetLongestElementSize()
{
    short longest_element_size = 2;
    bool sign = false;

    register int i, j;

    for(i = 0; i < rows; ++i)
        for(j = 0; j < columns; ++j)
        {
            short current_element_size = 1;
            TypeOfMatrixElements current_element = elements[i][j];

            sign = (current_element < 0) ? true : sign;

            while(current_element /= 10)
                current_element_size++;

            longest_element_size = (current_element_size > longest_element_size) ? current_element_size : longest_element_size;
        }

    longest_element_size += (sign) ? 1 : 0;
    return longest_element_size;
}

template <class TypeOfMatrixElements>
void Matrix<TypeOfMatrixElements>::Show()
{
    STD_OUT_STREAM << "\nMatrix \"" << name << "\" [" << rows << "][" << columns << "] : ";

    register int i, j;
    short spaces_quantity = this->GetLongestElementSize();

    for(i = 0; i < rows; ++i) {
        STD_OUT_STREAM << endl;
        for(j = 0; j < columns; ++j)
        {
            print_simbol(' ', spaces_quantity);
            STD_OUT_STREAM << elements[i][j];
        }
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
                STD_WARNING_STREAM << "\n#error : Incorrect input\n";
            }
        }
        ++i;
        j = 0;
    }
}

#endif // MATRIX_H
