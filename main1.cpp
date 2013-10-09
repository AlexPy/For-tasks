#include <iostream>
#include "matrix.h"
 
using namespace std;
 
int main()
{
    Matrix a;
    Matrix b(2,2);
    Matrix c(3,3);
 
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) b[i][j] = i+j;
 
    cout << b;
    b *= 2;
    b = a = b + b;
    a*=b;
 
    if (a != b) cout << "Something wrong\n";
    else cout << "As expected\n";
 
    //b += c;   // эта строчка работать не должна, потому что матрицы
        // разной размерности складывать нельзя.
 
    cout << a << endl
        << c << endl
        << b << endl;
 
    return 0;
}