#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main(const int argc, const char* const argv[])
{
    if (argc <= 1){
        cerr << "Error: Unable to compute statistics over data set because of insufficient input." << endl;
    };
    float list[argc-1];
    int population = argc -1;
    int sample = 1;
    int i =0;
    float sdev;
    float pdev;
    float total = 0;
    float avg =0;
    for (int m =1; m< argc; m++)
    {
        total = total +  atof(argv[m]);
    }
    avg = total/(argc-1);
    while (sample < argc)
    {
        if (atof(argv[sample]) == false){
            cerr << "Erroe: Unable to compute statistics over data set because of invalid input." << endl;
        }
        list[i]=atof(argv[sample]);
        i++;
        sample++;
    };
    int j =0;
    float max = list[0];
    float min = list[0];
    while (j < argc-1)
    {
        if (min > list[j])
            min = list[j];
        if (max < list[j])
            max = list[j];
        total += list[j];
        j++;
    };
    //avg = total/population;
   /* int k = 0;
    float temp = 0;
    while ( k <=population)
    {
        temp += ((list[k])-avg)*((list[k])-avg);
        k++;
    };*/
    float temp = 0;
    float temp2 =0;
    for (int q =1; q< argc; ++q)
    {
        temp2 = atof(argv[q]);
        temp = temp + (temp2-avg)* (temp2-avg);
    }
    pdev =sqrt(temp/population);
    sdev =sqrt(temp/(population-1));
    if (argc ==2)
    {
        cout << "Number of floating-point numbers: " << population << endl;
        cout << "Minimum floating-point number: " << min << endl;
        cout << "Average floating-point number: " << avg << endl;
        cout << "Maximum floating-point number: " << max << endl;
        cout << "Population standard deviation: " << pdev << endl;
        cout << "Sample standard deviation: infinity "<< endl;
    }
    else
    {
    cout << "Number of floating-point numbers: " << population << endl;
    cout << "Minimum floating-point number: " << min << endl;
    cout << "Average floating-point number: " << avg << endl;
    cout << "Maximum floating-point number: " << max << endl;
    cout << "Population standard deviation: " << pdev << endl;
    cout << "Sample standard deviation: " << sdev << endl;
    };
    return 0;
}

