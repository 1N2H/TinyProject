#include "Vector.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Vector::Vector() : mSize(0), mData(nullptr) {}

Vector::Vector(int size) : mSize(size) {
    if (size < 0) throw std::invalid_argument("Vector size must be non-negative");
    mData = new double[size];
    for (int i = 0; i < size; i++) mData[i] = 0.0;
}

Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

int Vector::GetSize() const { return mSize; }

double& Vector::operator()(int i) {
    if (i < 1 || i > mSize) throw std::out_of_range("Vector index out of range");
    return mData[i-1];
}

const double& Vector::operator()(int i) const {
    if (i < 1 || i > mSize) throw std::out_of_range("Vector index out of range");
    return mData[i-1];
}

double& Vector::operator[](int i) {
    if (i < 0 || i >= mSize) throw std::out_of_range("Vector index out of range");
    return mData[i];
}

const double& Vector::operator[](int i) const {
    if (i < 0 || i >= mSize) throw std::out_of_range("Vector index out of range");
    return mData[i];
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
    }
    return *this;
}

Vector Vector::operator+() const { return *this; }

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result.mData[i] = -mData[i];
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    if (mSize != other.mSize) throw std::invalid_argument("Vector sizes must match");
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result.mData[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (mSize != other.mSize) throw std::invalid_argument("Vector sizes must match");
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result.mData[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result.mData[i] = mData[i] * scalar;
    return result;
}

double Vector::operator*(const Vector& other) const {
    if (mSize != other.mSize) throw std::invalid_argument("Vector sizes must match");
    double result = 0.0;
    for (int i = 0; i < mSize; i++) result += mData[i] * other.mData[i];
    return result;
}

double Vector::Norm() const {
    return std::sqrt((*this) * (*this));
}

void Vector::Print() const {
    std::cout << "[ ";
    for (int i = 0; i < mSize; i++) std::cout << mData[i] << " ";
    std::cout << "]" << std::endl;
}

Vector operator*(double scalar, const Vector& vec) {
    return vec * scalar;
}