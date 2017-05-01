#include <iostream>
#include "../../../Library/matrix.h"

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
        matrix_a.SetElements();
        matrix_a.Show();

        cout << "\n\n\tdeterminant : " << matrix_a.GetDeterminant();

        if(matrix_a.GetDeterminant() == 0)
        {
            cout << "\n\tsystem has no solution...";
            cout << "\n\n\tEnd of program\n";
            return 0;
        }

        cout << "\n\n\tadjoint matrix : ";
        matrix_a.GetAdjoint().Show();
        cout << "\n\n\treverse matrix : ";
        matrix_a.GetReverse().Show();
        cout << "\n\n\tright part of equations system setup : " << endl;
        matrix_b.SetElements();
        cout << "\n\n\tX = A^(-1) * B = ";
        matrix_x = matrix_a.GetReverse().Multiplicate(matrix_b);
        matrix_x.Show();

        cout << endl;

        for(int i = 1; i <= rows; ++i)
            cout << "\n\tx" << i << " = " << matrix_x.EditElement(i, 1);

    }
    catch(Matrix<MatrixType>::MatrixArithmeticException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<MatrixType>::MatrixAccessException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<MatrixType>::MatrixTypeException exp)
    {
        exp.errmsg();
    }

    cout << "\n\n\tEnd of program\n";

    return 0;
}
