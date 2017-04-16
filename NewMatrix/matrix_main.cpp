#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<double> matrix_a("A", 2, 2);

    matrix_a.SetElements();

    matrix_a.Show();

    matrix_a.SwapRows(0, 1);
    matrix_a.SwapColumns(0, 1);

    matrix_a.Show();

    cout << "\n\n\tEnd of program\n";

    return 0;
}
