//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//
#include <limits.h>
#ifndef MARMOSET_TESTING
#include <iostream>

using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool stringToInt(const char input[], int& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool stringToInt(const char input[], int& value) {
    int i = 0;
    bool plusSign =0;
    bool minusSign=0;
    int plusNumber =-1;
    int minusNumber = -1;
    int unsignedNumber = 0;
    while (input[i] != '\0')
    {
        if (input[0] == '+')
        {
            plusSign = 1;
            i++;
            plusNumber++;
        }
       else if (input[0] == '-')
        {
            minusSign = 1;
            i++;
            minusNumber++;
        }
        else
        {
            i++;
            unsignedNumber++;
        }
    }
    if ( plusNumber >10 || minusNumber > 10 || unsignedNumber > 10)
        return false;
    //cout <<plusSign << endl;
    //cout <<minusSign << endl;
    //cout <<plusNumber << endl;
    //cout <<minusNumber << endl;
    //cout <<unsignedNumber<< endl;
    int j =0;
    long number = 0;
    switch (input[0])
    {
        case '+':
        {
            for (int index = 1; index <= plusNumber; index++)
            {
                if ( input[index] <'0' || input[index] >'9')
                    return false;
                number = number*10;
                number += (input[index]-'0');
                if (number >INT_MAX)
                    return false;
            }
            value = number;
            break;
        }
        case '-':
        {
            for (int index = 1; index <= minusNumber; index++)
            {
                if ( input[index] <'0' || input[index] >'9')
                    return false;
                number = number*10;
                number += (input[index]-'0');
                if (number >INT_MAX)
                    return false;
            }
            value = -number;
            break;
        }
        default:
        {
            for (int index = 0; index < unsignedNumber; index++)
            {
                if ( input[index] <'0' || input[index] >'9')
                    return false;
                number = number*10;
                number += (input[index]-'0');
                if (number >INT_MAX)
                    return false;
            }
            value = number;
        }
            //cout << value << endl;
        return true;
    }
    return true;
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

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
	
  
  // Some test driver code here ....
  int argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
    return -1;
  }

  if (stringToInt(argv[1],argv1)) 
    cout << "argv[1] is an int with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not an int." << endl;
  return 0;
}

#endif
