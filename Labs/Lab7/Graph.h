// CSCI 311 - Spring 2023
// Graph class header
// Author: Carter Tillquist

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include "Node.h"

class Graph{
  public:
    std::vector<std::shared_ptr<Node>> nodes;

    Graph();

    void printAdjList();
    bool isNeighbor(int, int);
    void DFS();
    int DFSVisit(int, int);
    void BFS(int);
    std::vector<int> distancesFrom(int);
};

#endif