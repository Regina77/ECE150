#include <limits>

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define isNaN(X) (X != X)
#define NaN std::numeric_limits<float>::quiet_NaN()

enum sortType { ASCENDING, DESCENDING, UNKNOWN, UNSORTED };

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort);
bool sorted(const float data[]);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
//

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort) {
    if (data[currentDataItem + 1] != data[currentDataItem + 1]) {
        return true;
    }
    else{
        switch (typeOfSort) {
            case ASCENDING:
                if(data[currentDataItem + 1] >= data[currentDataItem])
                    return isSorted(data, currentDataItem + 1, ASCENDING);
                else return false;
                break;
            case DESCENDING:
                if(data[currentDataItem + 1] <= data[currentDataItem])
                    return isSorted(data, currentDataItem + 1, DESCENDING);
                else return false;
                break;
            case UNKNOWN:
                if (data[currentDataItem] < data[currentDataItem+1])
                    return isSorted(data, currentDataItem + 1, ASCENDING);
                if (data[currentDataItem] > data[currentDataItem+1])
                    return isSorted(data, currentDataItem + 1, DESCENDING);
                if (data[currentDataItem] == data[currentDataItem + 1])
                    return isSorted(data, currentDataItem + 1, UNKNOWN);
                break;
            case UNSORTED:
                return false;
        }
    }
    return true;
}

bool sorted(const float data[]) {
    return isSorted(data, 0, UNKNOWN);
}


#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
    
    // Some test driver code here ....
    float data[] = {1, 2, 4, 5, 9, NaN};
    
    if (sorted(data))
        cout << "Data is sorted" << endl;
    else
        cout << "Data is not sorted" << endl;
    
    return 0;
}

#endif

