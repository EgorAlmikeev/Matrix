#include "../../../../Library/matrix.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
    system("clear");

    typedef double Type;

    int rows, columns;
    Type determinant;

    vector<Type> solutions;
    solutions.reserve(10);

    cout << "\n\n\tRows : ";
    cin >> rows;

    cout << "\n\n\tColumns : ";
    cin >> columns;

    cin.clear();
    cin.ignore(10, '\n');

    try
    {
        Matrix<Type> matrix("A", rows, columns);

        cout << "\n\n\tSet all elements with the right part of the system :\n";
        matrix.SetElements();

        cout << "Matrix at start : ";
        matrix.Show();

        Matrix<Type> original_determinant_matrix("ORIGIN DET TEMP");
        original_determinant_matrix = matrix;

        original_determinant_matrix.Resize(rows, columns - 1);

        cout << "\n\nOriginal determinant matrix : ";
        original_determinant_matrix.Show();

        determinant = original_determinant_matrix.GetDeterminant();
        cout << "\n\nDeterminant : " << determinant;

        if(determinant == 0)
        {
            cout << "\n\nOriginal determinant = 0..."
                 << "\nSystem have no solutions...";
            cout << "\n\n\tEND OF PROGRAM...\n";
            return 0;
        }

        cout << "\n----------------------------------\n";

        for(int i = 0; i < columns - 1; ++i)
        {
            Matrix<Type> temp("TEMP");
            temp = matrix;

            temp.SwapColumns(i + 1, columns);
            temp.Resize(rows, columns - 1);

            cout << "\n\nTemp matrix : ";
            temp.Show();

            Type temp_determinant = temp.GetDeterminant();
            solutions.push_back(temp_determinant);

            cout << "\n\nTemp determinant #" << i + 1 << " : " << temp_determinant << endl;
        }
    }
    catch(Matrix<Type>::MatrixAccessException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<Type>::MatrixArithmeticException exp)
    {
        exp.errmsg();
    }
    catch(Matrix<Type>::MatrixTypeException exp)
    {
        exp.errmsg();
    }

    vector<Type>::iterator iter;
    int counter;

    cout << endl << "+" << setw(43) << setfill('-') << "-" << "+" << setfill(' ');

    for(iter = solutions.begin(), counter = 1; iter != solutions.end(); ++iter, ++counter)
    {
        cout << endl << setiosflags(ios::right) << "| x" << counter << " = "
             << setw(10) << *iter << " / " << setw(10) << setiosflags(ios::left)
             << determinant << " = " << setw(10)
             << *iter / determinant << " |";
    }

    cout << endl << "+" << setw(43) << setfill('-') << "-" << "+" << setfill(' ');

    cout << "\n\n\tEND OF PROGRAM...\n";

    return 0;
}
