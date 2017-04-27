#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

//    typedef int MatrixType;
    typedef double MatrixType;

    system("clear");

    Matrix<MatrixType> matrix_a("A", 3, 3);
    Matrix<MatrixType> matrix_b("B", 3, 3);
    Matrix<MatrixType> matrix_c;

    try
    {
        matrix_a.SetElements();
//        int counter = 0;

//        for(int i = 0; i < 3; ++i)
//            for(int j = 0; j < 3; ++j)
//                matrix_a.EditElement(i + 1, j + 1) = ++counter;

        matrix_c = matrix_a.GetAdjoint();
        matrix_c.Show();
        matrix_c = matrix_a.GetReverse();
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
