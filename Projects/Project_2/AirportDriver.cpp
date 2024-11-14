/***********************************************
************CSCI-311-PROJECT-2-V-2071***********
************************************************
*******CODE-CHECKER-STARTING-ALIGNMENT**********
************************************************
*************CONTROL-NUMBER-XA-72***************
************************************************
**REPORT-GENERATION-MODE-AUTO_SYNC-EXCEPTION-2**
************************************************
*****************DATETIME-SYS*******************
************************************************/

//G1_EXCEPTION: Only produce your code as directed in Section A, B, C, and D1_EXCEPTION.
//G2_EXCEPTION: Do not write anything at the other places in this file.
//D1_EXCEPTION: Put you names here (on this line): Stephan Takacs

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
//SECTION_A_START: put your header files here using the include directive.
//G3_EXCEPTION: You can also declare using standard namespace if you like, but do not use any global variable or method.
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;


//SECTION_A_END: Section A ends here.
/***********************************************
*************SECTION-A-HEADERS-END**************
************************************************/

/***********************************************
*************SECTION-B-CLASSES******************
************************************************/
/*
classes to include: I want to make a class called aircraft and one called runway
althought it does look like from the project requirements aircraft and runway are both going to be priority queues
just based on the fact that output needs to be in the same order as the input
aircraft needs to have attributes:
int (time of entry)
int (aircraft id)
string (departing or arriving)
int (priority) << place in the priority queue
want to also overload < operator so i can compare priorities, will make sorting and organization a lot easier
and function to print

*/
//SECTION_B_START: put all your classes definitions here.
//aircraft class
class aircraft {
public:    //variables
    int tOE, acID, acPriority;
    string depOrArr;

    //constructor
    aircraft(int time, int identification, int priority, const string& status)
        : tOE(time), acID(identification), acPriority(priority), depOrArr(status) {}

    //print deets
    void printAC() const {
        cout << "Aircraft ID: " << acID;
        cout << ", Priority: " << acPriority;
        cout << ", Time of Entry: " << tOE;
        cout << ", Status: " << depOrArr;

    }

    //going to overload the < operator so can do priority comparison in heap
    //rewrote once I wrote the rest of the priority queue class to include < and >
    //for max heapify, push
    bool operator>(const aircraft& other) const{
        //if priority is the same then its based on toe
        if (acPriority == other.acPriority){
            return tOE < other.tOE;
        }
        return acPriority > other.acPriority;
    }

    bool operator<(const aircraft& other) const {
        return !(*this > other);
    }
};

/*
For pq I need:
empty(bool function to return true if empty)
size(int)
push(void: will be implemented to push my aircraft class into the pqueue)
pop(going to pop out aircraft)
peek(returns aircraft)
also may want to include:
top (returns reference to top object in queue)
printqueue(just prints all of the elements in the queue and their sub elements


Priority Queue difference from queue:
every element in the queue has a priority associated with it
items that are higher priority are served ahead of low priority (duh)
two elements with the same priority are served on basis of queue entry
lower priority value = greater priority
*/
class PriorityQueue{
private:
        vector<aircraft> heap;

        //heapify to maintain order
        /*
        downward heapify puesdocode from lecture slides:
        function max-heapify(H, i)
        l = 2i+1
        r = 2i+2
        m = i
        if l < size(H) and H[l]
        m = l
        if r < size(H) and H[r]
        m = r
        if m != i
        swap(H, i, m)
        max-heapify(H, m)
        */
    void maxHeapify(int i) {
        int size = heap.size();
        //calculate size indices of children
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int m = i;

        if(l < size && heap[l] > heap[m]) {
            m = l;
        }

        if(r < size && heap[r] > heap[m]){
            m = r;
        }
        if(m != i){
            swap(heap[i], heap[m]);
            maxHeapify(m);
        }
    }

public:
    PriorityQueue() {}

    //listed functions
    bool empty() const{
        return heap.empty();
    }

    int size() const{
        return heap.size();
    }

    /*
    going to use insert puesdocode from lecture slides for my push function:
    puesdocode for insert from lecture slides (08-01):
    function insert(H, v)
    H = H + [v]
    i = size(H)-1
    while i > 0 and H[floor((i-1)/2)] < H[i]
    swap(H, i, floor((i-1)/2))
    i = floor((i-1)/2)
    */
    void push(const aircraft& aircraft){
        heap.push_back(aircraft);

        int i = heap.size() - 1;

        while(i > 0 && heap[floor((i -1) / 2)] < heap[i]){
            swap(heap[i], heap[floor((i - 1) / 2)]);
            i = floor((i - 1) / 2);
        }

    }

    void pop() {
        if (empty()){
            cerr << "PQueue is empty" << endl;
            return;
        }
        //replace root with last element
        heap[0] = heap.back();
        heap.pop_back();

        maxHeapify(0);
    }

    aircraft peek() const {
        if (empty()) {
            cerr << "PQueue is empty" <<endl;
            return aircraft();
        }
        return heap[0];
    }

    aircraft& top() {
        if(empty()) {
            cerr << "PQueue is empty" << endl;
        }
        return heap[0];
    }

    void printQueue() const{
        cout << "PQueue Elements: " << endl;
        for(const auto& aircraft : heap) {
            aircraft.printAC();
        }
    }

    void clear() {
        heap.clear();
    }

};





//SECTION_B_END: Section B ends here.
/***********************************************
*************SECTION-B-CLASSES-END**************
************************************************/


/***********************************************
*************SECTION-C-MAIN-FUNCTION************
************************************************/
//SECTION_C_START: write your main function here.





//SECTION_C_END: Section C ends here.
/***********************************************
************SECTION-C-MAIN-FUNCTION-END*********
************************************************/

/***********************************************
**************PLAGIARISM-RTNG-PRTCL-C***********
****************GEN-AI-RTNG-PRTCL-K*************
*********LOOP-CS_SEC-CS_CHR-STU_R_R_RFR*********
*****************DICT-A-ENTRY-2071**************
***************ORI-KTIAN@CSUCHICO.EDU***********
************************************************/

/***********************************************
*********CODE-CHECKER-ENDING-ALIGNMENT**********
************************************************/
