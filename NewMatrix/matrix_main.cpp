#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 7, 7);

    matrix_a.SetElements();

    matrix_a.Show();

    int det = matrix_a.GetDeterminant();

    cout << "\n\tDeterminant of matrix A = " << det << endl;

    cout << "\n\n\tEnd of program\n";

    return 0;
}
