#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{   

    system("clear");

    Matrix<int> matrix_a("A", 5, 5);

    matrix_a.SetElements();

    matrix_a.Show();

    matrix_a.SwapColumns(1, 4);

    matrix_a.Show();

    cout << "\n\n\tEnd of program\n";

    return 0;
}
