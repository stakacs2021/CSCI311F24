// CSCI 311 - Spring 2023
// Node Class
// Author: Carter Tillquist

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

class Node{
  public:
    int id;
    int dist;
    int discovered;
    int finished;
    bool visited;
    std::shared_ptr<Node> predecessor;
    std::vector<std::shared_ptr<Node>> neighbors;
    
    Node();
    Node(int);
};

#endif