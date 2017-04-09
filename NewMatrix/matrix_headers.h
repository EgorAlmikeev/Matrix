#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "stream_defines.h"

template <class TypeOfMatrixElements>
class Matrix
{
public :

    Matrix();
    Matrix(STD_NAMESPACE::string _name, int _rows, int _columns);

    ~Matrix();

    void Show();

private :

    STD_NAMESPACE::string name;
    int rows;
    int columns;

    TypeOfMatrixElements **elements;

    short GetLongestElementSize();
};

#endif // MATRIX_H
