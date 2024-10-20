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
    //base case
    if (n <= 1) return 1;
        
    //recursive implementation
    return n + triangleNum(n - 1);
}



int rFib(int n){
    //base cases
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    //fibonacci implementation is literally just the given formula
    return rFib(n - 1) + rFib(n -2);
    
}

//use helper function to call itself and add to i
int rSumHelper(const vector<int> &v, int i){
    //base case need to use i as the iterator and need to chekc if its out of bounds of the
    if(i >= v.size()) {
        return 0;
    }
    return v[i] + rSumHelper(v, i + 1);
}
//starts the recursion and passes it off to the helper function
int rSum(const vector<int> &v){
    //pass it the first index
    return rSumHelper(v, 0);
}

//helper function will check for base case see if the vector is one element and then store a variable to check the max and return to itself
int rMaxHelper(const vector<int> &v, int start){
    if (start == v.size()) return INT_MIN;
    
    //compare the max and then return
    int max = rMaxHelper(v, start + 1);
    return (v[start] > max) ? v[start] : max;
    
}
//use function to start search and check for base case of function being empty
int rMax(const vector<int> &v){
    if (v.empty()) return INT_MIN;
    
    return rMaxHelper(v, 0);
}

bool isSorted(const vector<int> &v, int start, int end){
    //base case nothing in vector or 1 element it is sorted
    if (start >= end) return true;
    
   //if current element and next are not in order then not ascending
    if(v[start] > v[start + 1]) return false;
    
    //pass to function again and iterate to next index to compare
    return isSorted(v, start + 1, end);
}
bool isPalindromeHelper(string s, int start, int end){
    //if we have iterated all of the way through the word without false then it is a palindrome
    if (start >= end) return true;
    
    //covert to lowercase and compare both sides of the palindrome
    if (tolower(s[start]) != tolower(s[end])) return false;
    
    //iterate to the inter bounds of the word and pass back to the function
    return isPalindromeHelper(s, start + 1, end - 1);
    
}
//assuming that the string is all lowercase and alphanumeric function will pass to helper while iterating on the length of the string. essentially splitting string
bool isPalindrome(string s){
    
    return isPalindromeHelper(s, 0, s.length() - 1);
    
}
int rBinarySearch(const vector<int> &v, int low, int high, int target){
    //base case first check if the indexes are valid
    if (low > high) return - 1;
    
    //going to find middle of the vector as i have done binary search before i know this helps for overflow and faster
    int mid = low + (high - low) / 2;
    
    //if found at mid return mid
    if (v[mid] == target) return mid;
    
    //check if targer is smaller than mid so we can split to subarrays
    else if (target < v[mid]) return rBinarySearch(v, low, mid - 1, target);
    
    //if not greater time to check right subarray
    else return rBinarySearch(v, mid + 1, high, target);
    
}
bool rSubsetSum(const vector<int> &v, int start, int target){
    //base case 1 if target is 0 empty subset is fine
    if (target == 0) return true;
    
    //base case 2 if all elements have been considered and target cannot be found
    if(start >= v.size()) return false;
    
    //recursive case 1 include current element and check if target can be found
    if(rSubsetSum(v, start + 1, target - v[start])) return true;
    
    //recursive case 2 exclude current element and check for target
    if(rSubsetSum(v, start + 1, target)) return true;
    
    //if cannot be found with current element or excluding
    return false;
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
* Read a vector of integers in from cin *
* v - vector<int> & - the integer vector to fill *
* n - int - the number of integers to read *
* ************************************************/
void readIntVector(vector<int> &v, int n){
int m = 0;
for (int i = 0; i < n; i++){
cin >> m;
v.push_back(m);
}
}
