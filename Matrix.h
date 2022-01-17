#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
using namespace std;

class Matrix {
private:
    int n, m;
    double** matrix;
public:
    Matrix();
    Matrix(int _n, int _m);
    Matrix(int _n, int _m, double **arr);
    ~Matrix();
    Matrix(const Matrix& M);
    double getByIndex(int i, int j);
    void setByIndex(int i, int j, double value);
    Matrix transpose();
    Matrix getInverse(int size);
    double getDeterminant(int size);
    Matrix getMinor(int row, int col);
    double getN();
    double getM();

    Matrix operator=(const Matrix& matrix1);
    friend Matrix operator+(Matrix M1, Matrix M2);
    friend Matrix operator*(Matrix M1, Matrix M2);
    friend Matrix operator*(Matrix M1, double num);
    friend Matrix operator*(double num, Matrix M1);
    friend Matrix operator-(Matrix M1, Matrix M2);
    friend ostream &operator<<(ostream &out, Matrix M);
};


#endif //MATRIX_MATRIX_H
