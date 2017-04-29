#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

    typedef double MatrixType;

    system("clear");

    Matrix<MatrixType> matrix_a("A", 20, 20);

    try
    {
        for(int i = 0, counter = 1; i < 20; ++i)
            for(int j = 0; j < 20; ++j, ++counter)
                matrix_a.EditElement(i + 1, j + 1) = counter;

        matrix_a.Show();

        matrix_a.StairStep();
        matrix_a.Show();
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
