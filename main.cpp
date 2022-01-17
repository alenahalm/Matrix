#include "Matrix.h"

int main() {

    Matrix M(3 ,3);

    Matrix M1(3, 3);
    int a = 0;

    double array[3][3] = {
            {1, 2, 1},
            {3, 4, 0},
                {2, 0, 3}
    };
    double array2[3][3] = {
            {2, 4, 1},
            {0, 2,1},
            {2, 1, 1}
    };

    for (int i = 0; i < M.getN(); ++i) {
        for (int j = 0; j < M.getM(); ++j) {
            M.setByIndex(i, j, array[i][j]);
            M1.setByIndex(i, j, array2[i][j]);
        }
    }


    cout << "Matrix 1:" << endl;
    cout << M;
    cout << endl;
    cout << "Determinant:" << endl;
    cout << M.getDeterminant(3);
    cout << endl;
    cout << "Transpose:" << endl;
    cout << M.transpose();
    cout << endl;
    cout << "Inverse:" << endl;
    cout << M.getInverse(3);
    cout << endl;
    cout << "Matrix 2:" << endl;
    cout << M1;
    cout << endl;
    cout << "M1 + M2:"<< endl;
    cout << M + M1;
    cout << endl;
    cout << "M1 * M2:" << endl;
    cout << M * M1;
    cout << endl;
    cout << "M1 - M2:" << endl;
    cout << M - M1;
    cout << endl;
    cout << "M1 * 5:" << endl;
    cout << M * 5;
    cout << endl;
}
