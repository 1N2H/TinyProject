#include "LinearSystem.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    if (!A.IsSquare()) throw std::invalid_argument("Matrix A must be square");
    if (A.GetNumRows() != b.GetSize()) throw std::invalid_argument("Matrix A and vector b must have compatible dimensions");
    
    mSize = A.GetNumRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() const {
    // Gaussian elimination with partial pivoting
    Matrix A(*mpA);
    Vector b(*mpb);
    
    for (int k = 1; k <= mSize; k++) {
        // Partial pivoting
        int maxRow = k;
        double maxVal = std::abs(A(k, k));
        for (int i = k+1; i <= mSize; i++) {
            if (std::abs(A(i, k)) > maxVal) {
                maxVal = std::abs(A(i, k));
                maxRow = i;
            }
        }
        
        // Swap rows if necessary
        if (maxRow != k) {
            for (int j = k; j <= mSize; j++) {
                std::swap(A(k, j), A(maxRow, j));
            }
            std::swap(b(k), b(maxRow));
        }
        
        // Check for singular matrix
        if (std::abs(A(k, k)) < 1e-10) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }
        
        // Elimination
        for (int i = k+1; i <= mSize; i++) {
            double factor = A(i, k) / A(k, k);
            for (int j = k; j <= mSize; j++) {
                A(i, j) -= factor * A(k, j);
            }
            b(i) -= factor * b(k);
        }
    }
    
    // Back substitution
    Vector x(mSize);
    for (int i = mSize; i >= 1; i--) {
        double sum = 0.0;
        for (int j = i+1; j <= mSize; j++) {
            sum += A(i, j) * x(j);
        }
        x(i) = (b(i) - sum) / A(i, i);
    }
    
    return x;
}