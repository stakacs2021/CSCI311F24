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
#include <stdexcept>
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
class Aircraft {
public:    //variables
    int tOE, acID, acPriority, inputOrder;
    string depOrArr;

    //default constructor should fix issues with peek/print
    Aircraft() : tOE(0), acID(0), acPriority(0), depOrArr(""), inputOrder(0) {}
    //constructor
    Aircraft(int time, int identification, int priority, const string& status, int order)
        : tOE(time), acID(identification), acPriority(priority), depOrArr(status), inputOrder(order) {}

    //print deets
    void printAC() const {
        /* debug labeled out
        cout << "Aircraft ID: " << acID;
        cout << ", Priority: " << acPriority;
        cout << ", Time of Entry: " << tOE;
        cout << ", Status: " << depOrArr << endl;
        */
        cout << tOE << " " << acID << " " << depOrArr << " " << acPriority << endl;

    }

    //going to overload the < operator so can do priority comparison in heap
    //rewrote once I wrote the rest of the priority queue class to include < and >
    //for max heapify, push
    //for the t31 fail its gotta be this im so silly <- handle same toe and prior
    bool operator>(const Aircraft& other) const{
        if(acPriority != other.acPriority){
            return acPriority < other.acPriority;
        }
        if(tOE != other.tOE){
            return tOE < other.tOE;
        }

        return inputOrder < other.inputOrder;

    }
    //for t04 the last time step is flipped and it is because i am not handling same edges with < operator
    bool operator<(const Aircraft& other) const {
        if(acPriority != other.acPriority){
            return acPriority > other.acPriority;
        }
        if(tOE != other.tOE){
            return tOE > other.tOE;
        }
        return inputOrder > other.inputOrder;
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
        vector<Aircraft> heap;

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
    void push(const Aircraft& aircraft){
        heap.push_back(aircraft);

        int i = heap.size() - 1;

        while(i > 0 && heap[(i -1) / 2] < heap[i]){
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }

    }

    void pop() {
        if (empty()){
            return;
        }
        //replace root with last element
        heap[0] = heap.back();
        heap.pop_back();

        if(!empty()){
            maxHeapify(0);
        }
    }

    Aircraft peek() const {
        if (empty()) {
            return Aircraft();
        }
        return heap[0];
    }

    Aircraft& top() {
        if(empty()) {
            cerr << "PQueue is empty" << endl;
        }
        return heap[0];
    }

    void printQueue() const{
        cout << "PQueue Elements: " << endl;
        for(int i = 0; i < heap.size(); i++) {
           heap[i].printAC();
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
//writing a test main:
int main() {
    /* Small testing function for classes
    PriorityQueue sampleRunway;

    //adding sample acs
    sampleRunway.push(Aircraft(10, 101, 2, "arriving"));
    sampleRunway.push(Aircraft(12, 102, 3, "departing"));
    sampleRunway.push(Aircraft(11, 103, 2, "arriving"));
    sampleRunway.push(Aircraft(13, 104, 5, "departing"));

    //check if everything was loaded correctly
    sampleRunway.printQueue();

    //check priority functionality
    while (!sampleRunway.empty()) {
        Aircraft aircraft = sampleRunway.peek();
        sampleRunway.pop();

        //output currently processing
        cout << "Processing ";
        aircraft.printAC();
    }
    */

    /*
   main simulation:
   requirements:
   time is incremented discreetly
   at each time step something should be printed
   Output format:
   time step <time>
    Entering simulation
        <aircraft information>
        <...>
        <aircraft information>
   Runway A
    <aircraft information>
   Runway B
    <aircraft information>
    Input info: each indentation is a tab, use esc \t
    Ex output (one aircraft enters sim, one takes off runway A timestep 42)
    Time step 42
        Entering simulation
            42 10 departing 5
        Runway A
            23 4 departing 2
    Runway B
    ________
    main function first starts off by taking number of aircraft coming in
    going to make a vect of the aircraft based on that number
    then read the status of them all into the vect
    then create pqs for the aircrafts
    */
    //take number of aircraft
    int numAircraft;
    cin >> numAircraft;

    //create a vector of the aircrafts by reading in from input
    //updating this part to account for input order as well, using iterator inputOrderCounter
    int inputOrderCounter = 0;
    vector<Aircraft> aircraftList;
    for(int i =0; i < numAircraft; i++){
        //take all different variables of aircraft and load them in
        int time, id, priority;
        string status;
        cin >> time >> id >> status >> priority;
        //load them all into each aircraft in the vector
        aircraftList.push_back(Aircraft(time, id, priority, status, inputOrderCounter));
        inputOrderCounter++;
    }

    //now start simulation
    //track time for stepping
    int currentTime = 0;
    //track list of aircraft
    int index = 0;
    //i am pretty sure the professor said I should make to pqs for arriving and dept, but i could not really hear him. This is the approach I am going to take though at it seems way more simple
    PriorityQueue departures;
    PriorityQueue arrivals;

    //actual simulation loop
    //want to loop through the list of aircraft until we have visited them all or departures or arrivals is empty
    while(index < aircraftList.size() || !departures.empty() || !arrivals.empty()){
        //bool to track each landing/takeoff
        bool eventOccurred = false;

        //create a new vector of aircraft that are in action at the current time
        vector<Aircraft> currTimeAircraft;
        while (index < aircraftList.size() && aircraftList[index].tOE == currentTime){
            //if we find an aircraft that is currently in action eval
            const Aircraft& currAircraft = aircraftList[index];
            if(currAircraft.depOrArr == "departing"){
                departures.push(currAircraft);
            }
            else if(currAircraft.depOrArr == "arriving"){
                arrivals.push(currAircraft);
            }
            currTimeAircraft.push_back(currAircraft);
            index++;
            eventOccurred = true;
        }

        //now manage ac info for runways
        Aircraft aircraftA;
        Aircraft aircraftB;
        //track which runway is being used
        bool runwayAUsed = false;
        bool runwayBUsed = false;

        //process runways
        //runway b
        if(!arrivals.empty()) {
            aircraftB = arrivals.peek();
            arrivals.pop();
            runwayBUsed = true;
            eventOccurred = true;
        }

        if(!departures.empty()) {
            aircraftA = departures.peek();
            departures.pop();
            runwayAUsed = true;
            eventOccurred = true;
        }

        //runway b
        else if(!arrivals.empty()) {
            aircraftA = arrivals.peek();
            arrivals.pop();
            runwayAUsed = true;
            eventOccurred = true;
        }

        if(!runwayBUsed && !departures.empty()) {
            aircraftB = departures.peek();
            departures.pop();
            runwayBUsed = true;
            eventOccurred = true;
        }
        /*
        this turned out to be the issue in addition to the overloaded operators
        rather than using ifs/elif needed to add a case that would catch runway B used and
        departues is empty
        */

        /*now everytime an event happens need to output
        output format:
        Output format:
        time step <time>
         Entering simulation
             <aircraft information>
             <...>
             <aircraft information>
        Runway A
         <aircraft information>
        Runway B
         <aircraft information>
        */
        if(eventOccurred) {
            cout << "Time step " << currentTime << endl;

            cout << "\tEntering simulation" << endl;
            for(int i = 0; i < currTimeAircraft.size(); i++){
                cout << "\t\t";
                currTimeAircraft[i].printAC();
            }

            //runway a out
            cout << "\tRunway A" << endl;
            if(runwayAUsed){
                cout << "\t\t";
                aircraftA.printAC();
            }

            //runway b out
            cout << "\tRunway B" << endl;
            if(runwayBUsed){
                cout << "\t\t";
                aircraftB.printAC();
            }
        }
        //after each event step time
        currentTime++;
    }
    return 0;
}




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
