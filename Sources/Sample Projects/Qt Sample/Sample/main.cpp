#include <iostream>
#include <time.h>
#include "../../../Library/matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 3, 3);
    Matrix<int> matrix_b("B", 2, 2);

    try
    {
        matrix_a + matrix_b;
        matrix_a - matrix_b;
        matrix_a * matrix_b;
        matrix_a / matrix_b;
        matrix_a % matrix_b;
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
