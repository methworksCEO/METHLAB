//
// Created by vik on 3/31/25.
//

#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
using namespace std;

class Matrix{
    int rows;
    int cols;
    double** matrix;
public:
    Matrix(int, int);
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix&);
    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(double);
    Matrix operator*(const Matrix&);
    Matrix operator/(double);
    double gauss(bool);
    void rowSwap(Matrix&, int, int);
    void rowSub(Matrix&, int, int, double);
    Matrix transp();
    void minor(Matrix&, int, int);
    Matrix adj();
    Matrix inv();
    void setMatrix(double*);
    int getRows();
    int getCols();
    double** getMatrix();
    void print();
    ~Matrix();
};



#endif //MATRIX_H
