#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h> 

using namespace std;

int main( const int argc, const char * const argv[]) {
    int x;
    int i;
    int msb;
    int msb2;
    unsigned int y;
    x = atoi(argv[1]);
    y = x;
    msb = abs(x >> (8 * sizeof(x)-1));
    msb2 = y >> (8 * sizeof(y)-1);
    cout <<  "The value of x is " << x << endl;
    cout <<  "The value of y is " << y << endl;
    cout <<  "The most significant bit of x is " << msb << endl;
    cout <<  "The most significant bit of y is " << msb2 << endl;
    
    cout << "Type: \"short int\"; Size: " << sizeof(short int) << " bytes; "<< "Minimum value: "<< SHRT_MIN <<"; "<<"Maximum value:" << SHRT_MAX << endl;
    cout << "Type: \"unsigned short int\"; Size: " << sizeof(unsigned short int) << " bytes; "<< "Minimum value: 0; " <<"Maximum value:" << USHRT_MAX<< endl;
    cout << "Type: \"int\"; Size: " << sizeof(int) << " bytes; "<< "Minimum value: "<< INT_MIN <<"; "<<"Maximum value:" <<INT_MAX << endl;
    cout << "Type: \"unsigned int\"; Size: " << sizeof(unsigned int) << " bytes; "<< "Minimum value: 0; "<<"Maximum value:" << UINT_MAX << endl;
    cout << "Type: \"long int\"; Size: " << sizeof(long int) << " bytes; "<< "Minimum value: "<< LONG_MIN <<"; "<<"Maximum value:" <<LONG_MAX << endl;
    cout << "Type: \"unsigned long int\"; Size: " << sizeof(unsigned long int) << " bytes; "<< "Minimum value: 0; "<<"; "<<"Maximum value:" <<ULONG_MAX << endl;
    cout << "Type: \"long long int\"; Size: " << sizeof(long long int) << " bytes; "<< "Minimum value: "<< LLONG_MIN <<"; "<<"Maximum value:" <<LLONG_MAX << endl;
    cout << "Type: \"unsigned long long int\"; Size: " << sizeof(unsigned long long int) << " bytes; "<< "Minimum value: 0; "<<"Maximum value:" <<ULLONG_MAX << endl;
    cout << "Type: \"signed char\"; Size: " << sizeof(char) << " bytes; "<< "Minimum value: "<< CHAR_MIN <<"; "<<"Maximum value:" <<CHAR_MAX << endl;
    cout << "Type: \"unsigned char\"; Size: " << sizeof(unsigned char) << " bytes; "<< "Minimum value: 0; "<<"Maximum value:" <<UCHAR_MAX << endl;
    cout << "Type: \"float\"; Size: " << sizeof(float) << " bytes; "<< "Minimum value: "<< FLT_MIN <<"; "<<"Maximum value:" <<FLT_MAX << endl;
    cout << "Type: \"double\"; Size: " << sizeof(double) << " bytes; "<< "Minimum value: "<< DBL_MIN <<"; "<<"Maximum value:" <<DBL_MAX << endl;
    cout << "Type: \"long double\"; Size: " << sizeof(long double) << " bytes; "<< "Minimum value: "<< LDBL_MIN <<"; "<<"Maximum value:" <<LDBL_MAX << endl;
}

