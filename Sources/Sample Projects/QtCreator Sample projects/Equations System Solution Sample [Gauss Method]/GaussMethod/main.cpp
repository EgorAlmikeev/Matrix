#include "../../../../Library/matrix.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    typedef double Type;

    try
    {
        cout << "\n\tGauss method program\n";
        cout << "\nEnter the size of the matrix : ";
        setprecision(1);

        int size_of_matrix;
        cin >> size_of_matrix;
        cin.clear();
        cin.ignore(10, '\n');

        Matrix<Type> original_matrix("Matrix", size_of_matrix, size_of_matrix + 1);
        original_matrix.setElements();

        unsigned int start_time =  clock();

        Matrix<Type> cuted_matrix("CUTED");
        cuted_matrix = original_matrix;

        cuted_matrix.resize(size_of_matrix, size_of_matrix);

        original_matrix.stairStep();
        cuted_matrix.stairStep();

        cout << "\nStair step view : ";
        original_matrix.show();

        if(cuted_matrix.getDeterminant() == 0)
        {
            cout << "\n\tThis system have no solutions...";
            cout << "\n\tEND OF PROGRAM...\n";
            return 0;
        }

        if(original_matrix.getRank() != cuted_matrix.getRank())
        {
            cout << "\n\tRank of (A) matrix != rank of (A|B) matrix";
            cout << "\n\tEND OF PROGRAM...\n";
            return 0;
        }

        Type right_part[size_of_matrix];
        Type unknown_elements[size_of_matrix];

        for(int i = 0; i < size_of_matrix; ++i)
            unknown_elements[i] = 1;

        for(int i = 0; i < size_of_matrix; ++i)
            right_part[i] = original_matrix.at(i + 1, size_of_matrix + 1);


        unknown_elements[size_of_matrix - 1] = right_part[size_of_matrix - 1] / original_matrix.at(size_of_matrix, size_of_matrix);

        for(int i = size_of_matrix - 2; i >= 0; --i)
        {
            Type sum = 0;
            Type coefficient = original_matrix.at(i + 1, i + 1);

            for(int j = i + 1; j < size_of_matrix; ++j)
                sum += original_matrix.at(i + 1, j + 1) * unknown_elements[j];

            unknown_elements[i] = (right_part[i] - sum) / coefficient;
        }

        cout << "\n\nUnknown elements : ";
        for(int i = 0; i < size_of_matrix; ++i)
            cout << "\nx" << i + 1 << " = " << unknown_elements[i];

        unsigned int end_time = clock();
        cout << "\n\n\ttimer : " << start_time - end_time << " milliseconds";
    }
    catch(Matrix<Type>::MatrixAccessException exp)
    {
        exp.print_message();
    }
    catch(Matrix<Type>::MatrixArithmeticException exp)
    {
        exp.print_message();
    }
    catch(Matrix<Type>::MatrixTypeException exp)
    {
        exp.print_message();
    }

    cout << "\n\tEND OF PROGRAM...\n";
    return 0;
}
