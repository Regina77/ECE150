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

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
                float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool statistics(const float dataset[], const int size,
	   float& min, float& avg, float& max,
	   float& popSD, float& smplSD, float& mdn) {
    min = minimum(dataset,size);
    avg = average(dataset, size);
    max = maximum(dataset, size);
    popSD = popStdDev(dataset, size);
    smplSD = smplStdDev(dataset, size);
    mdn = median(dataset, size);
    if (size<2){
        return false;
    }
    if (size>=2){
        return true;
    }
}

float minimum(const float dataset[], const int size) {
    float min = dataset[0];
    for (int i =0; i < size; i++ )
    {
        if (min > dataset[i])
            min = dataset[i];
    };
    //cout << min << endl;
    return min;
}

float average(const float dataset[], const int size) {
    float total = 0;
    for (int i =0; i < size; i++ )
    {
        total +=dataset[i];
    };
    //cout << total << " " << size << endl;
    return total/size;
}

float maximum(const float dataset[], const int size) {
    float max = dataset[0];
    for (int i =0; i < size; i++ )
    {
        if (max < dataset[i])
            max = dataset[i];
    };
    return max;
}

float popStdDev(const float dataset[], const int size) {
    float temp = 0;
    float temp2 = 0;
    for (int i =0; i < size; i++ )
    {
        temp2 = dataset[i];
        temp = temp + (temp2 - average(dataset,size))*(temp2 - average(dataset,size));
    };
    return sqrt(temp/size);
}

float smplStdDev(const float dataset[], const int size) {
    float temp = 0;
    float temp2 = 0;
    for (int i =0; i < size; i++ )
    {
        temp2 = dataset[i];
        //cout << temp2 << endl;
        temp = temp + (temp2 - average(dataset,size))*(temp2 - average(dataset,size));
        //cout << temp << endl;
    };
    //cout << temp << endl;
    return sqrt(temp/(size-1));
}

float median(const float dataset[], const int size) {
    float copy[size];
    for (int a =0; a < size; a++)
    {
        copy[a] = dataset[a];
    };
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
            if (copy[j] > copy[j+1])
            {
                float swap = copy[j];
                copy[j] = copy[j+1];
                copy[j+1] = swap;
            };
        };
    };
    if (size % 2 != 0)
    {
        int mid = (size-1)/2;
        return copy[mid];
    }
    else
    {
        return (copy[size/2] + copy[size/2-1])/2.0;
    }
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
    int size = atoi(argv[1]);
    float dataset[size];
    for (int i=0; i < size; i++ )
    {
        dataset[i] = atof(argv[i+2]);
    }
    for (int j=0; j < size; j++ )
    {
        cout << dataset[j]<< " " << endl;;
    }
    //float dataset[] = {1, 2, 3, 4, 5};
    float min;
    float avg;
    float max;
    float popStDev;
    float smplStDev;
    float median;
    
    if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, median)) {
        cout << "Minimum: " << min << endl
        << "Average: " << avg << endl
        << "Median:  " << median << endl
        << "Maximum: " << max << endl
        << "Population Standard Deviation: " << popStDev << endl
        << "Sample Standard Deviation:     " << smplStDev << endl;
    }
    else
        cout << "Error: unable to compute statistics" << endl;
    
    return 0;
}

#endif
