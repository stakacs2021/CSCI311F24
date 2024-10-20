// CSCI 311
// Lab 1 Skeleton
// Author: Carter Tillquist

#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
using namespace std;

/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

//Stephan Takacs
//012540828

int collatzLength(int n){
    //track loop iterations in order to find the # term
    int count = 0;
    
    while(n != 1){
        count++;
        
        if(n % 2 == 0){
            n /= 2;
        }
        else{
            n = 3 * n + 1;
        }
    }
    return count;
}

void printStats(const vector<int> &v){
   //catch empty vector
    if(v.size() == 0){
        cout << "Empty vector" << endl;
    }
    //not empty
    else {
        //initalize variables for stats tracking
        int max = v[0];
        int min = v[0];
        int mean = v[0];
        for(int i = 1; i < v.size(); i++){
            if(v[i] > max){
                max = v[i];
            }
            if(v[i] < min){
                min = v[i];
            }
            mean = mean + v[i];
        }
        mean = mean/v.size();
        cout << min << " " << mean << " " << max << endl;
    }
}

int sumMultiples(const vector<int> &v, int n){
    //initialize the total sum
    int sum = 0;
    
    for (int i = 1; i < n; i++){
        //check through nums
        for (int num : v){
            //check multiple
            if(i % num == 0){
                sum += i;
                //found the sum move to the next number
                break;
            }
        }
    }
    return sum;
}

void greaterThanK(vector<int> &v, int k){
    //need to use .erase() to remove values so have to set a new beginning for the vector and new end
    int newBegindex = 0;
    
    for(int i = 0; i < v.size(); i++){
        if(v[i] > k ){
            v[newBegindex] = v[i];
            //essentially remove the value from the acceptable beginning
            newBegindex++;
            }
        }
    v.erase(v.begin() + newBegindex, v.end());
}

bool isSubarray(const vector<string> &a, const vector<string> &b){
    int vectASize = a.size();
    int vectBSize = b.size();
    bool isSubArray = false;
    
    //find where the subarray might start
    for(int i = 0; i <= vectBSize - vectASize; i++){
        isSubArray = true;
        
        for(int j = 0; j < vectASize; j++){
            //check if subarray beginning at i+j index is equal to a index
            if(b [i + j] != a[j]){
                isSubArray = false;
                break;
            }
        }
        //if the sub array was found
        if (isSubArray){
            return true;
        }
    }
    
    return false;
}

bool isPrimeA(int n){
  //first catch if number is < 1, added other edge cases after testing
    if(n <= 1) return false;
    if (n == 2) return true;
    //look for multiples of the number starting at 2
    for(int i = 2; i < n; i++){
       //if divisible not prime
        if (n % 1 == 0){
            return false;
        }
    }
    
    return true;
}

int sumPrimesA(int n){
    int sum = 0;
    
    //same logic as isprimeA look for all multiples
    for(int i = 2; i < n; i++){
        if(isPrimeA(i)){
            sum = sum + i;
        }
    }
    return sum;
}

bool isPrimeB(int n){
    //adding other edge case handling
    if(n <= 1) return false;
    if (n==2) return true;
    if (n % 2 == 0) return false;
    //look for multiples of the number starting at 2 and going up to square root of n
    for(int i = 3; i < sqrt(n); i++){
       //if divisible not prime
        if (n % 1 == 0){
            return false;
        }
    }
    
    return true;
}

int sumPrimesB(int n){
    int sum = 0;
    
    //copy paste of a just calling isprimeb
    for(int i = 2; i < n; i++){
        if(isPrimeB(i)){
            sum = sum + i;
        }
    }
    return sum;
}

int sieveOfEratosthenes(int n){
  //first catch <= 2 nums
    if (n <= 2 ) return 0;
    vector<int> primes(n, 1);
    // 0,1 aren't prime
    primes[0] = 0;
    primes[1] = 0;
    
    //begin multiples search
    for(int i = 2; i * i < n; i++){
        if(primes[i]) {
            //find all multiples of i in the vector
            for (int j = i * i; j < n; j = j + i){
                primes[j] = 0;
            }
        }
    }
    //now done marking its time to sum
    int sum = 0;
    for(int k = 2; k < n; k++){
        if(primes[k]){
            sum = sum + k;
        }
    }
    return sum;
    
}

/*************************************************************
 * Your solutions ends here and do not change anything below *
 * ***********************************************************/

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);
void timePrimes();

int main(){
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, k = 0, m = 0;
  vector<int> v;
  string s = "";
  vector<string> a;
  vector<string> b;

  switch (question){
    case 1: //collatzLength
      cout << "Collatz Sequence n: ";
      cin >> n;
      cout << collatzLength(n) << endl;
      break;
    case 2: //printStats
      cout << "Print Stats Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "Stats: " << endl;
      printStats(v);
      break;
    case 3: //sumMultiples
      cout << "Sum Multiples Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "Max Value: ";
      cin >> k;
      cout << "Sum: ";
      cout << sumMultiples(v, k) << endl;
      break;
    case 4: //greaterThanK
      cout << "Greater than K Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "k: ";
      cin >> k;
      cout << "Result: ";
      greaterThanK(v, k);
      for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
      break;
    case 5: //isSubarray
      cout << "Is Subarray Array Sizes: ";
      cin >> n >> m;
      cout << "Values for First Vector: ";
      for (int i = 0; i < n; i++){
        cin >> s;
        a.push_back(s);
      }
      cout << "Values for Second Vector: ";
      for (int i = 0; i < m; i++){
        cin >> s;
        b.push_back(s);
      }
      cout << "Result: ";
      cout << isSubarray(a, b) << endl;
      break;
    case 6: //naive prime sum
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sumPrimesA(n) << endl;
      break;
    case 7: //prime sum 2
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sumPrimesB(n) << endl;
      break;
    case 8: //sieve of eratosthenes
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sieveOfEratosthenes(n) << endl;
      break;
    case 9: //time primes
      cout << "Time Primes" << endl;
      timePrimes();
      break;
  }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n){
  int m = 0;
  for (int i = 0; i < n; i++){
    cin >> m;
    v.push_back(m);
  }
}

/***************************************************************************************************
 * Testing run times of different approaches to finding the sum of prime numbers under a threshold *
 * *************************************************************************************************/
void timePrimes(){
  int sum = -1;
  chrono::high_resolution_clock::time_point start;
  chrono::high_resolution_clock::time_point end;
  double elapsed = -1;
  vector<int> x = {10, 100, 1000, 10000, 100000, 500000};
  for (int i = 0; i < x.size(); i++)
  {
    cout << "Value: " << x[i] << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesA(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "A ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesB(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "B ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sieveOfEratosthenes(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "C ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;
    cout << endl << endl;
  }

  cout << "Sieve of Eratosthenes on primes below 1 million" << endl;
  start = chrono::high_resolution_clock::now();
  long sum2 = sieveOfEratosthenes(1000000);
  end = chrono::high_resolution_clock::now();
  elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
  cout << "Sum: " << sum2 << ", Time elapsed: " << elapsed << endl;
  cout << endl << endl;
}
