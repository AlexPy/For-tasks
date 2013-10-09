#include "matrix.h"
#include <stdexcept>
 
Matrix::Matrix()
{
    //ctor
}
Matrix::Matrix(int a, int b)
{
    this->_a = a;
    this->_b = b;
    for (int i = 0; i < b; i++)
    {
        std::vector<double> temp = std::vector<double>(a, 0);
        this->_m.push_back(temp);
    }
}
Matrix::~Matrix()
{
    //dtor
}
 
Matrix::Matrix(const Matrix& other)
{
    this->_m = other._m;
    this->_a = other._a;
    this->_b = other._b;
}
 
Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->_m = rhs._m;//assignment operator
    this->_a = rhs._a;
    this->_b = rhs._b;
    return *this;
}
Matrix& Matrix::operator+=(const Matrix& rhs)
{
    if (!((this->_a == rhs._a) && (this->_b == rhs._b)))
        throw std::length_error("Размерности матриц не совпадают");
    for (int i = 0; i < this->_b; i++)
    {
        for (int j = 0; j < this->_a; j++)
        {
            this->_m[i][j]+=rhs._m[i][j];
        }
    }
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& rhs)
{
    if (!((this->_a == rhs._a) && (this->_b == rhs._b)))
        throw std::length_error("Размерности матриц не совпадают");
    for (int i = 0; i < this->_b; i++)
    {
        for (int j = 0; j < this->_a; j++)
        {
            this->_m[i][j]-=rhs._m[i][j];
        }
    }
    return *this;
}
 
 
Matrix& Matrix::operator*=(const Matrix& rhs)
{
    *this = (*this) * rhs;
    return *this;
}
 
 
Matrix& Matrix::operator*=(double other)
{
    for (int i = 0; i < this->_b; i++)
    {
        for (int j = 0; j < this->_a; j++)
        {
            this->_m[i][j]*=other;
        }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& other)
{
    Matrix result = *this;
    result += other;
    return result;
 
}
 
Matrix Matrix::operator-(const Matrix& other)
{
    Matrix result = *this;
    result -= other;
    return result;
}
 
Matrix Matrix::operator*(const Matrix& other)
{
    if (!(this->_a == other._b))
        throw std::length_error("Размерности матриц не совпадают");
    Matrix result(other._a, this->_b);
    for (int i = 0; i < this->_b; i++)
    {
        for (int j = 0; j < other._a; j++)
        {
          for (int k = 0; k < other._b; k++)
          {
          result[i][j] += this->_m[i][k]*other._m[k][j];
          }
 
        }
    }
    return result;
}
 
Matrix Matrix::operator*(double other)
{
    Matrix result = *this;
    result *= other;
    return result;
}
 
std::vector<double>& Matrix::operator[](int i)
{
    return this->_m[i];
}
 
bool Matrix::operator==(const Matrix& rhs)
{
   for (int i = 0; i < this->_b; i++)
    {
        for (int j = 0; j < this->_a; j++)
        {
            if (this->_m[i][j]!=rhs._m[i][j]) return false;
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix& rhs)
{
    return !(*this == rhs);
}
 
std::ostream& operator<<(std::ostream& out, const Matrix& rhs)
{
    for (int i = 0; i < rhs._b; i++)
    {
        for (int j = 0; j < rhs._a; j++)
        {
            out << rhs._m[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}