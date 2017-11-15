#include <iostream>
#include <stdlib.h>
#include <iomanip>


using namespace std;

int main(const int argc, const char* const argv[])
{
    if (argc <= 1){
        cerr << "Unable to compute statistics over data set because of insufficient imput." << endl;
    };
    int sample = 1;
    float average;
    float max;
    float min;
    float total = 0.0;
    min = atof(argv[sample]);
    max = atof(argv[sample]);
    cout << "\t" << "Sample" << "\t" << "Value" << "\t" << "Minimum"<< "\t" << "Average" << "\t" << "Maximum"<< endl;
    while (sample != argc)
    {
        if (atof(argv[sample]) == false){
            cerr << "Unable to compute statistics over data set because of invalid input." << endl;
        }
        total += atof(argv[sample]);
        if (min > atof(argv[sample]))
            min = atof(argv[sample]);
        if (max < atof(argv[sample]))
            max = atof(argv[sample]);
        cout << "\t" << sample << "\t" << argv[sample] << "\t" << min << "\t" << total /sample << "\t" << max << endl;
        sample++;
    }
    return 0;
}

