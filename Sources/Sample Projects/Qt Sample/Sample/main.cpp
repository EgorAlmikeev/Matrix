#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{
    system("clear");

    typedef int MatrixType;

    Matrix<MatrixType> matrix_a("A", 3, 3);
    Matrix<MatrixType> matrix_b("B", 3, 3);
    Matrix<MatrixType> result("RESULT", 3, 3);


    try
    {

        matrix_a.SetElements();
        matrix_b.SetElements();

        matrix_a.Show();
        matrix_b.Show();

        result = matrix_a.Multiplicate(matrix_b);
        result.Show();

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
