#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 2, 2);
    Matrix<int> matrix_b("B", 3, 3);

    matrix_a.SetElements();
    matrix_b.SetElements();

    matrix_a.Show();
    matrix_b.Show();

    try
    {
        matrix_a *= matrix_b;
    }
    catch(Matrix<int>::MatrixException)
    {
        Matrix<int>::MatrixException::errormsg(matrix_a, matrix_b, Matrix<int>::MatrixException::multiplication);
    }

    matrix_a = matrix_b;

    matrix_a.Show();

    cout << "\n\n\tEnd of program\n";

    return 0;
}
