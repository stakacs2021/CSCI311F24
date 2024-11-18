// CSCI 311 - Spring 2023
// Lab 7 Driver
// Author: Carter Tillquist

#include <iostream>
#include <string>
#include "Node.h"
#include "Graph.h"
#include <limits.h>
using namespace std;

Graph makeGraph();
void checkNeighbors(Graph &G);
void checkDistancesFrom(Graph &G);
int main(){
  Graph G;

  int operation = -1;
  cin >> operation;

  while (operation > 0){
    switch(operation){
      case 1:
        cout << "MAKE GRAPH" << endl;
        G = makeGraph();
        break;
      case 2:
        cout << "ADJACENCY LIST" << endl;
        G.printAdjList();
        break;
      case 3:
        cout << "IS NEIGHBOR" << endl;
        checkNeighbors(G);
        break;
      case 4:
        cout << "DFS" << endl;
        G.DFS();
        for (int i = 0; i < G.nodes.size(); i++){
          cout << G.nodes[i]->id << ": " 
               << (G.nodes[i]->visited ? "True" : "False") << ", "
               << G.nodes[i]->discovered << ", "
               << G.nodes[i]->finished << ", "
               << ((G.nodes[i]->predecessor != nullptr) ? G.nodes[i]->predecessor->id : -1) << endl;
        }
        break;
      case 5:
        cout << "DISTANCES FROM" << endl;
        checkDistancesFrom(G);
        break;
      default:
        break;
    }
    cin >> operation;
  }

  return 0;
}

/*******************************************************************************************************************
 * A function to collect input from the user for making a simple graph. The first line of input should include two *
 * integers, n and m, representing the number of nodes and the number of edges in the graph. The following m lines *
 * each contain a pair of space separated integers representing edges in the graph.                                *
 * return - Graph - a graph constructed based on the user input                                                    *
 * *****************************************************************************************************************/
Graph makeGraph(){
  int n = 0, m = 0;
  cin >> n >> m;
  Graph G;
  for (int i = 0; i < n; i++){
    std::shared_ptr<Node> v(new Node(i));
    G.nodes.push_back(v);
  }
  for (int i = 0; i < m; i++){
    int u = -1, v = -1;
    cin >> u >> v;
    G.nodes[u]->neighbors.push_back(std::shared_ptr<Node>(G.nodes[v]));
    G.nodes[v]->neighbors.push_back(std::shared_ptr<Node>(G.nodes[u]));
  }
  return G;
}

/**************************************************************************************************************
 * A function to collect input from the user for checking whether or not nodes are neighbors in a given graph *
 * G - Graph & - a graph in which to check neighbors for a set of pairs of nodes                              *
 * ************************************************************************************************************/
void checkNeighbors(Graph &G){
  int num = -1;
  cin >> num;
  for (int i = 0; i < num; i++){
    int u = -1, v = -1;
    cin >> u >> v;
    cout << u << " " << v << " " << (G.isNeighbor(u, v) ? "True": "False") << endl;
  }
}

/*****************************************************************************************************************
 * A function to collect input from the user for checking distances from one node to all others in a given graph *
 * G - Graph & - a graph in which to check distances for a set of nodes acting as the source                     *
 * ***************************************************************************************************************/
void checkDistancesFrom(Graph &G){
  int num = -1;
  cin >> num;
  for (int i = 0; i < num; i++){
    int s = -1;
    cin >> s;
    vector<int> dists = G.distancesFrom(s);
    cout << "source " << s << ": ";
    for (int j = 0; j < G.nodes.size(); j++){
      cout << "(to " << G.nodes[j]->id << ": " 
           << ((G.nodes[j]->dist == INT_MAX) ? -1 : G.nodes[j]->dist) << ", "
           << ((dists[j] == INT_MAX) ? -1 : dists[j]) << ") ";
    }
    cout << endl;
  }
}