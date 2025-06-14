#include "PosSymLinSystem.h"
#include <cmath>
#include <stdexcept>

/**
 * Constructor for PosSymLinSystem
 * @param A Square symmetric positive definite matrix
 * @param b Vector of constants
 * @throws std::invalid_argument if A is not symmetric positive definite
 */
PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b) : LinearSystem(A, b) {
    if (!A.IsSymmetric()) {
        throw std::invalid_argument("Matrix must be symmetric for PosSymLinSystem");
    }
    
    if (!isPositiveDefinite(A)) {
        throw std::invalid_argument("Matrix must be positive definite");
    }
}

bool PosSymLinSystem::isPositiveDefinite(const Matrix& A) const {
    // Using Sylvester's criterion: all leading principal minors should be positive
    const int n = A.GetNumRows();
    
    for (int k = 1; k <= n; k++) {
        Matrix submatrix(k, k);
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                submatrix(i, j) = A(i, j);
            }
        }
        if (submatrix.Determinant() <= 0) {
            return false;
        }
    }
    return true;
}

bool PosSymLinSystem::isAllEigenvaluesPositive(const Matrix& A) const {
    // Alternative method using Gershgorin circle theorem
    const int n = A.GetNumRows();
    for (int i = 1; i <= n; i++) {
        double diagonal = A(i, i);
        double sum = 0.0;
        
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                sum += std::abs(A(i, j));
            }
        }
        
        // If any Gershgorin disk contains negative values, matrix is not positive definite
        if (diagonal <= sum) {
            return false;
        }
    }
    return true;
}

PosSymLinSystem::~PosSymLinSystem() {}

/**
 * Solves the linear system using Conjugate Gradient method
 * @return Solution vector x
 * @throws std::runtime_error if the method doesn't converge
 */
Vector PosSymLinSystem::Solve() const {
    const Matrix& A = *mpA;
    const Vector& b = *mpb;
    
    Vector x(mSize); // Initial guess (all zeros)
    Vector r = b - A * x;
    Vector p = r;
    
    double rsold = r * r;
    const double tolerance = 1e-10;
    const int maxIterations = mSize * 2;
    
    for (int i = 0; i < maxIterations; i++) {
        Vector Ap = A * p;
        double alpha = rsold / (p * Ap);
        x = x + alpha * p;
        r = r - alpha * Ap;
        
        double rsnew = r * r;
        if (std::sqrt(rsnew) < tolerance) {
            return x; // Convergence achieved
        }
        
        p = r + (rsnew / rsold) * p;
        rsold = rsnew;
    }
    
    throw std::runtime_error("Conjugate Gradient method did not converge");
}