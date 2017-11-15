//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <math.h>
#include <limits>
#include <stdlib.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;


// Sample function for which you need to find the root

float f(const float x) {
  return 3.2*x*x*x - 2.1*x - 23.0;
}

//#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize,
		      float& count);
float bisection(const float left, const float right,
		const float precision, const float minIntervalSize);
#endif
#include <math.h>
#include <limits>
#include <float.h>
//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//
float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize,int count)
    {
        float midpoint =(left + right )/2;
        float leftYValue = f(left);
        float rightYValue = f(right);
        float midPointYValue = f(midpoint);
        if(left>FLT_MAX || left<(-FLT_MAX) || right>FLT_MAX || right<(-FLT_MAX) || precision <= 0)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if (precision<FLT_MIN|| minIntervalSize<FLT_MIN)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if (left > right)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if ( leftYValue > 0 && rightYValue >0)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if ( leftYValue < 0 && rightYValue <0)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if ( precision >= 1 ||  precision <=0)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if (isnan(leftYValue) || isnan(rightYValue))
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else if((leftYValue*rightYValue)>0)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }
        else
        {
            if (count > 9999999)
            {
                return std::numeric_limits<float>::quiet_NaN();
            }
            else
            {
                if ( fabs(right - left) <= minIntervalSize || fabs( midPointYValue) <= precision)
                {
                    return midpoint;
                }
                else if (leftYValue * midPointYValue >= 0)
                {
                    return bisectionHelper( midpoint, right, precision, minIntervalSize, ++count);
                }
                else if(leftYValue * midPointYValue <= 0)
                {
                    return bisectionHelper( left, midpoint, precision, minIntervalSize, ++count);
                }
            }
        }
    }

float bisection(const float left, const float right,
		const float precision, const float minIntervalSize) {
    int count = 0;
    return bisectionHelper(left, right, precision, minIntervalSize, ++count);
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
    float midpoint = bisection(atof(argv[1]),atof(argv[2]),atof(argv[3]),atof(argv[4]));
   cout << midpoint << endl;
}

#endif
