#include <iostream>
#include "Matrix.h"

Matrix::Matrix() {
    n = m = 0;
}

Matrix::Matrix(int _n, int _m) {
    n = _n;
    m = _m;

    matrix = new double * [n];

    for (int i = 0; i < n; i++) {
        matrix[i] = new double [m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &M) {
    m = M.m;
    n = M.n;

    matrix = (double**) new double*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = (double*) new double[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = M.matrix[i][j];
        }
    }
}

Matrix::Matrix(int _n, int _m, double **array) {
    n = _n;
    m = _m;
    matrix = new double*[n];

    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = array[i][j];
        }
    }
}

double Matrix::getByIndex(int i, int j) {
    if (0 <= i < n && 0 <= j < m) {
        return matrix[i][j];
    }
    else {
        return 0;
    }
}

void Matrix::setByIndex(int i, int j, double value) {
    if (0 <= i < n && 0 <= j < m) {
        matrix[i][j] = value;
    }
}

Matrix Matrix::operator=(const Matrix& M) {
    if (m > 0) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
    }
    if (n > 0) {
        delete[] matrix;
    }

    n = M.n;
    m = M.m;

    matrix = (double**) new double*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = (double*) new double[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = M.matrix[i][j];
        }
    }
    return *this;
}

Matrix::~Matrix() {
    if (m > 0) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
    }
    if (n > 0) {
        delete[] matrix;
    }
}


ostream& operator<<(ostream &out, Matrix M) {
    for (int i = 0; i < M.getN(); i++)
    {
        for (int j = 0; j < M.getM(); j++)
            cout << M.getByIndex(i, j) << "\t";
        cout << endl;
    }
}

double Matrix::getN() {
    return n;
}

double Matrix::getM() {
    return m;
}

Matrix operator+(Matrix M1, Matrix M2) {
    if (M1.getN() == M2.getN() && M1.getM() == M2.getM()) {
        Matrix M(M1.getN(), M1.getM());
        for (int i = 0; i < M1.getN(); ++i) {
            for (int j = 0; j < M1.getM(); ++j) {
                M.setByIndex(i, j, M1.getByIndex(i, j) + M2.getByIndex(i, j));
            }
        }
        return M;
    }
}

Matrix operator*(Matrix M1, double num) {
    Matrix M(M1);
    for (int i = 0; i < M.getN(); ++i) {
        for (int j = 0; j < M.getM(); ++j) {
            M.setByIndex(i, j, M.getByIndex(i, j) * num);
        }
    }
    return M;
}

Matrix operator-(Matrix M1, Matrix M2) {
    if (M1.getN() == M2.getN() && M1.getM() == M2.getM()) {
        Matrix M(M1.getN(), M1.getM());
        M = M1 + M2 * (-1);
        return M;
    }
}

Matrix operator*(Matrix M1, Matrix M2) {
    if (M1.getM() == M2.getN()){
        Matrix M(M1.getN(), M2.getM());
        for (int i = 0; i < M1.getN(); ++i) {
            for (int j = 0; j < M2.getM(); ++j) {
                M.setByIndex(i, j, 0);
                for (int k = 0; k < M1.getM(); ++k) {
                    M.setByIndex(i, j, M.getByIndex(i, j) + M1.getByIndex(i, k) * M2.getByIndex(k, j));
                }
            }
        }
        return M;
    }
}

Matrix operator*(double num, Matrix M1) {
    return M1 * num;
}

Matrix Matrix::transpose() {
    Matrix M(this->getM(), this->getN());
    for (int i = 0; i < M.getN(); i++)
    {
        for (int j = 0; j < M.getM(); j++) {
            M.setByIndex(i, j, this->getByIndex(j, i));
        }
    }
    return M;
}

Matrix Matrix::getInverse(int size) {
    Matrix M = *this;
    Matrix inverse(M.getN(), M.getM());
    double det = M.getDeterminant(size);
    if (M.getN() == M.getM() && M.getDeterminant(size) != 0) {
        for (int i = 0; i < inverse.getN(); ++i) {
            for (int j = 0; j < inverse.getM(); ++j) {
                int odd;
                if ((i + j) % 2 == 0) {
                    odd = 1;
                }
                else {
                    odd = -1;
                }
                inverse.setByIndex(i, j, odd * M.getMinor(i, j).getDeterminant(size));
            }
        }
    }
    inverse = inverse.transpose();
    return 1 / det * inverse;
}

double Matrix::getDeterminant(int size) {
    Matrix M = *this;
    double det;
    int degree = 1;
    if (M.getN() == M.getM()) {
        if(M.getN() == 1) {
            det = M.getByIndex(0, 0);
        }
        else if (M.getN() == 2) {
            det = M.getByIndex(0,0) * M.getByIndex(1,1) - M.getByIndex(0,1) * M.getByIndex(1,0);
        }
        else {
            Matrix minor;
            for(int j = 0; j < size; j++) {
                minor = M.getMinor(0, j);
                det = det + (degree * M.getByIndex(0, j) * minor.getDeterminant(size - 1));
                degree = -degree;
            }
        }
    }
    return det;
}

Matrix Matrix::getMinor(int row, int col) {
    Matrix M = *this;
    Matrix minor(M.getN() - 1, M.getM() - 1);
    int rowReached = 0;
    int colReached = 0;
    for (int i = 0; i < minor.getN(); ++i) {
        if (i == row) {
            rowReached = 1;
        }
        colReached = 0;
        for (int j = 0; j < minor.getM(); ++j) {
            if (j == col) {
                colReached = 1;
            }
            minor.setByIndex(i, j, M.getByIndex(i + rowReached, j + colReached));
        }
    }
    return minor;
}
