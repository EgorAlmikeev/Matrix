#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 2, 2);

    matrix_a.Show();
    matrix_a.Resize(4, 4);
    matrix_a.Show();

    cout << "\n\n\tEnd of program\n";

    return 0;
}
