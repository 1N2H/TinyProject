#include "PosSymLinSystem.h"
#include <cmath>
#include <stdexcept>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b) : LinearSystem(A, b) {
    if (!A.IsSymmetric()) {
        throw std::invalid_argument("Matrix must be symmetric for PosSymLinSystem");
    }
}

PosSymLinSystem::~PosSymLinSystem() {}

Vector PosSymLinSystem::Solve() const {
    // Conjugate Gradient method
    const Matrix& A = *mpA;
    const Vector& b = *mpb;
    
    Vector x(mSize); // Initial guess (all zeros)
    Vector r = b - A * x;
    Vector p = r;
    
    double rsold = r * r;
    
    for (int i = 0; i < mSize; i++) {
        Vector Ap = A * p;
        double alpha = rsold / (p * Ap);
        x = x + alpha * p;
        r = r - alpha * Ap;
        
        double rsnew = r * r;
        if (std::sqrt(rsnew) < 1e-10) {
            break; // Convergence
        }
        
        p = r + (rsnew / rsold) * p;
        rsold = rsnew;
    }
    
    return x;
}