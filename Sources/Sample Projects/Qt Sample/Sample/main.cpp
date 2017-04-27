#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

    typedef int MatrixType;
//    typedef double MatrixType;

    system("clear");

    Matrix<MatrixType> matrix_a("A", 3, 3);
    Matrix<MatrixType> matrix_b("B", 3, 3);
    Matrix<MatrixType> matrix_c;

    try
    {
//        matrix_a.SetElements();
//        matrix_a.Show();

//        matrix_a + matrix_b;
//        matrix_a - matrix_b;
//        matrix_a * matrix_b;
//        matrix_a / matrix_b;
//        matrix_a % matrix_b;

//        matrix_a.SwapColumns(10, 9);
//        matrix_a.SwapRows(-2, 6);

//        matrix_c = matrix_a * matrix_b;
//        matrix_c.Show();

//        matrix_c = matrix_a.Multiplicate(matrix_b);
//        matrix_c.Show();

//        matrix_c = matrix_a.GetAdjoint();
//        matrix_c.Show();

        matrix_b = matrix_a.SetFill(9);
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

    cout << "\n\n\tEnd of program\n";

    return 0;
}
