#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <ostream>
#include <string>
 
using namespace std;
 
 
class BigInt
{
    public:
        BigInt();
        BigInt(std::string);
        BigInt(int x);
        ~BigInt();
        BigInt(const BigInt& another);
        BigInt& operator=(const BigInt& another);
        BigInt operator+(const BigInt& another);
        BigInt operator+(int);
        BigInt& operator++();
        BigInt operator++(int);
        BigInt operator-(const BigInt& another);
        BigInt operator-(int);
        BigInt& operator--();
        BigInt operator--(int);
        BigInt operator*(const BigInt& another);
        BigInt operator*(int);
        BigInt& operator+=(BigInt another);
        BigInt& operator+=(int);
        BigInt& operator-=(int);
        BigInt& operator-=(BigInt another);
        BigInt& operator*=(const BigInt& another);
        BigInt& operator*=(int);
        bool operator==(const BigInt& another);
        bool operator!=(const BigInt& another);
        bool operator<(const BigInt& another);
        bool operator>(const BigInt& another);
        bool operator<=(const BigInt& another);
        bool operator>=(const BigInt& another);
        friend std::ostream& operator<<(std::ostream& output, const BigInt& another);
    protected:
        void swap(BigInt&);
        void add(const BigInt& another);
        void subtract(const BigInt& another);
        bool abs_g_than_equal(const BigInt& another);
    private:
        std::vector<int>_n;
        static const int _base = 100;
        bool positive;
};