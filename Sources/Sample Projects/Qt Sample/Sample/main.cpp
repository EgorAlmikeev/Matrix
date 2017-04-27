#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

    typedef int MatrixType;

    system("clear");

    Matrix<MatrixType> matrix_a("A", 3, 3);
    Matrix<MatrixType> matrix_c("RESULT");

    try
    {
        matrix_a.SetElements();
        matrix_a.Show();

        matrix_c = matrix_a.GetAdjoint();
        matrix_c.Show();
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
