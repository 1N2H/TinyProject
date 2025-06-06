#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructors and destructor
    Vector();
    Vector(int size);
    Vector(const Vector& other);
    ~Vector();

    // Accessors
    int GetSize() const;
    double& operator()(int i);              // 1-based indexing
    const double& operator()(int i) const; // 1-based indexing const version
    double& operator[](int i);             // 0-based indexing with bounds checking
    const double& operator[](int i) const; // 0-based indexing const version

    // Assignment operator
    Vector& operator=(const Vector& other);

    // Unary operators
    Vector operator+() const;
    Vector operator-() const;

    // Binary operators
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    double operator*(const Vector& other) const; // Dot product

    // Other operations
    double Norm() const;
    void Print() const;
};

// Non-member function for scalar multiplication
Vector operator*(double scalar, const Vector& vec);

#endif // VECTOR_H