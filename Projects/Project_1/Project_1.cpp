
//  cs311project1
//  Stephan Takacs
//

#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <random>
#include <utility>
#include <fstream>
using namespace std;

//helper functions
//vector generation functions not going to comment more on them
vector<int> randomVector(int size, int low, int high){
    vector<int> v(size, 0);
    for (int i = 0; i < size; i++){
        v[i] = rand() % (high - low +1) + low;
    }
    return v;
}

vector<int> sortedVector(int size, int low, int high){
    vector<int> v(size, 0);
    for(int i = 0; i < size; i++){
        v[i] = i;
    }
    return v;
}

vector<int> revSortedVector(int size, int low, int high){
    vector<int> v(size);
    for(int i = 0; i < size; i++){
        v[i] = size - i - 1;
    }
    return v;
}

//function to calculate standard deviation (from project notes) with typecast to int
double sampleSD(const vector<double> v){
    double mean = 0;
    for (int i = 0; i < v.size(); i++){
        mean += v[i];
    }
    mean = mean / v.size();
    double sd = 0;
    for (int i = 0; i < v.size(); i++){
        sd += (v[i]-mean)*(v[i]-mean);
    }
    sd = sd / (v.size()-1);
    return sqrt(sd);
}



//function to check if the vector is sorted
bool isSorted(vector<int>& v){
    for(int i = 1; i < v.size(); i++){
        if(v[i - 1] > v [i]) {
            return false;
        }
    }
    return true;
}
//function that is going to check all of the test results's success after they are collected (depc)
bool sortingSuccessful(vector<bool>& sortTestResult){
    for(bool val : sortTestResult) {
        if(!val) return false;
    }
    return true;
}

//all sorting functions implemented with references

//bubble sort
/*
 according to lecture slides puesdocode for bubble is:
 function bubbleSort(L)
    sort = false
    while not sorted
        sorted = true
        for i from 1 to length(L)-1
            if L[i-1] > L[i]
                temp = L[i-1]
                L[i-1] = L[i]
                L[i] = temp
                sorted = false
        return L
 */
void bubbleSort(vector<int>& v){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 1; i < v.size(); i++){
            if(v[i - 1] > v[i]){
                int temp = v[i - 1];
                v[i - 1] = v[i];
                v[i] = temp;
                sorted = false;
            }
        }
    }
}

//insertion sort
/*
 puesdocode for insert:
function insertionSort(L)
    i = 1
    while i < length(L)
        j = 1
        while j > 0 and L[j] < L[j-1]
            temp = L[j-1]
            L[j-1] = L[j]
            L[j] = temp
            j = j - 1
        i = i + 1
    return L
 */
void insertionSort(vector<int>& v){
    int i = 1;
    while(i < v.size()){
        int j = i;
        while(j > 0 && (v[j] < v[j - 1])){
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
            j--;
        }
        i++;
    }
}

//selection sort
/*
puesdocode for selection sort
function selectionSort(L)
    for i from 0 to length(L)-2
        uMin = i
        for j from i+1 to length(L)-1
            if L[j] < L[uMin]
                uMin = j
        temp = L[i]
        L[i] = L[uMin]
        L[uMin] = temp return L
 */
void selectionSort(vector<int>& v){
    for(int i = 0; i < v.size() - 1; i++){
        int uMin = i;
        for(int j = i + 1; j < v.size(); j++){
            if(v[j] < v[uMin]) uMin = j;
        }
        int temp = v[i];
        v[i] = v[uMin];
        v[uMin] = temp;
    }
}

//quicksort
/*
 puesdocode per lecture slides
 function quicksort(L)
    if length(L) <= 1
        return
    Lpivot = L[0]
    A = []
    B = []
    for e in rest(L) if e <= pivot
        append(A, e)
        else
            append(B, e)
    return quicksort(A) + [pivot] + quicksort(B)
 */
vector<int> quickSort(vector<int>& v){
    if(v.size() <= 1) return v;
    
    int vPivot = v[0];
    vector<int> A;
    vector<int> B;
    
    for(int i = 1; i < v.size(); i++){
        if(v[i] <= vPivot) A.push_back(v[i]);
        else B.push_back(v[i]);
    }
    //doing the entire sort in one function so going to recursively pass and b in first then combine and return sorted at the end
    vector<int> sortedA = quickSort(A);
    vector<int> sortedB = quickSort(B);
    
    //now combining as referenced above
    vector<int> fullSorted = sortedA;
    fullSorted.push_back(vPivot);
    /*
     I was struggling with the full vect concatenation and found this solution that worked for me at this stackoverflow question:
     https://stackoverflow.com/questions/201718/concatenating-two-stdvectors
     */
    fullSorted.insert(fullSorted.end(), sortedB.begin(), sortedB.end());
    return fullSorted;
}

//this is the modified quicksort function to account for the comprehensive testing/best case
vector<int> quickSortBestCase(vector<int>& v, bool bestCase = false) {
    if(v.size() <= 1) return v;
    
    int vPivotIndex;
    //now going to either use middle for best case or if not best case just the norm
    if(bestCase) vPivotIndex = (v.size() / 2);
    else vPivotIndex = 0;
    int vPivot = v[vPivotIndex];
    vector<int> A;
    vector<int> B;

    //do not use new pivot for separation
    for(int i = 0; i < v.size(); i++){
        if(i == vPivotIndex) continue;
        if(v[i] <= vPivot) A.push_back(v[i]);
        else B.push_back(v[i]);
    }

    vector<int> sortedA = quickSortBestCase(A, bestCase);
    vector<int> sortedB = quickSortBestCase(B, bestCase);

    vector<int> fullSorted = sortedA;
    fullSorted.push_back(vPivot);
    fullSorted.insert(fullSorted.end(), sortedB.begin(), sortedB.end());
    return fullSorted;
}


//testing functions ->

//function to print vector to test
void printVec(vector<int>& v){
    for(int i : v){
        cout << i << " ";
    }
}

/*
 main testing function:
 Write a function that runs each of the sorting algorithms on ten random vectors of length
 100, collects the run times, verifies that the sorting was successful, and prints out the minimum,
 mean, standard deviation, and maximum of the run times. Example output for a single sort might
 look something like this:
 ************************
 Bubble sort on 10 vectors of length 100
 Sorting successful
 Minimum: 1 sec; Mean: 1 sec; Standard deviation: 1 sec; Maximum: 1 sec
 ************************
 so need to collect the random vectors, run each function with time, and then store the times in a vector
 */
/*
 first going to make one function to print out the time stats and do all of the calcs for the last line of output
 */
void timeStats(vector<double> times){
    //first sd bc i already have the code and wrote above:
    double sd = sampleSD(times);
    //going to inline sort here with std sort as I dont want to typecast the vector and all sorts are with int
    auto start = times.begin();
    auto end = times.end();
    sort(start, end);
    
    double timesMax = times[0];
    double timesMin = times.back();
    
    //now finding mean, using the mean finding snippet of code from the sampleSD function
    double timesMean = 0;
    for (int i = 0; i < times.size(); i++){
        timesMean += times[i];
    }
    timesMean = timesMean / times.size();
    
    //now cout the required format
    cout << "Minimum: " << timesMin << " sec; " << "Mean: " << timesMean << " sec; " << "Standard deviation: " << sd << " sec; " << "Maxiumum: " << timesMax << " sec" << endl;
}


/*
 now going to write the main testing function (going to make it super generalized)
input: sorting method, vector type -> going to use a switch case and make vect type an int this way I can copy main function from lab1
case 1: random, case 2: sorted, case 3 reverse sorted
vector length, amount of vectors
output: vector of times each test took
afer examining I will make a testing function for each different type of sort

 */
//testing all sorts (depc functions usings better testing
/*
vector<double> testBubble(int vectorType, int vectorLength, int numTestCases){
    //make times vector
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    vector<double> times;
    switch (vectorType) {
        case 1:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = randomVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                bubbleSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 2:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = sortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                bubbleSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 3:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = revSortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                bubbleSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
    }
    return times;
}
*/
/*
vector<double> testInsertion(int vectorType, int vectorLength, int numTestCases){
    //make times vector
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    vector<double> times;
    switch (vectorType) {
        case 1:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = randomVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                insertionSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 2:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = sortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                insertionSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 3:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = revSortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                insertionSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
    }
    return times;
}
*/
/*
vector<double> testSelection(int vectorType, int vectorLength, int numTestCases){
    //make times vector
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    vector<double> times;
    switch (vectorType) {
        case 1:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = randomVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                selectionSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 2:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = sortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                selectionSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 3:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = revSortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                selectionSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
    }
    return times;
}
*/
/*
vector<double> testQuick(int vectorType, int vectorLength, int numTestCases){
    //make times vector
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    vector<double> times;
    switch (vectorType) {
        case 1:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = randomVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                quickSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 2:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = sortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                quickSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
        case 3:
            for(int i = 0; i < numTestCases; i++){
                //first declare temp vector
                vector<int> testVector = revSortedVector(vectorLength, 1, (rand() % 1000));
                //test time of sort per code given in project manual
                start = chrono::high_resolution_clock::now();
                quickSort(testVector);
                end = chrono::high_resolution_clock::now();
                double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                times.push_back(elapsed);
            }
            break;
    }
    return times;
}
*/

/*
//now that there is a test function for each sorting method time to make the main test function
vector<double> testmaster(int sortingType, int vectorType, int vectorLength, int numTestCases){
    //we will have bubble sort as 1, insert as 2 and so on for sorting type switch cases
    vector<double> times;
    
    switch (sortingType) {
        case 1:
            times = testBubble(vectorType, vectorLength, numTestCases);
            break;
        case 2:
            times = testInsertion(vectorType, vectorLength, numTestCases);
            break;
        case 3:
            times = testSelection(vectorType, vectorLength, numTestCases);
            break;
        case 4:
            times = testQuick(vectorType, vectorLength, numTestCases);
            break;
    }
    return times;
}
I know I should have implemented vector containers for checking if test was successful, but just finishing up with the graphs and noticed dont have time :/
    nvm i was late now going to implement new testing function for the little ones
 */
/*
void mainTestingSorts(){
    int vectorType = 1;
    int vectorLength = 100;
    int numTests = 10;
    // going to only implement one test case of successful sort to make sure sorting is working
    cout << "Bubble sort on 10 vectors of length 100" << endl;
    cout << "Sorting Successful" << endl;
    timeStats(testmaster(1, vectorType, vectorLength, numTests));
    
    cout << "Insertion sort on 10 vectors of length 100" << endl;
    cout << "Sorting Successful" << endl;
    timeStats(testmaster(2, vectorType, vectorLength, numTests));
    
    cout << "Selection sort on 10 vectors of length 100" << endl;
    cout << "Sorting Successful" << endl;
    timeStats(testmaster(3, vectorType, vectorLength, numTests));
    
    cout << "Quick sort on 10 vectors of length 100" << endl;
    cout << "Sorting Successful" << endl;
    timeStats(testmaster(4, vectorType, vectorLength, numTests));
}
*/

void comprehensiveTestingHelper(const string& sort, vector<vector<int>>& vectors, int length, int numTestCases, const string& caseType, ofstream& outFile) {
    for (int i = 0; i < numTestCases; i++) {
        vector<int> testVector = vectors[i];

        // Start timer
        auto start = chrono::high_resolution_clock::now();

        // Sort the vector based on sort type
        if (sort == "bubble") {
            bubbleSort(testVector);
        } else if (sort == "insertion") {
            insertionSort(testVector);
        } else if (sort == "selection") {
            selectionSort(testVector);
        } else if (sort == "quick") {
            // Use modified quicksort for best case
            if (caseType == "best") {
                testVector = quickSortBestCase(testVector, true);
            } else {
                testVector = quickSortBestCase(testVector, false);
            }
        }

        // End timer
        auto end = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();

        // Write to CSV
        outFile << sort << "," << length << "," << elapsed << endl;
        
        //ahhhhhhhh why isnt it writing to my csvs
        // Debug output
        
//        cout << "Processed " << sort << " sort, " << caseType << " case, length " << length << ", test " << i + 1 << "/" << numTestCases << ", time: " << elapsed << " sec" << endl;
    }
}


/*
 goals of comprehensive testing:
 five vector lengths 10, 100, 1000, 5000, 10000
 50 test cases
 all types of vectors through all the types of sorting algorithms
 
 */
void comprehensiveTesting(){
    // Open CSV files
    //used a direct path as that is the only thing that allowed me to write to the csv files
    ofstream bestCases("/Users/stephantakacs/Documents/GitHub/alg:ds/cs311project1/cs311project1/bestCases.csv");
    ofstream averageCases("/Users/stephantakacs/Documents/GitHub/alg:ds/cs311project1/cs311project1/averageCases.csv");
    ofstream worstCases("/Users/stephantakacs/Documents/GitHub/alg:ds/cs311project1/cs311project1/worstCases.csv");
    

    // Check if files are open
    if(!bestCases.is_open() || !averageCases.is_open() || !worstCases.is_open()) {
        cout << "Failed to open output files." << endl;
        return;
    }

    // Define vector lengths and number of test cases
    vector<int> vectorLengths = {10, 100, 1000, 5000, 10000};
    int numTestCases = 50;

    // string of sorting algorithm types for if statements
    vector<string> sortTypes = {"bubble", "insertion", "selection", "quick"};

    // Iterate over each length
    for(int length : vectorLengths){
        // Generate vectors for this length
        vector<vector<int>> averageVectors;
        vector<vector<int>> sortedVectors;
        vector<vector<int>> revSortedVectors;

        // Generate vectors for average, best, and worst cases
        for(int i = 0; i < numTestCases; i++){
            averageVectors.push_back(randomVector(length, 1, 10000));
            sortedVectors.push_back(sortedVector(length, 1, 10000));
            revSortedVectors.push_back(revSortedVector(length, 1, 10000));
        }

        // Run tests for each sorting algorithm
        for(const string& sort : sortTypes){
            vector<vector<int>>* bestVectors;
            vector<vector<int>>* worstVectors;
            vector<vector<int>>* averageVectorsPTR = &averageVectors;

            // Special case for quicksort best/worst case
            if(sort == "quick"){
                bestVectors = &sortedVectors;
                worstVectors = &sortedVectors;
            } else {
                bestVectors = &sortedVectors;
                worstVectors = &revSortedVectors;
            }

            // Run tests + debug for each
            //cout << "Running " << sort << " sort, best case." << endl;
            comprehensiveTestingHelper(sort, *bestVectors, length, numTestCases, "best", bestCases);
            //cout << "Running " << sort << " sort, average case." << endl;
            comprehensiveTestingHelper(sort, *averageVectorsPTR, length, numTestCases, "average", averageCases);
            //cout << "Running " << sort << " sort, worst case." << endl;
            comprehensiveTestingHelper(sort, *worstVectors, length, numTestCases, "worst", worstCases);
        }
    }

    // Close CSV files
    bestCases.close();
    averageCases.close();
    worstCases.close();
}

//version 2 of the main testing that will use a similar method as the one I made for the comprehensive testing
//the helper will be pretty much identical to the comp testing helper func just also incluses the results
void mainTestingSortsHelper(const string& sort, int vectorLength, int numTestCases, vector<double>& times, vector<bool>& sortCheck) {
    for(int i = 0; i < numTestCases; i++){
        vector<int> testVector = randomVector(vectorLength, 1, rand() & 10000);
        
        // Start timer
        auto start = chrono::high_resolution_clock::now();

        // Sort the vector based on sort type
        if (sort == "bubble") {
            bubbleSort(testVector);
        } else if (sort == "insertion") {
            insertionSort(testVector);
        } else if (sort == "selection") {
            selectionSort(testVector);
        } else if (sort == "quick") {
            testVector = quickSort(testVector);
        }
        // End timer
        auto end = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
        
        //append time to times
        times.push_back(elapsed);
        
        //check if vector is actually sorted
        sortCheck.push_back(isSorted(testVector));
    }
    
}
void mainTestingSorts() {
    int numTestCases = 10;
    int vectorLength = 100;
    
    // Define sorting algorithms
    vector<string> sortTypes = {"bubble", "insertion", "selection", "quick"};
    
    for(const string& sort : sortTypes){
        cout << sort << " sort on " << numTestCases << " vectors of length " << vectorLength << endl;
        
        vector<double> times;
        vector<bool> sortCheck;
        
        //helper call to actually do the sorting tests
        mainTestingSortsHelper(sort, vectorLength, numTestCases, times, sortCheck);
        
        //now properly validate that the sort worked
        bool sortSuccess = true;
        for(bool sorted : sortCheck) {
            if(!sorted){
                sortSuccess = false;
                break;
            }
        }
        if(sortSuccess) cout << "Sorting Successful" << endl;
        else cout << "this better not happen the sorting has failed and the basis of the entire project has failed" << endl;
        
        timeStats(times);
        
        cout << endl;
    }
}


//now going to write the testing stuff in main with switch to do the small test
int main(int argc, const char * argv[]) {
    //seed random
    srand(time(NULL));
    /*
    int testType = -1;
    cout << "Please select the the type of test you would like to initialize, enter 1 for short test, enter 2 for comprehensive: ";
    cin >> testType;
    switch (testType) {
        case 1:
            mainTestingSorts();
            break;
            
        case 2:
            comprehensiveTesting();
            break;
    }
    */
    cout << "Running short sort sample tests" << endl;
    mainTestingSorts();
    
}

