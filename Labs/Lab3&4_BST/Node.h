// CSCI 311 - Spring 2023
// Node Header
// Author: Carter Tillquist

#ifndef NODE_H
#define NODE_H

#include <memory>

class Node{
  public:
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    
    Node();
    Node(int);
    ~Node();
};

#endif