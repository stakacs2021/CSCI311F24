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

*/
void Graph::printAdjList(){
    //look through all nodes based on order of their ids
    for(int i = 0; i < nodes.size(); i++){
        //print curr node id
        std::cout << nodes[i]->id << ": ";

        //now look through the neighbors of node i and print ids
       for(int j = 0; j < nodes[i]->neighbors.size(); j++){
           std::cout << nodes[i]->neighbors[j]->id;

           //output formatting to make sure no extra space at the end of the line
           if(j < nodes[i]->neighbors.size() - 1){
               std::cout << " ";
           }
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
*/
void Graph::DFS(){

    //first prep the graph by setting all nodes to initial state
    for(int i = 0; i < nodes.size(); i++){
        nodes[i]->visited = false;
        nodes[i]->discovered = -1;
        nodes[i]->finished = -1;
        nodes[i]->predecessor = nullptr;
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
*/
int Graph::DFSVisit(int s, int time){
    nodes[s]->visited = true;
    //increment time
    time++;
    //record discovery time
    nodes[s]->discovered = time;

    for (size_t i = 0; i < nodes[s]->neighbors.size(); i++) {
        if (!nodes[s]->neighbors[i]->visited) {
            nodes[s]->neighbors[i]->predecessor = nodes[s];
            time = DFSVisit(nodes[s]->neighbors[i]->id, time);
            }
        }

        time++;
        nodes[s]->finished = time;
        return time;
}

//perform bfs from node s
void Graph::BFS(int s){

    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i]->visited = false;
        nodes[i]->dist = INT_MAX;
        nodes[i]->predecessor = nullptr;
    }

    nodes[s]->visited = true;
    nodes[s]->dist = 0;

    std::queue<std::shared_ptr<Node>> q;
    q.push(nodes[s]);


    while (!q.empty()) {
        std::shared_ptr<Node> current = q.front();
        q.pop();


        for (size_t i = 0; i < current->neighbors.size(); i++) {
            if (!current->neighbors[i]->visited) {
                current->neighbors[i]->visited = true;
                current->neighbors[i]->dist = current->dist + 1;
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
