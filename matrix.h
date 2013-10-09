#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <ostream>
 
 
class Matrix
{
    public:
        Matrix();
        ~Matrix();
        Matrix(const Matrix& other);
        Matrix(int a, int b);
        Matrix& operator=(const Matrix& other);
        Matrix operator+(const Matrix& other);
        Matrix operator-(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix operator*(double other);
        std::vector<double>& operator[](int i);
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);
        Matrix& operator*=(double other);
        bool operator==(const Matrix& other);
        bool operator!=(const Matrix& other);
        friend std::ostream& operator<<(std::ostream& output, const Matrix& other);
    protected:
    private:
        std::vector< std::vector<double> > _m;
        int _a;
        int _b;
};