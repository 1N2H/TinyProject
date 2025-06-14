# Tiny Project: Linear Algebra & CPU Performance Regression

## Overview

This project implements:

- A linear algebra library (Vector, Matrix, LinearSystem classes)
- CPU performance prediction using linear regression on UCI's Computer Hardware dataset

### Requirements

- C++ compiler (g++/MinGW)
- Make utility

## Features

### Part A: Linear Algebra Library

- Vector and Matrix operations
- Linear system solver (Gaussian elimination)
- Positive definite system solver (Conjugate gradient)

### Part B: Linear Regression

- Predicts CPU performance (PRP) using 6 hardware features
- 80/20 train-test split
- Reports RMSE metrics

## Getting Started

### Dataset Setup

1. Download the Computer Hardware dataset from UCI:
   [Computer Hardware Dataset](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
2. Place the `machine.data` file in the `data/` folder

### Building the Project

#### Using Makefile

```bash
# On Linux/Mac:
make

# On Windows:
mingw32-make

# Run the program:
./tinyProject
```

#### Manual Compilation

```bash
g++ -std=c++11 -Iinclude src/*.cpp main.cpp -o tinyProject
./tinyProject
```

### Example Output

```plaintext
Regression coefficients:
MYCT: -0.012, MMIN: 0.005, MMAX: 0.003
CACH: 0.821, CHMIN: -0.104, CHMAX: 0.542

Training RMSE: 25.34
Testing RMSE: 28.71
```

## Project Structure

```plaintext
tinyProject/
├── include/       # Header files
├── src/          # Source code
├── data/         # Dataset
└── Makefile      # Build script
```

## Troubleshooting

- On Windows: Use `mingw32-make` instead of `make`
- Ensure `machine.data` exists in `data/` folder
- Requires C++11 support

## Links

- GitHub: [https://github.com/1N2H](https://github.com/1N2H)

---
