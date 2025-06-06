#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cmath>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"
#include "PosSymLinSystem.h"

struct ComputerHardware {
    std::string vendorName;
    std::string modelName;
    int MYCT;    // machine cycle time in nanoseconds
    int MMIN;    // minimum main memory in kilobytes
    int MMAX;    // maximum main memory in kilobytes
    int CACH;    // cache memory in kilobytes
    int CHMIN;   // minimum channels in units
    int CHMAX;   // maximum channels in units
    int PRP;     // published relative performance
    int ERP;     // estimated relative performance
};

std::vector<ComputerHardware> readData(const std::string& filename) {
    std::vector<ComputerHardware> data;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        ComputerHardware item;
        std::string token;
        
        // Vendor name
        std::getline(iss, item.vendorName, ',');
        
        // Model name
        std::getline(iss, item.modelName, ',');
        
        // Numerical values
        std::getline(iss, token, ',');
        item.MYCT = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.MMIN = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.MMAX = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.CACH = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.CHMIN = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.CHMAX = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.PRP = std::stoi(token);
        
        std::getline(iss, token, ',');
        item.ERP = std::stoi(token);
        
        data.push_back(item);
    }
    
    return data;
}

void splitData(const std::vector<ComputerHardware>& data, 
               std::vector<ComputerHardware>& trainData, 
               std::vector<ComputerHardware>& testData, 
               double trainRatio = 0.8) {
    std::vector<ComputerHardware> shuffledData = data;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledData.begin(), shuffledData.end(), g);
    
    size_t trainSize = static_cast<size_t>(data.size() * trainRatio);
    trainData.assign(shuffledData.begin(), shuffledData.begin() + trainSize);
    testData.assign(shuffledData.begin() + trainSize, shuffledData.end());
}

Matrix createDesignMatrix(const std::vector<ComputerHardware>& data) {
    Matrix X(data.size(), 6);
    for (size_t i = 0; i < data.size(); i++) {
        X(i+1, 1) = data[i].MYCT;
        X(i+1, 2) = data[i].MMIN;
        X(i+1, 3) = data[i].MMAX;
        X(i+1, 4) = data[i].CACH;
        X(i+1, 5) = data[i].CHMIN;
        X(i+1, 6) = data[i].CHMAX;
    }
    return X;
}

Vector createTargetVector(const std::vector<ComputerHardware>& data) {
    Vector y(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        y(i+1) = data[i].PRP;
    }
    return y;
}

double calculateRMSE(const Vector& predicted, const Vector& actual) {
    if (predicted.GetSize() != actual.GetSize()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    
    double sum = 0.0;
    for (int i = 1; i <= predicted.GetSize(); i++) {
        double diff = predicted(i) - actual(i);
        sum += diff * diff;
    }
    
    return std::sqrt(sum / predicted.GetSize());
}

int main() {
    try {
        // Part A: Test Vector, Matrix, and LinearSystem classes
        std::cout << "=== Testing Vector Class ===" << std::endl;
        Vector v1(3);
        v1(1) = 1.0; v1(2) = 2.0; v1(3) = 3.0;
        Vector v2(3);
        v2(1) = 4.0; v2(2) = 5.0; v2(3) = 6.0;
        
        std::cout << "v1: "; v1.Print();
        std::cout << "v2: "; v2.Print();
        std::cout << "v1 + v2: "; (v1 + v2).Print();
        std::cout << "v1 * v2: " << (v1 * v2) << std::endl;
        
        std::cout << "\n=== Testing Matrix Class ===" << std::endl;
        Matrix m1(2, 2);
        m1(1, 1) = 1.0; m1(1, 2) = 2.0;
        m1(2, 1) = 3.0; m1(2, 2) = 4.0;
        
        Matrix m2(2, 2);
        m2(1, 1) = 5.0; m2(1, 2) = 6.0;
        m2(2, 1) = 7.0; m2(2, 2) = 8.0;
        
        std::cout << "m1:\n"; m1.Print();
        std::cout << "m2:\n"; m2.Print();
        std::cout << "m1 + m2:\n"; (m1 + m2).Print();
        std::cout << "m1 * m2:\n"; (m1 * m2).Print();
        std::cout << "Determinant of m1: " << m1.Determinant() << std::endl;
        std::cout << "Inverse of m1:\n"; m1.Inverse().Print();
        
        std::cout << "\n=== Testing LinearSystem Class ===" << std::endl;
        Matrix A(3, 3);
        A(1, 1) = 1.0; A(1, 2) = 2.0; A(1, 3) = 3.0;
        A(2, 1) = 4.0; A(2, 2) = 5.0; A(2, 3) = 6.0;
        A(3, 1) = 7.0; A(3, 2) = 8.0; A(3, 3) = 10.0;
        
        Vector b(3);
        b(1) = 6.0; b(2) = 15.0; b(3) = 25.0;
        
        LinearSystem system(A, b);
        Vector x = system.Solve();
        std::cout << "Solution x: "; x.Print();
        
        // Part B: Linear Regression
        std::cout << "\n=== Part B: Linear Regression ===" << std::endl;
        
        // Read data
        std::vector<ComputerHardware> data = readData("data/machine.data");
        std::cout << "Total instances: " << data.size() << std::endl;
        
        // Split into training and testing sets
        std::vector<ComputerHardware> trainData, testData;
        splitData(data, trainData, testData);
        std::cout << "Training set size: " << trainData.size() << std::endl;
        std::cout << "Testing set size: " << testData.size() << std::endl;
        
        // Create design matrix and target vector for training
        Matrix X_train = createDesignMatrix(trainData);
        Vector y_train = createTargetVector(trainData);
        
        // Solve the linear system X'Xβ = X'y using normal equations
        Matrix XTX = X_train.Transpose() * X_train;
        Vector XTy = X_train.Transpose() * y_train;
        
        // Solve using LinearSystem (Gaussian elimination)
        LinearSystem normalSystem(XTX, XTy);
        Vector beta = normalSystem.Solve();
        
        std::cout << "\nRegression coefficients (using normal equations):\n";
        std::cout << "MYCT: " << beta(1) << std::endl;
        std::cout << "MMIN: " << beta(2) << std::endl;
        std::cout << "MMAX: " << beta(3) << std::endl;
        std::cout << "CACH: " << beta(4) << std::endl;
        std::cout << "CHMIN: " << beta(5) << std::endl;
        std::cout << "CHMAX: " << beta(6) << std::endl;
        
        // Evaluate on training set
        Vector y_train_pred = X_train * beta;
        double trainRMSE = calculateRMSE(y_train_pred, y_train);
        std::cout << "\nTraining RMSE: " << trainRMSE << std::endl;
        
        // Evaluate on testing set
        Matrix X_test = createDesignMatrix(testData);
        Vector y_test = createTargetVector(testData);
        Vector y_test_pred = X_test * beta;
        double testRMSE = calculateRMSE(y_test_pred, y_test);
        std::cout << "Testing RMSE: " << testRMSE << std::endl;
        
        // Solve using pseudo-inverse (for potentially ill-conditioned systems)
        Matrix X_pseudo = X_train.PseudoInverse();
        Vector beta_pseudo = X_pseudo * y_train;
        
        std::cout << "\nRegression coefficients (using pseudo-inverse):\n";
        std::cout << "MYCT: " << beta_pseudo(1) << std::endl;
        std::cout << "MMIN: " << beta_pseudo(2) << std::endl;
        std::cout << "MMAX: " << beta_pseudo(3) << std::endl;
        std::cout << "CACH: " << beta_pseudo(4) << std::endl;
        std::cout << "CHMIN: " << beta_pseudo(5) << std::endl;
        std::cout << "CHMAX: " << beta_pseudo(6) << std::endl;
        
        // Evaluate pseudo-inverse solution on testing set
        Vector y_test_pred_pseudo = X_test * beta_pseudo;
        double testRMSE_pseudo = calculateRMSE(y_test_pred_pseudo, y_test);
        std::cout << "\nTesting RMSE (pseudo-inverse): " << testRMSE_pseudo << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}