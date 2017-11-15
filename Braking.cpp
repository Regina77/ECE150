#include <iostream>
#include <stdlib.h>

using namespace std;

int main( const int argc, const char* const argv[])
{
    float deceleration;
    float  time;
    deceleration = -atof(argv[1]) * atof(argv[1] ) / 2 / atof(argv[2] );
    time = 2 * atof(argv[2]) /  atof(argv[1]);
    cout << "Initial car velocity: " << argv[1] << "m/ s" << endl;
    cout << "Distance to obstacle: " <<argv[2] << "m" << endl;
    cout << "Minimum deceleration: " << deceleration << "m/ s/ s" << endl;
    cout << "Maximum stopping time: " << time << "s" << endl;
    return 0;
}
