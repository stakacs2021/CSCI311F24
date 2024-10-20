// Lab 2 Skeleton
// Author: *** YOUR NAME HERE ***

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;


/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

int triangleNum(int n){
  return 0;
}

int rFib(int n){
  return 0;
}

int rSumHelper(const vector<int> &v, int i){
  return 0;
}

int rSum(const vector<int> &v){
  return 0;
}

int rMaxHelper(const vector<int> &v, int start){
  return 0;
}

int rMax(const vector<int> &v){
  return 0;
}

bool isSorted(const vector<int> &v, int start, int end){
  return false;
}

bool isPalindromeHelper(string s, int start, int end){
  return false;
}

bool isPalindrome(string s){
  return false;
}

int rBinarySearch(const vector<int> &v, int low, int high, int target){
  return 0;
}

bool rSubsetSum(const vector<int> &v, int start, int target){
  return 0;
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);

int main(){
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, start = 0, end = 0;
  vector<int> v;
  string s = "";
  switch (question){
    case 1: //triangleNum
      cout << "Triangle Number n: ";
      cin >> n;
      cout << triangleNum(n) << endl;
      break;
    case 2: //rFib
      cout << "Nth Fibonacci Number: ";
      cin >> n;
      cout << rFib(n) << endl;
      break;
    case 3: //rSum
      cout << "Recursive Sum Vector Size: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rSum(v) << endl;
      break;
    case 4: //rMax
      cout << "Recursive Max Vector Size: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rMax(v) << endl;
      break;
    case 5: //isSorted
      cout << "isSorted Vector Size: ";
      cin >> n;
      cout << "Start and End: ";
      cin >> start >> end;
      cout << "Values: ";
      readIntVector(v, n);
      cout << isSorted(v, start, end) << endl;
      break;
    case 6: //isPalindrome
      cout << "String: ";
      cin >> s;
      cout << isPalindrome(s) << endl;
      break;
    case 7: //rBinarySearch
      cout << "Binary Search Vector Size: ";
      cin >> n;
      cout << "Target: ";
      cin >> end;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rBinarySearch(v, 0, v.size()-1, end) << endl;
      break;
    case 8: //rSubsetSum
      cout << "Subset Sum Vector Size: ";
      cin >> n;
      cout << "Target: ";
      cin >> end;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rSubsetSum(v, 0, end) << endl;
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
