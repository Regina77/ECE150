#include <fstream>
#include <math.h>
#include <iostream>

#ifndef MARMOSET_TESTING
#include <iostream>

#endif
using namespace std;

//////////////////////////////////////////////////////////////

//struct definitions

//
//struct Student{
//    int studentID;
//    int grade;
//};
//
//struct Dataset{
//    int numStudents;
//    Student* students;
//};
//
//struct Rejects{
//    int numRejects;
//    int* rejects;
//};
//
//struct Mode{
//    int numModes;
//    int* modes;
//};
//
//struct Statistics{
//    int   minimum;
//    float average;
//    int   maximum;
//    float popStdDev;
//    float smplStdDev;
//    Mode  mode;
//    int   histogram[10];
//};

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool ERROR  = false;
int readCSV(const char filename[],const int minAcceptableID,
            const int maxAcceptableID,Dataset& data,
            Rejects& rejects);

int computeStatistics(Dataset& data, Statistics& stats);

int writeCSV(const char filename[], const Statistics& stats);
//sort
int bubbleSort(int dataset[], const int size){
    
    if (size <= 0)
        return -1;
    if (size >= 1) {
        for (int i = 0; i < size-1; i++)
        {
            for (int j = 0; j < size-i-1; j++)
            {
                if (dataset[j] > dataset[j+1])
                {
                    float swap = dataset[j];
                    dataset[j] = dataset[j+1];
                    dataset[j+1] = swap;
                }
            }
        }
    }
    return 0;
}

// check if the list can be sorted
bool sort(int dataset[], const int size){
    if(size <= 0) return false;
    if (bubbleSort(dataset, size))
        return false;
    else
        return true;
}

bool mode(const int dataset[], const int size, Mode &modes){
    if (size <= 0)
        return -1;
    if (size == 1) {
        modes.modes = new int[1];
        modes.modes[0] = dataset[0];
        modes.numModes = 1;
        return 0;
    }
    int copy[size];
    for (int a =0; a < size; a++)
    {
        copy[a] = dataset[a];
    };
    if (!sort(copy, size))
        return false;
    int count = 1;
    int maxCount = 1;
    
    for (int i = 0; i < size-1; i++) {
        if (copy[i + 1] == copy[i]) {
            count++;
            if (maxCount < count)
            {
                maxCount = count;
                count =1;
            }
        }
        else
            count = 1;
    }
    // no repeated number
    if (maxCount == 1)
    {
        modes.numModes  = size;
        modes.modes = new int[size];
        for ( int i = 0; i < size; i++)
        {
            modes.modes[i] = copy[i];
        }
        return 0;
    }
    modes.numModes = 0;
    count = 1;
    for (int i = 0; i < size-1; i++) {
        if (copy[i+1] ==copy[i])
        {
            count++;
            if (maxCount == count) {
                modes.numModes++;
                count = 1;
            }
        }
        else
            count = 1;
    }
    
    modes.modes = new int[modes.numModes];
    
    int count2 = 0;
    count = 1;
    for (int i = 0; i < size-1; i++) {
        if (copy[i+1] ==copy[i])
        {
            count++;
            if (count == maxCount) {
                modes.modes[count2] = copy[i];
                count2++;
            }
        }
        else count = 1;
    }
    return 0;
}


float median(const float dataset[], const int size) {
    float copy[size];
    for(int i = 0; i < size; i++)
        copy[i] = dataset[i];
    for (int i = 0; i < size; i++) {
        int min = copy[i];
        for (int j = (i+1); j < size; j++)
            if (copy[min] > copy[j])
                min = j;
        if(i != min){
            float a = copy[i];
            copy[i] = copy[min];
            copy[min] = a;
        }
    }
    if(! (size % 2))
        return ((copy[size / 2] + copy[size / 2 - 1]) / 2);
    else
        return copy[size / 2];
}


//bool stringToInt(const char input[], int& value) {
//    if (input[0] == '\0')
//        return false;
//    int i = 0;
//    bool plusSign =0;
//    bool minusSign=0;
//    int plusNumber =-1;
//    int minusNumber = -1;
//    int unsignedNumber = 0;
//    while (input[i] != '\0')
//    {
//        if (input[0] == '+')
//        {
//            plusSign = 1;
//            i++;
//            plusNumber++;
//        }
//        else if (input[0] == '-')
//        {
//            minusSign = 1;
//            i++;
//            minusNumber++;
//        }
//        else
//        {
//            i++;
//            unsignedNumber++;
//        }
//    }
//    if ( plusNumber >10 || minusNumber > 10 || unsignedNumber > 10)
//        return false;
//    //int j =0;
//    int number = 0;
//    switch (input[0])
//    {
//        case '+':
//        {
//            for (int index = 1; index <= plusNumber; index++)
//            {
//                if ( input[index] <'0' || input[index] >'9')
//                    return false;
//                number = number*10;
//                number += (input[index]-'0');
//            }
//            value = number;
//            break;
//        }
//        case '-':
//        {
//            for (int index = 1; index <= minusNumber; index++)
//            {
//                if ( input[index] <'0' || input[index] >'9')
//                    return false;
//                number = number*10;
//                number += (input[index]-'0');
//            }
//            value = -number;
//            break;
//        }
//        default:
//        {
//            for (int index = 0; index < unsignedNumber; index++)
//            {
//                if ( input[index] <'0' || input[index] >'9')
//                {
//                     return false;
//                }
//                number = number*10;
//                number += (input[index]-'0');
//            }
//            value = number;
//        }
//            return true;
//    }
//    return true;
//}

int readCSV(const char filename[], const int minAcceptableID, const int maxAcceptableID, Dataset& data, Rejects& rejects) {
    // condition check
    if(minAcceptableID > maxAcceptableID)
    {
        ERROR = true;
        return -1;
    }
    char copy[200] = {'\0'};
    int dotPosition = -1;
    int nameEnd = -1;
    // filename write
    for (int i = 0; filename[i] != '\0'; i++) {
        copy[i] = filename[i];
        if(copy[i] == '.')
            dotPosition = i;
        nameEnd = i;
    }
    // reqrite filename
    if(dotPosition == -1) {
        copy[nameEnd + 1] = '.';
        copy[nameEnd + 2] = 'c';
        copy[nameEnd + 3] = 's';
        copy[nameEnd + 4] = 'v';
        copy[nameEnd + 5] = '\0';
    }
    
    if(dotPosition != -1 && (copy[dotPosition + 1] != 'c' || copy[dotPosition + 2] != 's' || copy[dotPosition + 3] != 'v'))
    {
        ERROR = true;
        return -1;
    }
    if(dotPosition != -1 && copy[dotPosition + 1] == 'c' && copy[dotPosition + 2] == 's' && copy[dotPosition + 3] == 'v')
        copy[nameEnd + 1] = '\0';
    
    ifstream infile(copy);
    
    if(!infile.is_open() || minAcceptableID >= maxAcceptableID)
    {
        ERROR = true;
        return -1;
    }
    char line[200];
    int maxline =0;
    while ( !infile.eof())
    {
        infile.getline(line, 200);
        maxline++;
    }
    infile.close();
    data.students = new Student[maxline];
    rejects.numRejects = 0;
    rejects.rejects = new int[11];
    data.numStudents = 0;
    // start read file contant
    
    bool done = false;
    int fileLineNumber = 0;
    
    
    bool warning = 0;
    infile.open(copy);
    while(!done) {
        int studentID = 0;
        int grade = 0;
        
        bool invalid = 0;
        bool missing = 0;
        //bool missingID = 0;
        if(!infile.getline(line, 100)) {
            if(infile.eof())
            {
                done = true;
                break;
            }
            else
            {
                ERROR = true;
                invalid = 1;
            }
        }
        fileLineNumber++ ;
        for (int i = 0; line[i]; i++ )
        {
            // check for alphabetas in the whole line, invalid for jump the line, reset everyline.
            //warning doesn't rest, it is in charge of return a positive number if anything went slightly wrong
            if (( line[i] < '0' || line[i] > '9') && line[i] != ' ' && line[i] != '\t' && line[i] != '+' && line[i] != '-'&& line[i] != ',')
            {
                invalid = 1;
                warning = 1;
            }
            // check for missing grade or comma
            if ((line[i] == '+' ||line[i] == '-'  ) && line[i-1] != ',')
            {
                invalid =1;
                warning = 1;
            }
        }
        // empty line check
        if ( line[0] == 0 || line[0] == '\n')
        {
            invalid = 1;
            warning = 1;
        }
        int commaPosition = 0;
        // missing comma?
        if (invalid == 0)
        {
            missing = 1;
            for (int i = 0; line[i] !=',';i++)
            {
                if (line[i] <= '9' && line[i] >='0' )
                {
                    studentID = studentID*10 +(line[i] -'0');
                }
                if (line[i+1] == ',')
                {
                    commaPosition = i+1;
                    missing = 0;
                }
            }
            if (line[commaPosition+1] == 0)
                missing =1;
            for ( int i = commaPosition +1; line[i] !=0; i++)
            {
                if (line[i] == ',')
                    missing = 1;
                if (line[i] <= '9' && line[i] >='0')
                    grade =grade*10 +(line[i] -'0');
                if ( line[i+1] == 0)
                {
                    break;
                }
            }
            // get the first and last ID number position
            int firstIDdigit =0;
            int lastIDdigit = 0;
            if ( line[commaPosition +1 ] == '-')
                grade = -1 * grade;
            for (int i = 0; line[i] !=',';i++)
            {
                if (line[i] <= '9' && line[i] >='0')
                {
                    firstIDdigit = i;
                    break;
                }
            }
            for (int i = 0; line[i] !=',';i++)
            {
                if (line[i] <= '9' && line[i] >='0')
                {
                    lastIDdigit = i;
                }
            }
            //get the first and last grade number position
            int firstGradeDigit = 0;
            int lastGradeDigit = 0;
            for (int i = commaPosition +1; line[i]; i++)
            {
                if (line[i] <= '9' && line[i] >='0')
                {
                    firstGradeDigit = i;
                    break;
                }
            }
            for (int i = commaPosition +1; line[i]; i++)
            {
                if (line[i] <= '9' && line[i] >='0')
                {
                    lastGradeDigit = i;
                }
            }
            
            for (int i = 0; line[i]; i++)
            {
                if ((line[i]==' ' || line[i]=='\t' )&&i >= firstIDdigit && i <= lastIDdigit)
                {
                    missing = 1;
                }
                if ((line[i]==' ' || line[i]=='\t' )&&i >=  firstGradeDigit&& i <= lastGradeDigit)
                {
                    missing = 1;
                }
            }
            int space = 0;
            int count = 0;
            for (int i = 0; line[i] !=','; i++)
            {
                count++;
                if (line[i]==' ' || line[i]=='\t')
                {
                    space++;
                }
            }
            if (space == count)
                missing =1;
            space =0;
            count =0;
            for (int i = commaPosition+1; line[i]; i++)
            {
                count++;
                if (line[i]==' ' || line[i]=='\t')
                {
                    space++;
                }
            }
            if (space == count)
                missing =1;
            if (line[commaPosition+1] == '\n' || line[commaPosition+1] ==0)
                missing =1;
            if ( studentID < minAcceptableID || studentID > maxAcceptableID || grade < 0 || grade > 100 || missing ==1)
            {
                warning = 1;
                rejects.rejects[rejects.numRejects] = fileLineNumber;
                rejects.numRejects++;
                if (rejects.numRejects >=10)
                {
                    ERROR = 1;
                    return -1;
                }
            }
            else
            {
                data.students[data.numStudents].studentID = studentID;
                data.students[data.numStudents].grade = grade;
                data.numStudents++;
            }
        }
    }
    
    infile.close();
    return 0;
}

int computeStatistics(Dataset& data, Statistics& stats){
    if (ERROR == true)
        return false;
    
    //store all students grade into a new array
    int datasetCopy[data.numStudents];
    for (int i = 0; i < data.numStudents; i++)
        datasetCopy[i] = data.students[i].grade;
    
    //minimum
    stats.minimum = datasetCopy[0];
    int count = 0;
    while (count < data.numStudents)
    {
        if (datasetCopy[count] < stats.minimum)
            stats.minimum = datasetCopy[count];
        count++;
    }
    
    //maximum
    stats.maximum = datasetCopy[0];
    count = 0;
    while (count < data.numStudents)
    {
        if (datasetCopy[count] > stats.maximum)
            stats.maximum = datasetCopy[count];
        count++;
    }
    
    //average
    stats.average = 0;
    for (int i = 0; i < data.numStudents; i++)
    {
        stats.average += datasetCopy[i];
    }
    stats.average /= data.numStudents;
    
    //popstddev
    count = 0;
    while(count < data.numStudents)
    {
        float input = datasetCopy[count];
        stats.popStdDev += (input - stats.average) * (input - stats.average);
        count++;
    }
    stats.popStdDev = sqrt(stats.popStdDev / data.numStudents);
    
    //smplstddev
    count = 0;
    while(count < data.numStudents)
    {
        float input = datasetCopy[count];
        stats.smplStdDev += (input - stats.average) * (input - stats.average);
        count++;
    }
    stats.smplStdDev = sqrt(stats.smplStdDev / (data.numStudents - 1));
    
    //modes
    mode(datasetCopy, data.numStudents, stats.mode);
    
    //histogram
    for (int i = 0; i < data.numStudents; i++) {
        stats.histogram[data.students[i].grade / 10]++;
    }
    
    return 0;
}

int writeCSV(const char filename[], const Statistics& stats){
    if (ERROR == true)
        return false;
    char copy[200] = {'\0'};
    int dotPosition = -1;
    int nameEnd = -1;
    for (int i = 0; filename[i] != '\0'; i++) {
        copy[i] = filename[i];
        if(copy[i] == '.')
            dotPosition = i;
        nameEnd = i;
    }
    
    if(dotPosition == -1) {
        copy[nameEnd + 1] = '.';
        copy[nameEnd + 2] = 's';
        copy[nameEnd + 3] = 't';
        copy[nameEnd + 4] = 'a';
        copy[nameEnd + 5] = 't';
        copy[nameEnd + 6] = '\0';
        
    }
    if(dotPosition != -1 && (copy[dotPosition + 1] != 'c' || copy[dotPosition + 2] != 's' || copy[dotPosition + 3] != 'v'))
        return -1;
    if(dotPosition != -1 && copy[dotPosition + 1] == 'c' && copy[dotPosition + 2] == 's' && copy[dotPosition + 3] == 'v') {
        copy[dotPosition + 1] = 's';
        copy[dotPosition + 2] = 't';
        copy[dotPosition + 3] = 'a';
        copy[dotPosition + 4] = 't';
        copy[dotPosition + 5] = '\0';
    }
    
    //////////////////////////////////////
    
    ///////////////////////////////////////
    ofstream outfile(copy);
    if(!outfile.is_open())
        return -1;
    
    outfile << "Minimum: " << stats.minimum << std::endl;
    outfile << "Average: " << stats.average << std::endl;
    outfile << "Maximum: " << stats.maximum << std::endl;
    outfile << "Population Standard Deviation: " << stats.popStdDev << std::endl;
    outfile << "Sample Standard Deviation: " << stats.smplStdDev << std::endl;
    outfile << "Modes: ";
    for (unsigned char i = 0; i < stats.mode.numModes; i++) {
        outfile << stats.mode.modes[i];
        if(i != stats.mode.numModes - 1)
            outfile << ", ";
    }
    outfile << endl;
    
    outfile << "Histogram: " << endl;
    for (unsigned char i = 0; i < 10; i++)
        outfile << "[" << (i*10) << "-" << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
    
    outfile.close();
    return 0;
}
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
    
    int minAcceptableID = 20000000;
    int maxAcceptableID = 23000000;
    
    Dataset data = {0};
    Rejects rejects = {0};
    Statistics stats = {0};
    
    std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;
    
    if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
    {
        std::cout << ".csv file could not be read" << std::endl;
    }
    
    if (computeStatistics(data, stats) < 0)
    {
        std::cout << "Stats could not be computed" << std::endl;
    }
    
    if (writeCSV(argv[1], stats) < 0)
    {
        std::cout << ".stat file could not be written" << std::endl;
    }
    
    std::cout << "Average: " << stats.average << std::endl;
    std::cout << "Minimum: " << stats.minimum << std::endl;
    std::cout << "Maximum: " << stats.maximum << std::endl;
    std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
    std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;
    
    for (unsigned char i = 0; i < stats.mode.numModes; i++)
    {
        std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
    }
    
    for (unsigned char i = 0; i < 10; i++)
    {
        std::cout << "Histogram bin [" << (i*10) << ", " << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
    }
    
    
    return 0;
}

#endif


