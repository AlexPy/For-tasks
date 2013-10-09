#include <iostream>
#include "bigint.h"
 
using namespace std;
 
int main()
    {
        BigInt a;
        BigInt b("-1217");
        BigInt c(1207);
 
        a = c;
        if (a != c) cout << "Something wrong\n";
        else cout << "As expected\n";
 
        if (b < c) cout << "As expected\n";
        else cout << "Something wrong\n";
 
        cout << b++ <<endl;
        cout << ++b <<endl;
        cout << c-1 << endl
             << (b+=7) << endl;
 
        BigInt d(500);
        cout << d + b << endl;
 
        b *= d;
        cout<< b << endl;
        return 0;
    }