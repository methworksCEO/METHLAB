//
// Created by vik on 3/31/25.
//
#include "cmath"
#include "matrix.h"
Matrix::Matrix(int pRows, int  pCols) : rows(pRows), cols(pCols){
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}
Matrix::Matrix(const Matrix& theOther) : rows(theOther.rows), cols(theOther.cols){
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = theOther.matrix[i][j];
        }
    }
}
Matrix& Matrix::operator=(const Matrix& theOther) {
    if (this == &theOther) return *this;
    rows = theOther.rows;
    cols = theOther.cols;

    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = theOther.matrix[i][j];
        }
    }
    return *this;
}


Matrix Matrix::operator+(const Matrix& theOther) {
    if (rows == theOther.rows && cols == theOther.cols) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.matrix[i][j] = matrix[i][j] + theOther.matrix[i][j];
            }
        }
        return result;
    }
    cout<<"Can't be added";
    return Matrix(0, 0);
}

Matrix Matrix::operator-(const Matrix& theOther) {
    if (rows == theOther.rows && cols == theOther.cols) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.matrix[i][j] = matrix[i][j] - theOther.matrix[i][j];
            }
        }
        return result;
    }
    cout<<"Can't be subtracted";
    return Matrix(0, 0);
}

Matrix Matrix::operator*(const double theScalar) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = matrix[i][j] * theScalar;
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& theOther) {
    if (cols == theOther.rows) {
        Matrix result(rows, theOther.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < theOther.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.matrix[i][j] += matrix[j][k] * theOther.matrix[k][j];
                    result.print();
                }
            }
        }
        return result;
    }
    cout<<"Can't be multiplied";
    return Matrix(0, 0);
}

Matrix Matrix::operator/(const double scalar) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = matrix[i][j] / scalar;
        }
    }
    return result;
}

Matrix Matrix::transp() {
    Matrix result(cols, rows);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            result.matrix[i][j] = matrix[j][i];
        }
    }
    return result;
}

void Matrix::rowSwap(Matrix& M, int row1, int row2) {
    if (row1 >= M.cols || row2 >= M.cols) {
        cout<<"stupid";
        return;
    }

    for (int i = 0; i < M.cols; i++) {
        double temp = M.matrix[row1][i];
        M.matrix[row1][i] = M.matrix[row2][i];
        M.matrix[row2][i] = temp;
    }
}

void Matrix::rowSub(Matrix& M, int row1, int row2, double mul) {
    if (row1 >= M.cols || row2 >= M.cols) {
        cout<<"stupid";
        return;
    }

    for (int i = 0; i < M.cols; i++)
        M.matrix[row2][i] -= mul * M.matrix[row1][i];
}



double Matrix::gauss(bool rref) {
    if (rows != cols) {
        cout<<"Not square matrix"<<endl<<endl;
        return 0;
    }
    Matrix M(rows, cols);
    M.matrix = matrix;
    double det = 1;
    double tempDiv;
    for (int j = 0; j < M.cols; j++) {
        for (int i = j; i < M.rows; i++) {
            if (M.matrix[i][j] != 0) {
                tempDiv = M.matrix[i][j];
                det *= tempDiv;
                for (int k = j; k < M.cols; k++) {
                    M.matrix[i][k] = M.matrix[i][k] / tempDiv;
                }
                if (i != j) {
                    rowSwap(M, i, j);
                    det *= -1;
                }
                for (int l = j+1; l < M.rows; l++) {
                    if (matrix[l][j] != 0) {
                        rowSub(M, j, l, matrix[l][j]);
                    }

                }

            }
        }

    }
    return det;
}

void Matrix::minor(Matrix& min, int delRow, int delCol) {
    int n = 0;
    int m = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i != delRow && j != delCol) {
                min.matrix[n][m] = matrix[i][j];
                m++;
                if (m == min.cols) {
                    m = 0;
                    n++;
                }
            }
        }
    }
}

Matrix Matrix::adj() {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrix temp(rows-1, cols-1);
            minor(temp, i, j);
            if ((i+j)%2 == 0) {
                result.matrix[i][j] = temp.gauss(0);
            }
            else {
                result.matrix[i][j] = -1*temp.gauss(0);
            }
            temp.matrix = nullptr;
        }
    }
    result = result.transp();
    return result;
}

Matrix Matrix::inv() {
    Matrix result(rows, cols);
    result = adj();
    result = result / gauss(0);
    return result;
}

void Matrix::setMatrix(double* values) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[cols * i + j];
        }
    }
}
int Matrix::getRows() {
    return rows;
}
int Matrix::getCols() {
    return cols;
}
double** Matrix::getMatrix() {
    return matrix;
}
void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout<<matrix[i][j]<< " ";
        }
        cout<<"\n";
    }
    cout<<endl;
}
Matrix::~Matrix() {
    delete[] matrix;
};