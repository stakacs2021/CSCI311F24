// CSCI 311 lab 7
// Graph class skeleton cpp file
// change name to "Graph.cpp"
//Stephan Takacs

#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>

//do not change the headers above
//implement the functions below, but do not add new functions

/*
Implement a default constructor for the Graph class. Initially, there should be no nodes in the graph.
*/
Graph::Graph(){
  nodes = {};
}

/*
The method needs to print graph info in the form of an adjacency list
Format for list:
line start with node id, then :, followed by space separated list of adjacent nodes
one line per node
order of nodes is determined by order in which neighbors of each node is stored
iteratate through all notes and find neighbors
*/
void Graph::printAdjList(){
    //look through all nodes based on order of their ids
    for(int i = 0; i < nodes.size(); i++){
        //print curr node id
        std::cout << nodes[i]->id << ": ";

        //now look through the neighbors of node i and print ids
       for(int j = 0; j < nodes[i]->neighbors.size(); j++){
           std::cout << nodes[i]->neighbors[j]->id << " ";
       }
       std::cout << std::endl;
    }
}

/*
returns true if v is a neighbor of u
*/
bool Graph::isNeighbor(int u, int v){
//first check to made sure the ids exist
    if(u < 0 || u >= nodes.size() || v < 0 || v >= nodes.size()){
        return false;
    }

//search through u's neighbors for v
    for(int i = 0; i < nodes[u]->neighbors.size(); i++){
        if(nodes[u]->neighbors[i]->id == v){
            return true;
        }
    }
    return false;
}


/*
prepares the graph for dfs and will call the recursive helper funtion dfs visit
function DFS(G):
 for u in v
    u.visited = false
    u.predecessor - null
    u.discovered = -1
    u.finished = - 1
time = 0
for u in v:
    if u.visited == false
    time = DFSVisist(G, u , time)
*/
void Graph::DFS(){

    //first prep the graph by setting all nodes to initial state
    for(int i = 0; i < nodes.size(); i++){
        nodes[i]->visited = false;
        nodes[i]->predecessor = nullptr;
        nodes[i]->discovered = -1;
        nodes[i]->finished = -1;
    }
    //for dfs visit need start time
    int time = 0;

    for(int i = 0; i < nodes.size(); i++){
        if(!nodes[i]->visited){
            time = DFSVisit(i, time);
        }
    }

}

/*
runs the dfs search from node s with start time. keeps track of discovery and finish times for each node
discover time for first node visited should be 1
pesudocode:
funnctionDFSvisit(G, u, time)
time = time + 1
u.discovered = true
u.visited = true
for v in neighbors(G, u):
    if v.visited = false
     v.predecessor = u
     time = DFSVisist(G, v, time)
time = time + 1
u.finished = true
return time
*/
int Graph::DFSVisit(int s, int time){
    // Increment time first
    time++;
    // Set discovered time and mark as visited
    nodes[s]->discovered = time;
    nodes[s]->visited = true;

    // Visit all unvisited neighbors
    for (size_t i = 0; i < nodes[s]->neighbors.size(); i++) {
        if(!nodes[s]->neighbors[i]->visited){
            nodes[s]->neighbors[i]->predecessor = nodes[s];  // Set predecessor before recursive call
            time = DFSVisit(nodes[s]->neighbors[i]->id, time);
        }
    }

    // Increment time and set finish time
    time++;
    nodes[s]->finished = time;
    return time;
}

//perform bfs from node s
/*
pseudocode from lecture slides
fu n c t i o n B F S ( G , s )
f o r u i n V
u . di s t = ∞
u . v i s i t e d = f a l s e
u . pr e de c e s s or = nul l
s . di s t = 0
s . v i s i t e d = t r ue
Q = que ue ( )
Q. pus h ( s )
whi l e l e ng t h ( Q) > 0
u = Q. pop ( )
f o r v i n n e i g h b o r s ( G , u )
i f v . v i s i t e d == f a l s e
v . di s t = u.dist + 1
v . v i s i t e d = t r ue v .
pr e de c e s s or = u Q.
pus h ( v )

*/
void Graph::BFS(int s){

    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i]->visited = false;
        nodes[i]->dist = INT_MAX;
        nodes[i]->predecessor = nullptr;
    }

    nodes[s]->dist = 0;
    nodes[s]->visited = true;


    std::queue<std::shared_ptr<Node>> q;
    q.push(nodes[s]);


    while (!q.empty()) {
        std::shared_ptr<Node> current = q.front();
        q.pop();


        for (size_t i = 0; i < current->neighbors.size(); i++) {
            if(!current->neighbors[i]->visited){
            // setup props before queuing
                current->neighbors[i]->dist = current->dist + 1;
                current->neighbors[i]->visited = true;
                current->neighbors[i]->predecessor = current;
                q.push(current->neighbors[i]);
            }
        }
    }
}


std::vector<int> Graph::distancesFrom(int s){
    BFS(s);

    std::vector<int> distances;
    for (size_t i = 0; i < nodes.size(); i++) {
        distances.push_back(nodes[i]->dist);
    }

    return distances;
}
