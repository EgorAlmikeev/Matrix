#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{
//    system("clear");

    int rows, columns = rows = 4;
    typedef double MatrixType;


    Matrix<MatrixType> matrix_a("A", rows, columns);


    try
    {
        matrix_a.SetElements();
        matrix_a.Show();

        matrix_a.StairStep();
        matrix_a.Show();

        cout << "\n\tMatrix A has null rows : " << matrix_a.HowManyNullRows();
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
        cout << "\n#error [Type]\n";
    }

    cout << "\n\n\tEnd of program\n";

    return 0;
}
