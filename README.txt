Tiny Project: Linear Algebra & CPU Performance Regression
I.Overview:
This project implements: 
A linear algebra library (Vector, Matrix, LinearSystem classes)
CPU performance prediction using linear regression on UCI's Computer Hardware dataset
Requirements:
1.C++ compiler (g++/MinGW)
2.Make utility
Download dataset:
Place machine.data in data/ folder from:
https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware

II.Build & Run:
Using Makefile:
make or mingw32-make
./tinyProject
Manual compilation:
g++ -std=c++11 -Iinclude src/*.cpp main.cpp -o tinyProject
./tinyProject

III.Features:
1.Part A: Linear Algebra Library
Vector and Matrix operations
Linear system solver (Gaussian elimination)
Positive definite system solver (Conjugate gradient)

2.Part B: Linear Regression
Predicts CPU performance (PRP) using 6 hardware features
80/20 train-test split
Reports RMSE metrics
Output Example
Regression coefficients:

MYCT: -0.012, MMIN: 0.005, MMAX: 0.003  
CACH: 0.821, CHMIN: -0.104, CHMAX: 0.542

Training RMSE: 25.34
Testing RMSE: 28.71

Directory Structure
tinyProject/
├── include/       # Header files
├── src/           # Source code
├── data/          # Dataset
└── Makefile       # Build script

Troubleshooting
On Windows: Use mingw32-make instead of make
Ensure machine.data exists in data/ folder
Requires C++11 support


Github: https://github.com/1N2H

