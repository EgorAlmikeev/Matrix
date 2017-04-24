#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 3, 3);
    Matrix<int> matrix_b("B", 3, 3);
    Matrix<int> matrix_c("C", 3, 3);

    try
    {
//        matrix_a + matrix_b;
//        matrix_a - matrix_b;
//        matrix_a * matrix_b;
//        matrix_a / matrix_b;
//        matrix_a % matrix_b;

//        matrix_a.SwapColumns(10, 9);
//        matrix_a.SwapRows(-2, 6);

        matrix_a.SetElements();
        matrix_b.SetElements();

        matrix_c = matrix_a * matrix_b;
        matrix_c.Show();

        matrix_c = matrix_a.Multiplicate(matrix_b);
        matrix_c.Show();
    }
    catch(Matrix<int>::MatrixArithmeticException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<int>::MatrixAccessException exp)
    {
        exp.errmsg();
    }

    cout << "\n\n\tEnd of program\n";

    return 0;
}
