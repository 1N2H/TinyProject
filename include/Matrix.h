#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <vector>

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

    void AllocateMemory();
    void DeallocateMemory();
    void CopyData(const Matrix& other);

public:
    // Constructors and destructor
    Matrix();
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();

    // Accessors
    int GetNumRows() const;
    int GetNumCols() const;
    double& operator()(int i, int j);              // 1-based indexing
    const double& operator()(int i, int j) const; // 1-based indexing const version

    // Assignment operator
    Matrix& operator=(const Matrix& other);

    // Unary operators
    Matrix operator+() const;
    Matrix operator-() const;

    // Binary operators
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& vec) const;
    Matrix operator*(double scalar) const;

    // Matrix operations
    Matrix Transpose() const;
    double Determinant() const;
    Matrix Inverse() const;
    Matrix PseudoInverse() const;
    Matrix SubMatrix(int excludeRow, int excludeCol) const;

    // Utility functions
    void Print() const;
    bool IsSquare() const;
    bool IsSymmetric() const;
};

// Non-member function for scalar multiplication
Matrix operator*(double scalar, const Matrix& mat);

#endif // MATRIX_H