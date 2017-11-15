#include <iostream>
#include <stdlib.h>
#include <float.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
    if (argc < 3){
        cerr << "Error: Unable to compute statistics over data set because of insufficient input." << endl;
    };
    int windowSize = atoi(argv[1]);
    if (windowSize==1)
    {
        cerr << "Warning: The window size can't be one." << endl;
    };
    if (windowSize<=0)
    {
        cerr << "Error: Unable to compute statistics over data set because the window size can't be negative or zero." << endl;
        return -1;
    };
    if (windowSize > argc - 2)
    {
        cerr << "Warning: The window size can't be greater than inputs." << endl;
    };
    cout << "Window Size: " << windowSize << endl;
    cout << "Sample" <<"\t" << "Value" << "\t" << "SWMinimum" << " \t" <<"SWAverage"<<" \t"<< "SWMaximum" <<endl;
    float list[windowSize];
    int sample = 2;
    float total= 0;
    float min = atof(argv[sample]);
    float max = atof(argv[sample]);
    for (int i =2; i < argc; i++)
    {
        if (i-1 <= windowSize)
        {
            if (min > atof(argv[sample]))
                min = atof(argv[sample]);
            if (max < atof(argv[sample]))
                max = atof(argv[sample]);
            total += atof(argv[sample]);
            cout << i-1 << "\t" << argv[i] << "\t" << min << "\t" << "\t" << total /(sample-1) << "\t" << "\t" << max << endl;
            sample++;
        }
        else
        {
            for (int j =0; j < windowSize; j++)
            {
                list[j] =atof(argv[j+i-windowSize+1]);
            };
            min = list[0];
            for (int m =0; m < windowSize; m++)
            {
                if (min > list[m])
                    min = list[m];
                if (max < list[m])
                    max = list[m];
                //total +=list[m];
            }
            //cout << total << endl;
            float total2 = 0;
            for (int n = 0; n < windowSize; n++)
            {
                //cout << list[n] <<" ";
                total2 +=list[n];
            };
            //cout << endl;
            //cout << total2 << endl;
            cout << i-1 << "\t" << argv[i]  << "\t" << min  << "\t"<< "\t"  << total2/windowSize << "\t" << "\t" << max  << endl;
        }
        
    };
    
}
// ./swstats 3 1 2 3 4 7 1
