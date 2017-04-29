#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

    typedef int MatrixType;

    system("clear");

    Matrix<MatrixType> matrix_a("A", 3, 3);
    Matrix<MatrixType> matrix_c("Minor");

    try
    {
        matrix_a.SetElements();
        matrix_a.Show();

        cout << "\n\tMin row of matrix A = " << matrix_a.GetMinRow();
    }
    catch(Matrix<MatrixType>::MatrixArithmeticException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<MatrixType>::MatrixAccessException exp)
    {
        exp.errmsg();
    }

    cout << "\n\n\tEnd of program\n";

    return 0;
}
