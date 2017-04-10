#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{   

    system("clear");

    Matrix<int> matrix_a("A", 3, 3);

    matrix_a.show();

    return 0;
}
