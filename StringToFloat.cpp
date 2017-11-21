//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...

#include <float.h>
// You are allowed float.h

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

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

bool stringToFloat(const char input[], float& value) {
    // check for empty input
    if (input[0] == '\0')
        return false;
    int i = 0;
    bool plusSign =0;
    bool minusSign=0;
    bool noSign =0;
    bool eExist =0;
    bool justInt = 0;
    int intPart = 0;
    float decPart = 0;
    float number =0;
    int intPartLength = 0;
    while (input[i] != '.' )
    {
        if (  input[i] != '\0')
        {
            i++;
            intPartLength++;
        }
        else
        {
            justInt =1;
            break;
        }
    }
    int SigintPartLength = 0;
    int decPartLength = 0;
    i++;
    while (input[i] != '\0')
    {
        if (input[i] != 'e' && input[i] != 'E' && justInt ==0)
        {
            i++;
            decPartLength++;
        }
        else
            break;
    }
    int decplace = 10;
    for (int m =1; m< decPartLength; m++)
    {
        decplace*=10;
    }
    bool posPower = 0;
    bool negPower = 0;
    int power = 0;
    long int powerBig = 1;
    float powerSmall =1;
    if (input[i] == 'e' || input[i] == 'E' )
    {
        i++;
        eExist =1;
        if (input[i] == '+')
        {
            posPower =1;
            i++;
        }
        else if ( input[i] == '-')
        {
            negPower =1;
            i++;
        }
        else if ( input[i] < '0' || input[i] > '9')
        {
            return  false;
        }
        if (eExist)
        {
            while ( input[i] != '\0')
            {
                power *= 10;
                power += (input[i]-'0');
                i++;
            }
            for (int i = 0; i < power;i++)
                if (negPower ==1)
                    powerSmall = powerSmall * 0.1;
                else
                    powerBig = powerBig * 10;
        }
    }
    // check sign
    switch (input[0]) {
        case '+' :
            plusSign = 1;
            break;
        case '-' :
            minusSign = 1;
            break;
        default:
            if (input[0] <'0' || input[0] >'9' ) //check invalid input
                return  false;
            noSign = 1;
            break;
    }
    switch (intPartLength) {
        case 0:
            intPart =0;
            break;
        case 1 :
            if (plusSign == 1 || minusSign ==1){
                intPart = 0;
            }
            if (input[0] == ' ')
                intPart =0;
            else{
                intPart = input[0]-'0';
            }
            break;
        default:
            if (plusSign == 1 || minusSign ==1)
            {
                for (int i = 1; i < intPartLength; i++)
                {
                    if (input[i] == ' ')
                        i++;
                    if (input[i] <'0' || input[i] >'9')
                        return false;
                    intPart = intPart*10;
                    intPart += (input[i]-'0');
                }
            }
            else
            {
                for (int i = 0; i < intPartLength; i++)
                {
                    if (input[i] <'0' || input[i] >'9')
                        return false;
                    intPart = intPart*10;
                    intPart += (input[i]-'0');
                }
            }
            break;
    }
    //    float decplace = 1;
    for (int j =intPartLength+1; j < intPartLength+ decPartLength +1; j++)
    {
        if (input[j] < '0' ||input[j] >'9' )
            return false;
        decPart = decPart* 10;
        decPart += (input[j]-'0');
    }
    decPart = decPart/decplace;
    if ( plusSign ==1  || noSign ==1)
    {
        if ( negPower ==1)
            number = ( intPart +decPart)* powerSmall;
        else
            number = ( intPart +decPart)* powerBig;
    }
    if ( minusSign ==1 )
    {
        if ( negPower ==1)
            number = -( intPart +decPart)* powerSmall;
        else
            number = -( intPart +decPart)* powerBig;
    }
    value = number;
    return true;
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
    
    // Some test driver code here ....
    float argv1;
    
    if (argc < 2) {
        cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
        return -1;
    }
    
    if (stringToFloat(argv[1],argv1))
        cout << "argv[1] is a float with value: " << argv1 <<endl;
    else
        cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
    return 0;
}

#endif


