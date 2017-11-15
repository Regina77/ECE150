#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(const int argc, const char* const argv[])
{
    //error message
    if (argc < 4)
    {
        cerr << "Error: insufficient arguments; exiting" << endl;
        return -1;
    }
    if (argc > 4)
    {
        cerr << "Warning: Expecting three command-line arguments; received " << argc-1 << "; ignoring extraneous arguments." << endl;
    };
    float velocity = atof(argv[1]);
    float distance = atof(argv[2]);
    // acceptable deceleration
    float accDec = atof(argv[3]);
    // Determines whether or not a collision is going to occur if there is no change in the car’s velocity.
    if (velocity == 0)
    {
        cout <<"There is no possibility of collision because the car is not moving." << endl;
        return -1;
    }
    else if ( velocity > 0 && distance < 0)
    {
        cout <<"There is no possibility of collision because the object is behind the car." << endl;
        return -1;
    }
    else if (velocity < 0 && distance > 0)
    {
        cout <<"There is no possibility of collision because the car is moving away from the object." << endl;
        return -1;
    };
    float minDeceleration = velocity*velocity /2/distance;
    float maxTime = 2* distance / velocity;
    if (minDeceleration < 0)
    {
        minDeceleration = -1* minDeceleration;
    };
    //no collision, v > 0, distance > 0
    if (minDeceleration < accDec)
    {
        cout << "Initial car velocity: " << velocity << " m/s"<< endl;
        cout << "Distance to obstacle: " << distance << " m" << endl;
        cout << "Minimum deceleration: " << minDeceleration << " m/s/s" << endl;
        cout << "Maximum stopping time: " << maxTime << " s" << endl;
        return -1;
    };
    // collision, v > 0, distance > 0
    if (minDeceleration >= accDec && velocity > 0)
    {
        float crashVelocity = sqrt(velocity * velocity - 2 * accDec * distance);
        float crashTime = 2*distance/(crashVelocity + velocity);
        cout << "Crash will occur in " << crashTime << " seconds at velocity " << crashVelocity << " m/s; deploying airbags." << endl;
        return -1;
    };
    // collision, v < 0, distance < 0
    if (minDeceleration >= accDec && velocity < 0)
    {
        float crashVelocity = -sqrt(velocity * velocity + 2 * accDec * distance);
        float crashTime = 2*distance/(crashVelocity + velocity);
        cout << "Crash will occur in " << crashTime << " seconds at velocity " << crashVelocity << " m/s; deploying airbags." << endl;
        return 0;
    };
    return 0;
}
