#include "bigint.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
 
using namespace std;
 
 
BigInt::BigInt()
{
    positive = true;
}
BigInt::BigInt(std::string s)
{
    positive = true;
    if (s[0] == '-')
    {
        positive = false;
        s.erase(0,1);
    }
    for (size_t i=0; i < s.length(); i++)
        if (i%2)
            _n[i/2] += 10 * (s[s.length()-i-1]-'0');
        else
            _n.push_back(s[s.length()-i-1]-'0');
}
BigInt::BigInt(int x)
{
    positive = true;
    if (x < 0)
    {
        positive = false;
        x = -x;
    }
    while (x)
    {
        _n.push_back(x%_base);
        x/=_base;
    }
}
BigInt::~BigInt()
{
    //dtor
}
 
BigInt::BigInt(const BigInt& another)
{
    this->_n = another._n;
    this->positive = another.positive;
}
 
BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->_n = rhs._n;//assignment operator
    this->positive = rhs.positive;
    return *this;
}
BigInt BigInt::operator+(const BigInt& another)
{
    BigInt result = *this;
    result += another;
    return result;
}
BigInt BigInt::operator+(int x)
{
    BigInt t(x);
    BigInt result;
    result = *this + t;
    return result;
}
BigInt& BigInt::operator++()
{
    BigInt t(1);
    *this += t;
    return *this;
}
 
BigInt BigInt::operator++(int)
{
    BigInt result = *this;
    *this += BigInt(1);
    return result;
}
 
BigInt BigInt::operator-(const BigInt& another)
{
    BigInt result = *this;
    result -= another;
    return result;
}
BigInt BigInt::operator-(int x)
{
    BigInt t(x);
    BigInt result;
    result = *this - t;
    return result;
}
BigInt& BigInt::operator--()
{
    *this -= BigInt(1);
    return *this;
}
BigInt BigInt::operator--(int)
{
    BigInt t(1);
    BigInt result = *this;
    *this -= t;
    return result;
}
BigInt BigInt::operator*(const BigInt& another)
{
    BigInt c;
    for(size_t i = 0; i < this->_n.size() + another._n.size(); i++)
        c._n.push_back(0);
    int t;
    int d;
    for (size_t i = 0; i < this->_n.size(); i++)
    {
        for (size_t j = 0; j < another._n.size(); j++)
        {
            t = c._n[i+j] + this->_n[i]*another._n[j];
            c._n[i+j] = t%_base;
            d = t/_base;
            c._n[i+j+1] = d;
        }
    }
    for (size_t i = c._n.size() - 1; (i >= 0) and (c._n[i] == 0); i--)
        c._n.pop_back();
    c.positive = (this->positive == another.positive);
    return c;
}
BigInt BigInt::operator*(int x)
{
    BigInt t(x);
    BigInt result;
    result = *this * t;
    return result;
}
BigInt& BigInt::operator+=(BigInt another)
{
    if ((this->positive == true) && (another.positive == true))
    {
        this->plus(another);
        return *this;
    }
    if ((this->positive == true) && (another.positive != true) && (this->abs_gte(another)))
    {
        this->minus(another);
        return *this;
    }
    if ((this->positive == true) && (another.positive != true) && (!(this->abs_gte(another))))
    {
         this->swap(another);
         this->minus(another);
         return *this;
    }
    if ((this->positive != true) && (another.positive == true)&& (!(this->abs_gte(another))))
    {
         this->swap(another);
         this->minus(another);
         return *this;
    }
    if ((this->positive != true) && (another.positive == true)&& (this->abs_gte(another)))
    {
        this->minus(another);
        return *this;
    }
    if ((this->positive != true) && (another.positive != true))
    {
        this->plus(another);
        return *this;
    }
 
}
BigInt& BigInt::operator+=(int x)
{
    BigInt t(x);
    *this += t;
    return *this;
}
BigInt& BigInt::operator-=(BigInt another)
{
    if ((this->positive == true) && (another.positive == true)&& (!(this->abs_gte(another))))
    {
         this->swap(another);
         this->minus(another);
         return *this;
    }
    if ((this->positive == true) && (another.positive == true)&& (this->abs_gte(another)))
    {
        this->minus(another);
        return *this;
    }
    if ((this->positive == true) && (another.positive != true))
    {
        this->plus(another);
        return *this;
    }
    if ((this->positive != true) && (another.positive == true))
    {
        this->plus(another);
        return *this;
    }
    if ((this->positive != true) && (another.positive != true)&& (!(this->abs_gte(another))))
    {
         this->swap(another);
         this->minus(another);
         this->positive = true;
         return *this;
    }
    if ((this->positive != true) && (another.positive != true)&& (this->abs_gte(another)))
    {
        this->minus(another);
        return *this;
    }
 
}
BigInt& BigInt::operator-=(int x)
{
    BigInt t(x);
    *this -=  t;
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& another)
{
    *this = (*this) * other;
    return *this;
}
BigInt& BigInt::operator*=(int x)
{
    BigInt t(x);
    *this = (*this) * t;
    return *this;
}
bool BigInt::operator==(const BigInt& another)
{
    if (this->_n.size() != another._n.size()) return false;
    if (this->positive != another.positive) return false;
    for (size_t i = 0; i < another._n.size(); i++)
        {
            if (this->_n[i]!=another._n[i]) return false;
        }
    return true;
}
bool BigInt::operator!=(const BigInt& another)
{
    return !((*this) == another);
}
bool BigInt::operator<(const BigInt& another)
{
    if ((this->positive == true) && (another.positive == true)&& (this->abs_gte(another))) return false;
    if ((this->positive == true) && (another.positive != true) ) return false;
    if ((this->positive != true) && (another.positive != true)&& (!(this->abs_gte(another)))) return false;
    return true;
}
bool BigInt::operator>(const BigInt& another)
{
    return !((*this == another) && (*this < another));
}
bool BigInt::operator<=(const BigInt& another)
{
   return !(*this > another);
}
bool BigInt::operator>=(const BigInt& another)
{
    return !(*this < another);
}
void BigInt::swap(BigInt& another)
{
    std::swap(this->_n, another._n);
    std::swap(this->positive, another.positive);
}
void BigInt::add(const BigInt& another)
{
    int carry = 0;
    for (size_t i=0; i < std::max(this->_n.size(),another._n.size()) || carry; ++i) {
        if (i == this->_n.size())
            this->_n.push_back (0);
        this->_n[i] += carry + (i < another._n.size() ? another._n[i] : 0);
        carry = this->_n[i] >= _base;
        if (carry)  this->_n[i] -= _base;
    }
}
void BigInt::subtract(const BigInt& another)
{
    int carry = 0;
    for (size_t i=0; i<another._n.size() || carry; ++i) {
        this->_n[i] -= carry + (i < another._n.size() ? another._n[i] : 0);
        carry = this->_n[i] < 0;
        if (carry)  this->_n[i] += _base;
    }
    while (this->_n.size() > 1 && this->_n.back() == 0)
        this->_n.pop_back();
}
 
bool BigInt::abs_g_than_equal(const BigInt& another)
{
    if (this->_n.size()<another._n.size()) return false;
    if (this->_n.size()>another._n.size()) return true;
    else
    {
        for (size_t i = 0; i < std::max(this->_n.size(),another._n.size()); i++)
        {
            if (this->_n[i] < another._n[i]) return false;
        }
    return true;
    }
}
std::ostream& operator<<(std::ostream& output, const BigInt& another)
{
    if (another.positive == 0) cout<<'-';
    output << another._n[another._n.size()-1];
    for (size_t i = 1; i < another._n.size(); i++)
    {
        cout<<setfill('0')<<setw(2)<<another._n[another._n.size()-i-1];
 
    }
    return output;
}