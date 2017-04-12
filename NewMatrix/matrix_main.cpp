#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{   

    system("clear");

    Matrix<int> matrix_a("A", 3, 3);
    Matrix<int> matrix_b("B", 3, 3);
    Matrix<int> matrix_c("C", 3, 3);

    matrix_a.SetElements();
    matrix_b.SetElements();

    matrix_a.Show();
    matrix_b.Show();

    matrix_c = matrix_a + 1;

    matrix_c.Show();

    cout << "\n\n\tEnd of program\n";

    return 0;
}