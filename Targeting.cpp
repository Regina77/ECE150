//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN() 
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta);
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta) {
    float PI = 3.14159;
    float g = 9.8;
    if (v == 0 || h < 0 )
    {
        return 0;
    }
    else {
        float left = 0;
        float right = 0;
        float x = 0;
        float rad = 0;
        float sb = ((-0.5*g)*d*d)/(v*v);
        left = (-d+sqrt(d*d-4*sb*(sb+h-t)))/(2*sb);
        right = (-d-sqrt(d*d-4*sb*(sb+h-t)))/(2*sb);
        rad=atan(right);
        theta=rad/PI*180;
        return 1;
        }
}

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v) {
    float PI = 3.14159;
    float g = 9.8;
    if ( theta==0 || h < 0)
    {
        return 0;
    }
    else
    {
        float angle = (theta/180)*PI;
		float undersquare = t-h-tan(angle)*d;
		float div = -0.5*g;
		float square = sqrt(undersquare/div);
		v=d/square/cos(angle);
		return 1;
	}
}
		

#ifndef MARMOSET_TESTING
int main() {
	
  // Some test driver code here ....
  
  float h = 50;
  float d = 60;
  float b = 40;
  float t = 30;
  float w = 30;
  float m = 1;

  float theta = 45; // Angle in degrees;
  float v = 25;	

  cout << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity\n\n";
  }

  cout << "Given initial velocity: " << v << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenVelocity (h, v, m, d, t, b, w, theta)) {
    cout << "required angle: " << theta << endl << endl;
  }
  else {
    cout << "cannot calculate the angle\n\n";  
  }
    
  return 0;
}
#endif
