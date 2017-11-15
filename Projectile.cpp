//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include <iostream>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

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

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
    if ( theta < -90 || theta >= 180)
        return false;
    if ( v < 0 || t<=0 || b <= 0 || d<=0 ||w<=0 || m <=0 || h<0)
        return false;
    if (theta == 90 || v ==0)
    {
        destY = h;
        destX = 0;
        return true;
    }
    destX = 0;
    destY = t-h;
    float timeOne = 0;
    float timeTwo = 0;
    float angle = theta * PI / 180;
    float horizontalV = v*cos(angle);
    float verticalV = v * sin(angle);
    timeOne = (-verticalV + sqrt(verticalV*verticalV - 2* 9.8 * destY))/(-9.8);
    timeTwo =(-verticalV - sqrt(verticalV*verticalV - 2* 9.8 * destY))/(-9.8);
    float finalVelocityY = 0;
    float time = 0;
    time = (timeOne >= timeTwo) ? timeOne : timeTwo;
    finalVelocityY =verticalV - 9.8 * time;
    float TtimeOne = (-finalVelocityY + sqrt(finalVelocityY*finalVelocityY + 2* 9.8 * t))/(-9.8);
    float TtimeTwo =(-finalVelocityY - sqrt(finalVelocityY*finalVelocityY + 2* 9.8 * t))/(-9.8);
    float Ttime = 0;
    Ttime = (TtimeOne >= TtimeTwo) ? TtimeOne : TtimeTwo;
    float extraDistance = Ttime*horizontalV;
    destX = time *horizontalV;
    if (t>=h)
    {
        timeOne = (-verticalV + sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        timeTwo =(-verticalV - sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        time = (timeOne >= timeTwo) ? timeOne : timeTwo;
        destX = time * horizontalV;
        if (destX > b )
        {
            destX = b;
            time = b/horizontalV;
            destY = h+(verticalV* time -4.9*time * time);
            return true;
        }
        else
        {
            destY =0;
            return true;
        }
    }
    if (theta > 90 )
    {
        float thetaN = 180 - theta;
        angle = thetaN * PI / 180;
        horizontalV = v*cos(angle);
        verticalV = v * sin(angle);
        timeOne = (-verticalV + sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        timeTwo = (-verticalV - sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        time = (timeOne >= timeTwo) ? timeOne : timeTwo;
        destX = -time *horizontalV;
        destY = 0;
        return true;
    }
   
    if (destX <= b-extraDistance)
    {
        timeOne = (-verticalV + sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        timeTwo =(-verticalV - sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        time = (timeOne >= timeTwo) ? timeOne : timeTwo;
        destX = time *horizontalV;
        destY = 0;
        return true;
    }
    if ( destX >= b && destX <=b+w )
    {
        destX = destX;
        destY = t;
        return true;
    }
    if ( destX > b+w)
    {
        destY =0;
        timeOne = (-verticalV + sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        timeTwo =(-verticalV - sqrt(verticalV*verticalV + 2* 9.8 * h))/(-9.8);
        time = (timeOne >= timeTwo) ? timeOne : timeTwo;
        destX = time *horizontalV;
        return true;
    }
    if (destX > b-extraDistance &&  destX < b)
    {
        time = b/horizontalV;
        destX = b;
        destY = h+(verticalV* time -4.9*time * time);
        return true;
    }
  // Your code here ...
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

  float h = 50;
  float v =  18.4;
  float m = 10;
  float theta =  17.89;        // Angle in degrees; will need to be converted by function
  float d = 100;
  float t = 60;
  float b = 30;
  float w = 20;

  float hitsAtX;
  float hitsAtY;

  if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
    cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
  else
    cout << "Unable to calculate where projectile hits." << endl;
  return 0;
}

#endif
