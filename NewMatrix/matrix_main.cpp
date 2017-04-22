#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{

    system("clear");

    Matrix<int> matrix_a("A", 4, 4);
    Matrix<int> matrix_b("B", 3, 3);


    matrix_a.EditElement(1, 1) = 1;
    matrix_a.EditElement(1, 2) = 2;
    matrix_a.EditElement(1, 3) = 3;
    matrix_a.EditElement(1, 4) = 4;

    matrix_a.EditElement(2, 1) = 5;
    matrix_a.EditElement(2, 2) = 6;
    matrix_a.EditElement(2, 3) = 7;
    matrix_a.EditElement(2, 4) = 8;

    matrix_a.EditElement(3, 1) = 9;
    matrix_a.EditElement(3, 2) = 10;
    matrix_a.EditElement(3, 3) = 11;
    matrix_a.EditElement(3, 4) = 12;

    matrix_a.EditElement(4, 1) = 13;
    matrix_a.EditElement(4, 2) = 14;
    matrix_a.EditElement(4, 3) = 15;
    matrix_a.EditElement(4, 4) = 16;

    matrix_a.Show();

    matrix_b = matrix_a.GetMinor(2, 3);

    matrix_b.Show();


    cout << "\n\n\tEnd of program\n";

    return 0;
}
