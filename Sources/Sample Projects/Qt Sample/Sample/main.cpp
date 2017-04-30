#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{
    system("clear");

    typedef int MatrixType;
    int rows, columns;

    cout << "\n\tSet matrix rows : ";
    cin >> rows;
    cout << "\n\tSet matrix columns : ";
    cin >> columns;

    cin.clear();
    cin.ignore(10, '\n');


    Matrix<MatrixType> matrix_a("A", rows, columns);
    Matrix<MatrixType> matrix_b("B", rows, columns);


    try
    {
        matrix_a.SetElements();
        matrix_b.SetElements();
        matrix_a.Show();
        matrix_b.Show();
    }
    catch(Matrix<MatrixType>::MatrixArithmeticException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<MatrixType>::MatrixAccessException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<MatrixType>::MatrixTypeException exp)
    {
        exp.errmsg();
    }

    cout << "\n\n\tEnd of program\n";

    return 0;
}
