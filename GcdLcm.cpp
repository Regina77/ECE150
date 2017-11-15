#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
    if (argc < 3)
    {
        cerr << "Error: Unable to compute GCD and/or LCM because of insufficient arguments." << endl;
        return -1;
    };
    if (argc > 3)
    {
        cerr << "Warning: Expecting three command-line arguments; ignoring extraneous arguments."<< endl;
        return 0;
    };
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    if (m <= 0 || n <= 0 )
    {
        cerr << "Error: Unable to compute GCD and/or LCM because of insufficient arguments."  << endl;
        return -1;
    };
    int gcd = 0;
    for (int i = 1 ; i <= m && i <= n; i++)
    {
        if (m % i == 0  &&  n % i == 0 )
        {
            gcd=i;
            if (gcd >= 2147483547)
            {
                break;
            }
        };
    };
    int lcm = m/gcd*n;
    if (lcm > 2147483647 )
    {
        cerr << "Error: Unable to compute GCD and/or LCM because of the invalid input." <<endl;
        return -1;
    }
    cout << "GCD (" <<  m << ", " << n <<" ) = " << gcd << endl;
    cout << "LCM (" << m << "," << n <<") = " << lcm << endl;
    return 0;
}

