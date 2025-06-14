#include "LinearSystem.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

/**
 * Constructor for LinearSystem
 * @param A Square matrix of coefficients
 * @param b Vector of constants
 * @throws std::invalid_argument if A is not square or dimensions don't match
 * @throws std::runtime_error if memory allocation fails
 */
LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    if (!A.IsSquare()) {
        throw std::invalid_argument("Matrix A must be square");
    }
    if (A.GetNumRows() != b.GetSize()) {
        throw std::invalid_argument("Matrix A and vector b must have compatible dimensions");
    }
    
    try {
        mSize = A.GetNumRows();
        mpA = new Matrix(A);
        mpb = new Vector(b);
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Memory allocation failed in LinearSystem constructor: " + std::string(e.what()));
    }
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

/**
 * Solves the linear system Ax = b using Gaussian elimination with partial pivoting
 * @return Solution vector x
 * @throws std::runtime_error if the matrix is singular or nearly singular
 */
Vector LinearSystem::Solve() const {
    // Check if the system is well-defined
    if (mSize == 0 || !mpA || !mpb) {
        throw std::runtime_error("Linear system is not properly initialized");
    }

    const double epsilon = 1e-10;  // Threshold for considering a matrix singular
    
    // Create copies for manipulation
    Matrix A(*mpA);
    Vector b(*mpb);
    
    // Gaussian elimination with partial pivoting
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
        
        // Check for singular matrix
        if (maxVal < epsilon) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }
        
        // Swap rows if necessary
        if (maxRow != k) {
            for (int j = k; j <= mSize; j++) {
                std::swap(A(k, j), A(maxRow, j));
            }
            std::swap(b(k), b(maxRow));
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