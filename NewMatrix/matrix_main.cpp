#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 3, 3);


    matrix_a.EditElement(1, 1) = 1;
    matrix_a.EditElement(1, 2) = 2;
    matrix_a.EditElement(1, 3) = 3;
    matrix_a.EditElement(2, 1) = 4;
    matrix_a.EditElement(2, 2) = 5;
    matrix_a.EditElement(2, 3) = 6;
    matrix_a.EditElement(3, 1) = 7;
    matrix_a.EditElement(3, 2) = 8;
    matrix_a.EditElement(3, 3) = 9;
    matrix_a.Show();
    matrix_a.Resize(2, 2);
    matrix_a.Show();


    cout << "\n\n\tEnd of program\n";

    return 0;
}
