#include "Matrix.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>

void Matrix::AllocateMemory() {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
    }
}

void Matrix::DeallocateMemory() {
    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;
}

void Matrix::CopyData(const Matrix& other) {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

Matrix::Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) {}

Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    if (numRows <= 0 || numCols <= 0) throw std::invalid_argument("Matrix dimensions must be positive");
    AllocateMemory();
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    AllocateMemory();
    CopyData(other);
}

Matrix::~Matrix() {
    DeallocateMemory();
}

int Matrix::GetNumRows() const { return mNumRows; }
int Matrix::GetNumCols() const { return mNumCols; }

double& Matrix::operator()(int i, int j) {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) 
        throw std::out_of_range("Matrix index out of range");
    return mData[i-1][j-1];
}

const double& Matrix::operator()(int i, int j) const {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) 
        throw std::out_of_range("Matrix index out of range");
    return mData[i-1][j-1];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        DeallocateMemory();
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        AllocateMemory();
        CopyData(other);
    }
    return *this;
}

Matrix Matrix::operator+() const { return *this; }

Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols)
        throw std::invalid_argument("Matrix dimensions must match");
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols)
        throw std::invalid_argument("Matrix dimensions must match");
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (mNumCols != other.mNumRows)
        throw std::invalid_argument("Matrix dimensions must be compatible for multiplication");
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < other.mNumCols; j++) {
            result.mData[i][j] = 0.0;
            for (int k = 0; k < mNumCols; k++) {
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
            }
        }
    }
    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    if (mNumCols != vec.GetSize())
        throw std::invalid_argument("Matrix and vector dimensions must be compatible");
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < mNumCols; j++) {
            result[i] += mData[i][j] * vec[j];
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::Transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[j][i] = mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::SubMatrix(int excludeRow, int excludeCol) const {
    if (!IsSquare()) throw std::runtime_error("SubMatrix is only for square matrices");
    if (excludeRow < 1 || excludeRow > mNumRows || excludeCol < 1 || excludeCol > mNumCols)
        throw std::out_of_range("Invalid row or column to exclude");
    
    Matrix result(mNumRows-1, mNumCols-1);
    int rowOffset = 0;
    for (int i = 0; i < mNumRows; i++) {
        if (i == excludeRow-1) {
            rowOffset = 1;
            continue;
        }
        int colOffset = 0;
        for (int j = 0; j < mNumCols; j++) {
            if (j == excludeCol-1) {
                colOffset = 1;
                continue;
            }
            result.mData[i-rowOffset][j-colOffset] = mData[i][j];
        }
    }
    return result;
}

double Matrix::Determinant() const {
    if (!IsSquare()) throw std::runtime_error("Matrix must be square to compute determinant");
    
    if (mNumRows == 1) return mData[0][0];
    if (mNumRows == 2) return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    
    double det = 0.0;
    for (int j = 0; j < mNumCols; j++) {
        Matrix subMatrix = SubMatrix(1, j+1);
        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * mData[0][j] * subMatrix.Determinant();
    }
    return det;
}

Matrix Matrix::Inverse() const {
    if (!IsSquare()) throw std::runtime_error("Matrix must be square to compute inverse");
    double det = Determinant();
    if (std::abs(det) < 1e-10) throw std::runtime_error("Matrix is singular (determinant is zero)");
    
    if (mNumRows == 1) {
        Matrix inverse(1, 1);
        inverse(1, 1) = 1.0 / mData[0][0];
        return inverse;
    }
    
    Matrix adjugate(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            Matrix subMatrix = SubMatrix(i+1, j+1);
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            adjugate(j+1, i+1) = sign * subMatrix.Determinant(); // Note the transpose
        }
    }
    
    return adjugate * (1.0 / det);
}

Matrix Matrix::PseudoInverse() const {
    if (mNumRows >= mNumCols) {
        Matrix ATA = Transpose() * (*this);
        Matrix ATAInv = ATA.Inverse();
        return ATAInv * Transpose();
    } else {
        Matrix AAT = (*this) * Transpose();
        Matrix AATInv = AAT.Inverse();
        return Transpose() * AATInv;
    }
}

void Matrix::Print() const {
    std::cout << std::fixed << std::setprecision(4);
    for (int i = 0; i < mNumRows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < mNumCols; j++) {
            std::cout << std::setw(8) << mData[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

bool Matrix::IsSquare() const { return mNumRows == mNumCols; }

bool Matrix::IsSymmetric() const {
    if (!IsSquare()) return false;
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < i; j++) {
            if (std::abs(mData[i][j] - mData[j][i]) > 1e-10) return false;
        }
    }
    return true;
}

Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;
}