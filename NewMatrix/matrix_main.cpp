#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<double> matrix_a("A", 2, 2);
    Matrix<int> matrix_b("B", 2, 2);

    matrix_a.SetElements();
    matrix_b.SetElements();

    matrix_a.Show();
    matrix_b.Show();

    cout << "\n\n\tEnd of program\n";

    return 0;
}
