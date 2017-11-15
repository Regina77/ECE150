#include<iostream>
#include<stdlib.h>

using namespace std;

int main( const int argc, const char* const argv[])
{
    if ( argc < 4 )
    {
        cerr << "Error: Unable to compute Nth root because insufficent arguments." << endl;
        return -1;
    };
    if ( argc > 4 )
    {
        cerr << "Warning: Expecting three commond-line arguments,received " << argc -1 <<" ; ignoring extraneous arguments." << endl;
    };
    float number = atof(argv[1]);
    float precision = atof(argv[3]);
    float difference = 0;
    float temp = 15;
    int root = atoi(argv[2]);
    if (root != 2)
    {
        cerr << "Error: Unable to compute Nth root because of invalid input." << endl;
        return -1;
    };
    if ( precision < 0)
    {
        cerr << "Error: Unable to compute Nth root because the number is precision is smaller than 0." << endl;
        return -1;
    };
    int divide = root % 2;
    if ( number < 0 && divide == 0 )
    {
        cerr << "Error: Unable to compute Nth root because of invalid input." << endl;
        return -1;
    };
    
    if ( difference < 0 )
        difference = difference*(-1);
    int i = 1;
    for ( int i =1; i <= 200; ++i)
    {
        
        temp = (temp + number/temp) / 2;
        difference = (number - temp*temp)/number;
        if ( difference < 0 )
            difference = difference*(-1);
        if ( precision >= difference)
            i = 200;
    };
    cout << "Root(" << number << "," << root << ") = " << temp << endl;
    cout << "(with precision " << difference << " )" << endl;
    return 0;
}
