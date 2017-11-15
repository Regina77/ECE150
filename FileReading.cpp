//StringToInt(const char input[], int& value) {
    //    if (input[0] >= 48 && input[0] <= 57) {
    //        int length = 0;
    //        for(int i = 0; input[i] != '\0' ;i++)
    //            length = i;
    //        int sum = 0;
    //
    //        for (int i = 0; i <= length; i++)
    //            sum = 10 * sum + input[i] - 48;
    //        value = sum;
    //    }
    //    if (input[0] == '+') {
    //        int length = 0;
    //        for(int i = 1; input[i] != '\0' ;i++)
    //            length = i;
    //        int sum = 0;
    //
    //        for (int i = 0; i < length; i++)
    //            sum = 10 * sum + input[i + 1] - 48;
    //        value = sum;
    //    }
    //    if (input[0] == '-') {
    //        int length = 0;
    //        for(int i = 1; input[i] != '\0' ;i++)
    //            length = i;
    //        int sum = 0;
    //
    //        for (int i = 0; i < length; i++)
    //            sum = 10 * sum + input[i + 1] - 48;
    //        value = -sum;
    //    }
    //
    //
    //    return 0;
    //}
    
    //////////////////////////////////////////////////////////////
    //
    // Your #includes here; make sure you are allowed them ...
    //
    
#include <fstream>
    using namespace std;
    
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
    // Replace "..." in bisectionHelper() with any parameter(s)
    // you need to ensure termination when precision and
    // minIntervalSize are too tightly specified.
    //
    
    int histogram(const char filename[], int histogram[10],
                  const int minAcceptableID, const int maxAcceptableID,
                  int*& rejects);
    
    //////////////////////////////////////////////////////////////
    //
    // Your code here ...
    //
    // Return -1 if you cannot compute the histogram for any
    // reason;
    // Return 0 if the histogram is correct and there are no
    // rejections;
    // Return the number of rejects if there are rejected
    // records from the file
    //
    
    int histogram(const char filename[], int histogram[10],
                  const int minAcceptableID, const int maxAcceptableID,
                  int*& rejects) {
        
        if(histogram == NULL)
            return -1;
        
        if (minAcceptableID > maxAcceptableID)
            return -1;
        
        ifstream infile; // declare the file object
        infile.open(filename); // open the file
        
        if (!infile.is_open())
            return -1;
        
        bool done = false;
        //*rejects =0;
        int arrayRejects[100];
        int rejectTimes = 0;
        if (histogram == NULL)
            return -1;
        
        for (int i = 0; i < 10; i++)
            histogram[i] = 0;
        
        //int count = 0;
        int fileLineNumber = 0;
        const int maxLineLength = 100;
        char line[maxLineLength];
        while (!done) { // Read from file
            int studentID = 0;
            int grade = 0;
            ++fileLineNumber;
            if (!infile.getline(line, maxLineLength)) { // Get next line
                if (infile.eof()) { // End of file
                    done = true;
                    break;
                }
                else // Some error reading file
                    return -1;
            }
            int i = 0;
            while (line[i] != ',')
            {
                if (line[i] == ' ' || line[i] == '\t')
                    i++;
                else{
                    if (line[i] < '0' || line[i] > '9' )
                        return -1;
                    studentID *= 10;
                    studentID += (line[i]-'0');
                    i++;
                }
            }
            i++;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
            while (line[i] != 0 ) {
                if (line[i] == '-'){
                    grade *= -10;
                    grade -= (line[i+1]-'0');
                }
                grade *= 10;
                grade += (line[i]-'0');
                i++;
            };
            if ( grade < 0 || grade >100 || studentID > maxAcceptableID || studentID < minAcceptableID)
            {
                arrayRejects[rejectTimes] = fileLineNumber;
                rejectTimes++;
            }
            else
                histogram[grade/10]++;
            
            rejects = new int[rejectTimes];
            for (int j = 0; j < rejectTimes; j++)
            {
                *(rejects + j) = arrayRejects[j];
                int maxNumErrors = 10;
                if ( rejectTimes >= maxNumErrors)
                    return -1;
            }
            //cout << studentID << "  :  " << grade << endl;
        }
        return rejectTimes;
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
    
#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself
    
    int main(const int argc, const char* const argv[]) {
        
        // Some test driver code here ....
        if (argc < 2) {
            
        }
        const int numBuckets = 10;
        const int bucketRange = 100/numBuckets;
        int  buckets[numBuckets];
        int* rejectedRecords;
        int retCode = histogram(argv[1], buckets, 20000000, 22299999, rejectedRecords);
        if (retCode < 0) {
            cout << "Unable to compute histogram." << endl;
        }
        else {
            for (int i = 0; i < numBuckets; ++i)
                if (i != numBuckets-1)
                    cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
                else
                    cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
            if (retCode > 0) {
                cout << "Number of rejected records: " << retCode << endl;
                cout << "Rejected records are:";
                for (int i = 0; i < retCode; ++i)
                    cout << " " << rejectedRecords[i];
                cout << endl;
                delete[] rejectedRecords;
            }
        }
        
        return 0;
    }
    
#endif
