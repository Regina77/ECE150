#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main (const int argc, const char* const argv[]){
int numFloats=argc-1;
float value=0;
int i=2;
int j=0;
float min;
float max;

int windowSize = atoi(argv[1]);
float At;
int max_count=1;
int min_count=1;




    if (argc<=1)
    {
        cerr <<"Error: Unable to compute statistics over data set because of insufficient input." <<endl;
        return -1;
    }

if(windowSize<=0)
{cerr << "Unable to compute statistics over data set because there are insufficient arguments."<<endl;
return 1;}


else
{
    cout << "Window Size: " << windowSize << endl;
    cout << "\t" << "Sample" << "\t" << "Value" << "\t" << "SWMinimum"<< "\t" << "SWAverage" << "\t" << "SWMaximum"<< endl;
}
while (i< argc)
{value = atof (argv[i]);
	if (i==2){
value= atof (argv[i]);
max=atof (argv[i]);
min=atof (argv[i]);


else{

	if (max>value){
	 max_count++;}
	if (max<=value){
		max_count=1;
		max=value;}
	if (min<value){
		min_count++;}
	if (min>=value){
		min_count=1;
		min=value;}
}
		
	if (max_count>windowSize){
	max=value;}
		
	if (min_count>windowSize)
	{min=value;}

if (value >max){
max=value;}

else if(value <min){
min=value;}	   


cout << "\t" << count << "\t" << list[count]  << "\t" << min  << "\t" << 0 << "\t" << max  << endl;
i++;
}
}
