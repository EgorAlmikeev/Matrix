#include <iostream>
#include "../../../../Library/matrix.h"

using namespace std;

int main()
{
    system("clear");

    typedef double MatrixType;

    int rows, columns;

    cout << "\n\tset rows : ";
    cin >> rows;

    cout << "\n\tset columns : ";
    cin >> columns;

    cin.clear();
    cin.ignore(10, '\n');

    Matrix<MatrixType> matrix_a("A", rows, columns);
    Matrix<MatrixType> matrix_b("B", rows, 1);
    Matrix<MatrixType> matrix_x("X", rows, 1);

    try
    {

        cout << "\n\n\tleft part of eqations system setup : " << endl;
        matrix_a.setElements();
        matrix_a.show();

        cout << "\n\n\tdeterminant : " << matrix_a.getDeterminant();

        if(matrix_a.getDeterminant() == 0)
        {
            cout << "\n\tsystem has no solution...";
            cout << "\n\n\tEnd of program\n";
            return 0;
        }

        cout << "\n\n\tadjoint matrix : ";
        matrix_a.getAdjoint().show();
        cout << "\n\n\treverse matrix : ";
        matrix_a.getReverse().show();
        cout << "\n\n\tright part of equations system setup : " << endl;
        matrix_b.setElements();
        cout << "\n\n\tX = A^(-1) * B = ";
        matrix_x = matrix_a.getReverse().multiplicate(matrix_b);
        matrix_x.show();

        cout << endl;

        for(int i = 1; i <= rows; ++i)
            cout << "\n\tx" << i << " = " << matrix_x.at(i, 1);

    }
    catch(Matrix<MatrixType>::MatrixArithmeticException exp)
    {
        exp.print_message();
    }
    catch(Matrix<MatrixType>::MatrixAccessException exp)
    {
        exp.print_message();
    }
    catch(Matrix<MatrixType>::MatrixTypeException exp)
    {
        exp.print_message();
    }

    cout << "\n\n\tEnd of program\n";

    return 0;
}
