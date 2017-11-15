#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
    int count = argc-1;
    float average;
    float max;
    float min;
    float total = 0.0;
    min = atof(argv[count]);
    max = atof(argv[count]);
    if (argc == 1){
        cerr << "Unable to compute statistics over data set because of no imput." << endl;
    }
    while (count != 0)
    {
        if (atof(argv[count]) == false){
            cerr << "Unable to compute statistics over data set because of invalid input." << endl;
        }
        total += atof(argv[count]);
        if (min > atof(argv[count]))
            min = atof(argv[count]);
        if (max < atof(argv[count]))
            max = atof(argv[count]);
        count = count - 1;
    }
    cout <<"Number of floating-point numbers: " <<  argc-1 << endl;
    cout <<"Minimum floating-point number: " <<  min << endl;
    cout <<"Average floating-point number: " <<  total /(argc-1) << endl;
    cout <<"Maximum floating-point number: " <<  max << endl;
    return 0;
}

