//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include  <limits.h>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

int greatestCommonDenominator(const int, const int);
int leastCommonMultiple(const int, const int);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

int greatestCommonDenominator(const int a, const int b) {
    int t;
    int m = 0;
    int n = 0;
    if (a < b )
    {
        m = b;
        n = a;
    }
    else
    {
        m = a;
        n = b;
    };
    if ( m <= 0 || n <= 0 )
    {
        return -1;
    };
    while (n != 0)
    {
        t = m % n;
        m = n;
        n = t;
    };
    return m;
}

int leastCommonMultiple (const int a, const int b) {
    if ( a <= 0 || b <= 0 )
    {
        return -1;
    };
    int lcm = a / greatestCommonDenominator(a, b) * b;
    if ( a / greatestCommonDenominator(a,b) > INT_MAX/b)
    {
        return -2;
    };
    return lcm;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {

  if (argc < 3) {
    cerr << "Error: Usage: " << argv[0] << "<num1> <num2>; exiting" << endl;
    return -1;
  }

  int gcd = greatestCommonDenominator(atoi(argv[1]),atoi(argv[2]));
  if (gcd < 0)
    cerr << "Unable to compute GCD(" << argv[1] << "," << argv[2] << ")" << endl;
  else
    cout << "GCD(" << argv[1] << "," << argv[2] << ") = " << gcd << endl;

  int lcm = leastCommonMultiple(atoi(argv[1]),atoi(argv[2]));
  if (lcm < 0)
    cerr << "Unable to compute LCM(" << argv[1] << "," << argv[2] << ")" << endl;
  else
    cout << "LCM(" << argv[1] << "," << argv[2] << ") = " << lcm << endl;


  return 0;
}

#endif
